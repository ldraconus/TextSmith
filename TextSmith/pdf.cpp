#include "pdf.h"

#include <QJsonArray>
#include <QTextDocumentFragment>
#include <QtPrintSupport/QPrinter>

PDF::Scene PDF::objectToScene(const QJsonObject& obj)
{
    PDF::Scene scene;
    scene._html = obj["doc"].toString("");
    scene._name = obj["name"].toString("");
    const QJsonArray& tags = obj["tags"].toArray();
    for (auto tag: tags) scene._tags.append(tag.toString("").toLower());
    return scene;
}

PDF::Scene PDF::objectToItem(const QJsonObject& obj)
{
    PDF::Scene scene = objectToScene(obj);
    const QJsonArray& children = obj["children"].toArray();
    for (auto child: children) scene._children.append(objectToItem(child.toObject()));
    return scene;
}

bool PDF::recognizeTag(const QList<QString>& tags, const QString& tag) {
    return tags.indexOf(tag) != -1;
}

bool PDF::saveStringByTag(const QList<QString>& tags, QString& where, QString tag, const QString& html) {
    if (recognizeTag(tags, tag)) {
        QTextEdit edit;
        edit.setHtml(html);
        where = edit.toPlainText();
        if (tag == "cover")
            if (html.contains("img src="))
                where = html;
        return true;
    }
    return false;
}

QString PDF::fixImages(QString html) {
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
        QString path = _dir;
        npos = filename.lastIndexOf("/");
        if (npos != -1) {
            path = filename.left(npos + 1);
            filename = filename.mid(npos + 1);
        }
        if (path.isEmpty()) path += "./";
        filename = path + filename;
        if (filename.right(3) != "jpg") filename += ".jpg";
        html = start + filename + rest;
    }
}

void PDF::sceneToDocument(TextEdit& edit, const PDF::Scene& scene) {
    QTextEdit temp;
    if (!saveStringByTag(scene._tags, _cover, "cover", scene._html)) {
        if (recognizeTag(scene._tags, "trash")) return;
        else if (recognizeTag(scene._tags, "chapter")) {
            QTextBlockFormat blockFormat;
            blockFormat.setPageBreakPolicy(QTextFormat::PageBreak_AlwaysAfter);
            if (!_firstChapter) edit.textCursor().insertBlock(blockFormat);
            else _firstChapter = false;
            temp.setHtml(scene._html);
        }
        else if (recognizeTag(scene._tags, "scene")) temp.setHtml(scene._html);
        temp.setHtml(fixImages(temp.toHtml()));
        QString html = temp.toHtml();
        edit.insertHtml(html);
        if (!temp.toPlainText().isEmpty()) edit.insertPlainText("\r\n");
    }
    for (const auto& scn: scene._children) sceneToDocument(edit, scn);
}

void PDF::novelToBook(QJsonObject obj, TextEdit& edit, Tree& tree, QPageSize pgsz, int res)
{
    const QJsonObject& doc = obj["document"].toObject();
    const QJsonObject& root = doc["root"].toObject();
    tree._top = objectToItem(root);

    sceneToDocument(edit, tree._top);

    if (_cover.isEmpty()) return;

    QString filename = _cover;
    if (_cover.left(2) == "<!") {
        int pos = _cover.indexOf("img src=");
        if (pos == -1) return;
        filename = _cover.mid(pos + 9);
        pos = filename.indexOf("\"");
        if (pos == -1) return;
        filename = filename.left(pos);
        QString path = _dir;
        pos = filename.lastIndexOf("/");
        if (pos != -1) {
            path = filename.left(pos + 1);
            filename = filename.mid(pos + 1);
            if (_dir != path) {
                QFile::copy(path + filename, _dir + filename);
                QImage img(_dir + filename);
                QSize sz = pgsz.sizePixels(res);
                QImage scaled = img.scaled(sz, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                QImageWriter writer(_dir + filename, "jpg");
                writer.write(scaled);
            }
            path = "";
        }
        if (path.isEmpty()) path = _dir;
        filename = path + filename;
        if (filename.right(3) != "jpg") filename += ".jpg";
    }
    QTextCursor c = edit.textCursor();
    c.setPosition(0);
    edit.setTextCursor(c);
    edit.insertFromFile(filename);
    edit.insertPlainText("\n\n");
}

PDF::PDF(QString dir, QJsonObject obj)
{
    if (dir == "") dir = "./";
    if (dir.right(1) != "/") dir += "/";
    _dir = dir;
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);

    TextEdit book(_dir);
    novelToBook(obj, book, _tree, printer.pageLayout().pageSize(), printer.resolution());
    if (dir == "") dir = "./";
    printer.setOutputFileName(dir + _tree._top._name + ".pdf");

    QTextDocument* document = book.document();
    document->print(&printer);
}
