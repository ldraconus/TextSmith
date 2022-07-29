#include "epub.h"

#include <QApplication>
#include <QClipboard>
#include <QJsonArray>
#include <QTextEdit>

EPUB::Scene EPUB::objectToScene(const QJsonObject& obj) {
    EPUB::Scene scene;
    scene._html = obj["doc"].toString("");
    scene._name = obj["name"].toString("");
    const QJsonArray& tags = obj["tags"].toArray();
    for (auto tag: tags) scene._tags.append(tag.toString("").toLower());
    return scene;
}

EPUB::Scene EPUB::objectToItem(const QJsonObject& obj)
{
    EPUB::Scene scene = objectToScene(obj);
    const QJsonArray& children = obj["children"].toArray();
    for (auto child: children) scene._children.append(objectToItem(child.toObject()));
    return scene;
}

void EPUB::novelToBook(QJsonObject obj, QList<Chapter>& book, Tree& tree) {
    const QJsonObject& doc = obj["document"].toObject();
    const QJsonObject& root = doc["root"].toObject();
    tree._top = objectToItem(root);

    TextEdit edit(_dir);
    _name = tree._top._name;
    sceneToDocument(book, edit, tree._top);
    int last = book.length() - 1;
    if (last >= 0) book[last]._html = edit.toHtml();
}

bool EPUB::recognizeTag(const QList<QString>& tags, const QString& tag) {
    return tags.indexOf(tag) != -1;
}

bool EPUB::allWS(QString x) {
   for (int i = 0; i < x.count(); ++i) if (!x[i].isSpace()) return false;
   return true;
}

bool EPUB::saveStringByTag(const QList<QString>& tags, QString& where, QString tag, const QString& html) {
    if (recognizeTag(tags, tag)) {
        TextEdit edit(_dir);
        edit.setHtml(html);
        where = edit.toPlainText();
        if (tag == "cover")
            if (html.contains("img src="))
                where = html;
        return true;
    }
    return false;
}

QString EPUB::fixImages(QString html) {
    int pos = 0;
    for (; ; ) {
        pos = html.indexOf("img src=", pos + 1);
        if (pos == -1) return html;
        QString filename = html.mid(pos + 9);
        QString start = html.left(pos + 9);
        int npos = filename.indexOf("\"");
        if (npos == -1) return html;
        QString rest = filename.mid(npos);
        filename = filename.left(npos);
        npos = filename.lastIndexOf("/");
        QString dir = _dir;
        if (npos != -1) {
            dir = filename.left(npos + 1);
            filename = filename.mid(npos + 1);
        }
        QString path = "images/";
        if (filename.right(3) != "jpg") filename += ".jpg";
        _images[dir + filename] = path + filename;
        html = start + path + filename + rest;
    }
}

void EPUB::sceneToDocument(QList<Chapter>& book, TextEdit& edit, const EPUB::Scene& scene) {
    if (!saveStringByTag(scene._tags, _cover, "cover", scene._html) &&
        !saveStringByTag(scene._tags, _author, "author", scene._html) &&
        !saveStringByTag(scene._tags, _rights, "rights", scene._html) &&
        !saveStringByTag(scene._tags, _language, "language", scene._html) &&
        !saveStringByTag(scene._tags, _publisher, "publisher", scene._html) &&
        !saveStringByTag(scene._tags, _id, "id", scene._html)) {
        TextEdit temp(_dir);
        if (recognizeTag(scene._tags, "trash")) return;
        else if (recognizeTag(scene._tags, "chapter")) {
            int last = book.length() - 1;
            if (last >= 0) book[last]._html = edit.toHtml();
            Chapter n(scene._name);
            book.append(n);
            edit.clear();
            temp.setHtml(scene._html);
        }
        else if (recognizeTag(scene._tags, "scene")) temp.setHtml(scene._html);
        temp.setHtml(fixImages(temp.toHtml()));
        QString html = temp.toHtml();
        edit.insertHtml(html);
        if (!temp.toPlainText().isEmpty()) edit.insertPlainText("\r\n");
    }

    for (const auto& scn: scene._children) sceneToDocument(book, edit, scn);
}

int EPUB::chapterNumWidth(const QList<Chapter>& book) {
    int start = _cover.isEmpty() ? 1 : 2;
    return (int) QString::asprintf("%lld", book.length() + start).length();
}

