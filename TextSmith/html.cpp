#include "html.h"

#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QStandardPaths>
#include <QTextStream>

HTML::Scene HTML::objectToScene(const QJsonObject& obj)
{
    HTML::Scene scene;
    scene._html = obj["doc"].toString("");
    scene._name = obj["name"].toString("");
    const QJsonArray& tags = obj["tags"].toArray();
    for (auto tag: tags) scene._tags.append(tag.toString("").toLower());
    return scene;
}

HTML::Scene HTML::objectToItem(const QJsonObject& obj)
{
    HTML::Scene scene = objectToScene(obj);
    const QJsonArray& children = obj["children"].toArray();
    for (auto child: children) scene._children.append(objectToItem(child.toObject()));
    return scene;
}

bool HTML::recognizeTag(const QList<QString>& tags, const QString& tag) {
    return tags.indexOf(tag) != -1;
}

bool HTML::saveStringByTag(const QList<QString>& tags, QString& where, QString tag, const QString& html) {
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

QString HTML::fixImages(QString html) {
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
        QString ext = filename.right(4).toLower();
        if (ext != ".jpg" && ext != ".gif" && ext != ".png") ext = ".jpg";
        else ext = "";
        npos = filename.lastIndexOf("/");
        QString path = _dir;
        if (npos != -1) {
            path = filename.left(npos + 1);
            filename = filename.mid(npos + 1);
            QFile::copy(path + filename, _dir + filename + ext);
            path = "";
        } else {
            path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
            if (path.right(1) != "/") path += "/";
            QFile::copy(path + filename + ext, _dir + filename + ext);
            path = "";
        }
        filename += ext;
        if (path.isEmpty()) path += "./";
        filename = path + filename;
        html = start + filename + rest;
    }
}

void HTML::sceneToDocument(TextEdit& edit, const HTML::Scene& scene) {
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
        edit.insertHtml(fixImages(temp.toHtml()));
        if (!temp.toPlainText().isEmpty()) edit.insertPlainText("\r\n");
    }
    for (const auto& scn: scene._children) sceneToDocument(edit, scn);
}

void HTML::novelToBook(QJsonObject obj, TextEdit& edit, Tree& tree)
{
    const QJsonObject& doc = obj["document"].toObject();
    const QJsonObject& root = doc["root"].toObject();
    tree._top = objectToItem(root);

    sceneToDocument(edit, tree._top);

    if (!_cover.isEmpty()) {
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
                if (_dir != path) QFile::copy(path + filename, _dir + filename);
                path = "";
            }
            if (path.isEmpty()) path = _dir;
            filename = path + filename.left(pos);
            if (filename.right(3) != "jpg") filename += ".jpg";
        }
        QTextCursor c = edit.textCursor();
        c.setPosition(0);
        edit.setTextCursor(c);
        edit.insertFromFile(filename);
        edit.insertPlainText("\n\n");
    }
}

HTML::HTML(QString dir, QJsonObject obj)
{
    if (dir == "") dir = "./";
    if (dir.right(1) != "/") dir += "/";
    _dir = dir;
    TextEdit book(_dir);
    novelToBook(obj, book, _tree);

    QFile file(dir + _tree._top._name + ".html");
    file.open(QFile::WriteOnly);
    QTextStream out(&file);
    out << book.toHtml();
    file.close();
}