QString EPUB::chapterManifest(const QList<Chapter>& book) {
    QString manifest = "";
    int len = chapterNumWidth(book);
    for (int i = 1; i < book.length() + 1; ++i)
        manifest += QString::asprintf("        <item id=\"chapter%0*d\" href=\"chap%0*d.xhtml\" media-type=\"application/xhtml+xml\" />\n", len, i, len, i);
    return manifest;
}

QString EPUB::spineTOC(const QList<Chapter>& book) {
    QString spine;
    int len = chapterNumWidth(book);
    for (int i = 1; i < book.length() + 1; ++i) spine += QString::asprintf("        <itemref idref=\"chapter%0*d\" />\n", len, i);
    return spine;
}

QString EPUB::navPoints(const QList<Chapter>& book) {
    QString nav;
    int len = chapterNumWidth(book);
    int start = _cover.isEmpty() ? 1 : 2;
    for (int i = start; i < book.length() + start; ++i)
        nav += QString::asprintf("      <navPoint id=\"chapter%0*d\" playOrder=\"%d\">\n"
                                 "          <navLabel>\n"
                                 "              <text>%s</text>\n"
                                 "          </navLabel>\n"
                                 "          <content src=\"chap%0*d.xhtml\"/>\n"
                                 "      </navPoint>\n", len, i - (start - 1), i, book[i - start]._name.toStdString().c_str(), len, i - (start - 1));
    return nav;

}

QString EPUB::convertHTML(QString html, QString title) {
    html = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n" + html;
    int pos = html.indexOf("<!DOCTYPE");
    QString left = html.left(pos);
    html = html.right(html.length() - pos);
    pos = html.indexOf(">");
    html = left + "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\" \"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\">" + html.right(html.length() - pos - 1);
    pos = html.indexOf("<html>") + 5;
    html = html.left(pos) + " xmlns=\"http://www.w3.org/1999/xhtml\"" + html.right(html.length() - pos);
    pos = html.indexOf("<style ");
    int end = html.indexOf("</style>") + 8;
    html = html.left(pos) + html.right(html.length() - end);
    pos = html.indexOf("<head>") + 6;
    html = html.left(pos) + "<title>" + title + "</title>" + html.right(html.length() - pos);
    return html;
}

void EPUB::loadCover(const QString& name, Zippy::ZipEntryData& jpg)
{
    QString filename = name;
    if (name.left(2) == "<!") {
        int pos = name.indexOf("img src=");
        if (pos == -1) return;
        filename = name.mid(pos + 9);
        pos = filename.indexOf("\"");
        if (pos == -1) return;
        filename = filename.left(pos);
        QString path = _dir;
        pos = filename.lastIndexOf("/");
        if (pos != -1) {
            path = filename.left(pos + 1);
            filename = filename.mid(pos + 1);
        }
        if (path.isEmpty()) path += _dir;
        filename = path + filename;
        if (filename.right(3) != "jpg") filename += ".jpg";
    }
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) return;
    QByteArray data(file.readAll());
    for (const auto& x: data) jpg.emplace_back(x);
    file.close();
}

EPUB::EPUB(QString dir, QJsonObject obj) {
    if (dir == "") dir = "./";
    if (dir.right(1) != "/") dir += "/";
    _dir = dir;
    QList<Chapter> book;
    novelToBook(obj, book, _tree);

    QDate date;
    _year = QString::asprintf("%d", date.currentDate().year());

    // create the zip file from the book
    Zippy::ZipArchive arch;
    arch.Create((_dir + _name + ".epub").toStdString());
    arch.AddEntry("mimetype", "application/epub+zip");
    arch.AddEntry("META-INF/container.xml",
                  "<?xml version=\"1.0\"?>"
                  "<container xmlns=\"urn:oasis:names:tc:opendocument:xmlns:container\" version=\"1.0\">"
                  "  <rootfiles>"
                  "    <rootfile media-type=\"application/oebps-package+xml\" full-path=\"OEBPS/content.opf\"/>"
                  "  </rootfiles>"
                  "</container>");
    if (!_cover.isEmpty()) {
        Zippy::ZipEntryData jpg;
        loadCover(_cover, jpg);
        arch.AddEntry("OEBPS/images/Cover.jpg", jpg);
        arch.AddEntry("OEBPS/Cover.xhtml",
                      "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
                      "<html>\n"
                      "   <body>\n"
                      "     <img align=\"center\" height=\"100%\" src=\"images/Cover.jpg\"/><br/>&nbsp;\n"
                      "   </body>\n"
                      "</html>\n");
    }
    arch.AddEntry("OEBPS/page-template.xpgt",
                  "<ade:template xmlns=\"http://www.w3.org/1999/xhtml\" xmlns:ade=\"http://ns.adobe.com/2006/ade\"\n"
                  "         xmlns:fo=\"http://www.w3.org/1999/XSL/Format\">\n"
                  "  <fo:layout-master-set>\n"
                  "    <fo:simple-page-master master-name=\"single_column\">\n"
                  "        <fo:region-body margin-bottom=\"3pt\" margin-top=\"0.5em\" margin-left=\"3pt\" margin-right=\"3pt\"/>\n"
                  "    </fo:simple-page-master>\n"
                  "    <fo:simple-page-master master-name=\"single_column_head\">\n"
                  "        <fo:region-before extent=\"8.3em\"/>\n"
                  "        <fo:region-body margin-bottom=\"3pt\" margin-top=\"6em\" margin-left=\"3pt\" margin-right=\"3pt\"/>\n"
                  "    </fo:simple-page-master>\n"
                  "    <fo:simple-page-master master-name=\"two_column\" margin-bottom=\"0.5em\" margin-top=\"0.5em\" margin-left=\"0.5em\" margin-right=\"0.5em\">\n"
                  "        <fo:region-body column-count=\"2\" column-gap=\"10pt\"/>\n"
                  "    </fo:simple-page-master>\n"
                  "    <fo:simple-page-master master-name=\"two_column_head\" margin-bottom=\"0.5em\" margin-left=\"0.5em\" margin-right=\"0.5em\">\n"
                  "        <fo:region-before extent=\"8.3em\"/>\n"
                  "        <fo:region-body column-count=\"2\" margin-top=\"6em\" column-gap=\"10pt\"/>\n"
                  "    </fo:simple-page-master>\n"
                  "    <fo:simple-page-master master-name=\"three_column\" margin-bottom=\"0.5em\" margin-top=\"0.5em\" margin-left=\"0.5em\" margin-right=\"0.5em\">\n"
                  "        <fo:region-body column-count=\"3\" column-gap=\"10pt\"/>\n"
                  "    </fo:simple-page-master>\n"
                  "    <fo:simple-page-master master-name=\"three_column_head\" margin-bottom=\"0.5em\" margin-top=\"0.5em\" margin-left=\"0.5em\" margin-right=\"0.5em\">\n"
                  "        <fo:region-before extent=\"8.3em\"/>\n"
                  "        <fo:region-body column-count=\"3\" margin-top=\"6em\" column-gap=\"10pt\"/>\n"
                  "    </fo:simple-page-master>\n"
                  "    <fo:page-sequence-master>\n"
                  "        <fo:repeatable-page-master-alternatives>\n"
                  "            <fo:conditional-page-master-reference master-reference=\"three_column_head\" page-position=\"first\" ade:min-page-width=\"80em\"/>\n"
                  "            <fo:conditional-page-master-reference master-reference=\"three_column\" ade:min-page-width=\"80em\"/>\n"
                  "            <fo:conditional-page-master-reference master-reference=\"two_column_head\" page-position=\"first\" ade:min-page-width=\"50em\"/>\n"
                  "            <fo:conditional-page-master-reference master-reference=\"two_column\" ade:min-page-width=\"50em\"/>\n"
                  "            <fo:conditional-page-master-reference master-reference=\"single_column_head\" page-position=\"first\" />\n"
                  "            <fo:conditional-page-master-reference master-reference=\"single_column\"/>\n"
                  "        </fo:repeatable-page-master-alternatives>\n"
                  "    </fo:page-sequence-master>\n"
                  "  </fo:layout-master-set>\n"
                  "  <ade:style>\n"
                  "    <ade:styling-rule selector=\".title_box\" display=\"adobe-other-region\" adobe-region=\"xsl-region-before\"/>\n"
                  "  </ade:style>\n"
                  "</ade:template>\n");
    arch.AddEntry("OEBPS/stylesheet.css",
                  "/* Style Sheet */\n"
                  "/* This defines styles and classes used in the book */\n"
                  "body { margin-left: 5%; margin-right: 5%; margin-top: 5%; margin-bottom: 5%; text-align: justify; }\n"
                  "pre { font-size: x-small; }\n"
                  "h1 { text-align: center; }\n"
                  "h2 { text-align: center; }\n"
                  "h3 { text-align: center; }\n"
                  "h4 { text-align: center; }\n"
                  "h5 { text-align: center; }\n"
                  "h6 { text-align: center; }\n"
                  ".CI {\n"
                  "    text-align:center;\n"
                  "    margin-top:0px;\n"
                  "    margin-bottom:0px;\n"
                  "    padding:0px;\n"
                  "    }\n"
                  ".center   {text-align: center;}\n"
                  ".smcap    {font-variant: small-caps;}\n"
                  ".u        {text-decoration: underline;}\n"
                  ".bold     {font-weight: bold;}\n");
    if (_id.isEmpty()) _id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    arch.AddEntry("OEBPS/content.opf",
                  ("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n"
                   "<package xmlns=\"http://www.idpf.org/2007/opf\" unique-identifier=\"BookID\" version=\"2.0\" >\n"
                   "    <metadata xmlns:dc=\"http://purl.org/dc/elements/1.1/\" xmlns:opf=\"http://www.idpf.org/2007/opf\">\n"
                   "        <dc:title>" + _name + "</dc:title>\n"
                   "        <dc:creator opf:role=\"aut\">" + _author + "</dc:creator>\n"
                   "        <dc:language>" + _language + "</dc:language>\n"
                   "        <dc:rights>" + _rights + "</dc:rights>\n"
                   "        <dc:publisher>" + _publisher + "</dc:publisher>\n"
                   "        <dc:date>" + _year + "</dc:data>\n"
                   "        <dc:identifier id=\"BookID\" opf:scheme=\"UUID\">" + _id +"</dc:identifier>\n" +
                   (_cover.size() ? "        <meta name=\"cover\" content=\"images/Cover.jpg\" />\n" : "") +
                   "    </metadata>\n"
                   "    <manifest>\n" +
                   (_cover.size() ? "        <item id=\"cover_jpg\" href=\"images/Cover.jpg\" media-type=\"image/jpeg\" />" : "") +
                   "        <item id=\"ncx\" href=\"toc.ncx\" media-type=\"application/x-dtbncx+xml\" />\n"
                   "        <item id=\"style\" href=\"stylesheet.css\" media-type=\"text/css\" />\n"
                   "        <item id=\"pagetemplate\" href=\"page-template.xpgt\" media-type=\"application/vnd.adobe-page-template+xml\" />\n" +
                   (_cover.size() ? "        <item id=\"cover_html\" href=\"Cover.xhtml\" media-type=\"application/xhtml+xml\" />\n" : "") +
                   chapterManifest(book) + "\n"
                   "    </manifest>\n"
                   "    <spine toc=\"ncx\">\n" +
                   (_cover.size() ? "        <itemref idref=\"cover_html\" />\n" : "") +
                   spineTOC(book) +
                   "    </spine>\n"
                   "</package>").toStdString().c_str());
    arch.AddEntry("OEBPS/toc.ncx",
                  ("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                   "<ncx xmlns=\"http://www.daisy.org/z3986/2005/ncx/\" version=\"2005-1\">\n"
                   "   <head>\n"
                   "       <meta name=\"dtb:uid\" content=\"" + _id + "\"/>\n"
                   "       <meta name=\"dtb:depth\" content=\"1\"/>\n"
                   "       <meta name=\"dtb:totalPageCount\" content=\"0\"/>\n"
                   "       <meta name=\"dtb:maxPageNumber\" content=\"0\"/>\n"
                   "   </head>\n"
                   "   <docTitle>\n"
                   "       <text>" + _name + "</text>\n"
                   "   </docTitle>\n"
                   "   <navMap>\n" +
                   (_cover.size() ?
                   "      <navPoint id=\"cover_html\" playOrder=\"1\">\n"
                   "          <navLabel>\n"
                   "              <text>Cover</text>\n"
                   "          </navLabel>\n"
                   "          <content src=\"Cover.xhtml\"/>\n"
                   "      </navPoint>\n" : "") +
                   navPoints(book) +
                   "   </navMap>\n"
                   "</ncx>").toStdString().c_str());
    int len = chapterNumWidth(book);
    for (int i = 1; i <= book.length(); ++i)
        arch.AddEntry(QString::asprintf("OEBPS/chap%0*d.xhtml", len, i).toStdString().c_str(), convertHTML(book[i - 1]._html, book[i - 1]._name).toStdString().c_str());
    for (auto i = _images.begin(); i != _images.end(); ++i) {
        Zippy::ZipEntryData jpg;
        QFile file(i.key());
        if (!file.open(QIODevice::ReadOnly)) continue;
        QByteArray data(file.readAll());
        for (const auto& x: data) jpg.emplace_back(x);
        file.close();
        arch.AddEntry(QString::asprintf("OEBPS/%s", i.value().toStdString().c_str()).toStdString().c_str(), jpg);
    }
    arch.Save();
    arch.Close();
}
