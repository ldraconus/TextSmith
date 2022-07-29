#include <QJsonArray>
#include <QJsonObject>

#include "TextEdit.h"
#include "text.h"

xTEXT::Scene xTEXT::objectToScene(const QJsonObject& obj)
{
    xTEXT::Scene scene;
    scene._html = obj["doc"].toString("");
    scene._name = obj["name"].toString("");
    const QJsonArray& tags = obj["tags"].toArray();
    for (auto tag: tags) scene._tags.append(tag.toString("").toLower());
    return scene;
}

xTEXT::Scene xTEXT::objectToItem(const QJsonObject& obj) {
    xTEXT::Scene scene = objectToScene(obj);
    const QJsonArray& children = obj["children"].toArray();
    for (auto child: children) scene._children.append(objectToItem(child.toObject()));
    return scene;
}

bool xTEXT::processCharacters(QString& para, QString& text) {
    int pos = text.indexOf("<");
    if (pos == -1) return false;
    QString tmp = text.left(pos);
    para += tmp;
    text = text.mid(pos);

    if (text.left(13) == "<span style=\"") {
        pos = text.indexOf("\">");
        text = text.mid(pos + 2);
        return true;
    }
    else if (text.left(7) == "</span>") {
        text = text.mid(7);
        return true;
    }

    return false;
}

void xTEXT::processAlignment(QString style) {
    ALIGNMENT type = LEFT;

    _align = _alignment;

    int pos = style.indexOf("align=\"");
    if (pos == -1) return;
    QString align = style.mid(pos + 7);
    pos = align.indexOf("\"");
    if (pos == -1) return;
    align = align.left(pos).toUpper();

    if (align == "CENTER") type = CENTER;
    else if (align == "RIGHT") type = RIGHT;
    else if (align == "JUSTIFY") type = JUSTIFY;

    _alignment = type;

    _indent = style.indexOf("-qt-block-indent:1") != -1;
}

QString xTEXT::formatParagraph(ALIGNMENT align, QString& text) {
    QString para;

    QStringList words = text.split(" ");
    QString line = "     ";
    switch (align) {
    case LEFT:
    {
        if (_indent) line += "     ";
        for (const auto& word: words) {
            if ((line + " " + word).count() > 72) {
                para += line + "\n";
                line = (_indent ? "     " : "") + word;
            } else line += " " + word;
        }
        para += line;
        break;
    }
    case CENTER:
    {
        if (_indent) line += "     ";
        for (const auto& word: words) {
            if ((line + " " + word).count() > 72) {
                int spaces = (72 - line.count()) / 2;
                while (spaces--) line = " " + line;
                para += line + "\n";
                line = (_indent ? "     " : "") + word;
            } else line += " " + word;
        }
        int spaces = (72 - line.count()) / 2;
        while (spaces--) line = " " + line;
        para += line;
        break;
    }
    case RIGHT:
    {
        if (_indent) line += "     ";
        for (const auto& word: words) {
            if ((line + " " + word).count() > 72) {
                int spaces = 72 - line.count();
                while (spaces--) line = " " + line;
                para += line + "\n";
                line = (_indent ? "     " : "") + word;
            } else line += " " + word;
        }
        int spaces = 72 - line.count();
        while (spaces--) line = " " + line;
        para += line;
        break;
    }
    case JUSTIFY:
    {
        line += _indent ? "     " : "";
        int len = line.count();
        QStringList wordsInLine;
        for (const auto& word: words) {
            if (len + 1 + word.count() > 72) {
                QStringList gaps;
                int numGaps = wordsInLine.count() - 1;
                int gapSize = (72 - len) / wordsInLine.count() + 1;
                QString gap = "";
                for (int i = 0; i < gapSize; ++i) gap += " ";
                for (int i = 0; i < numGaps; ++i) gaps.append(gap);
                int extraSpaces = (72 - len - (numGaps * (gapSize - 1)));
                int left = 0;
                int right = numGaps;
                for (int i = 0; i < extraSpaces; ++i) {
                    if (i % 2) {
                        gaps[left++] += " ";
                        if (left == numGaps) left = 0;
                    } else {
                        gaps[--right] += " ";
                        if (right == 0) right = numGaps;
                    }
                }
                for (int i = 0; i < numGaps; ++i) line += wordsInLine[i] + gaps[i];
                line += wordsInLine[numGaps];
                para += line + "\n";
                line = _indent ? "     " : "";
                len = line.count();
                wordsInLine.clear();
                wordsInLine.append(word);
            } else {
                wordsInLine.append(word);
                len += 1 + word.count();
            }
        }
        for (int i = 0; i < wordsInLine.count(); ++i) line += wordsInLine[i] + " ";
        para += line;
        break;
    }
    }

    return para + "\n";
}

bool xTEXT::processParagraph(QString& html) {
    QString para;
    // strip out to just past '<p '
    int pos = html.indexOf("<p ", 0, Qt::CaseInsensitive);
    if (pos == -1) return false;
    html = html.mid(pos + 3);
    pos = html.indexOf(">");
    if (pos == -1) return false;
    QString style = html.left(pos);
    html = html.mid(pos + 1);

    processAlignment(style);

    pos = html.indexOf("</p>", 0, Qt::CaseInsensitive);
    if (pos == -1) return false;
    QString text = html.left(pos);
    html = html.mid(pos + 4);

    while (processCharacters(para, text))
        ;
    para += text;

    _out << formatParagraph(_alignment, para);

    _alignment = LEFT;

    return true;
}

void xTEXT::sceneToTXT(QString html) {
    // strip out to just past '<body '
    int pos = html.indexOf("<body ", 0, Qt::CaseInsensitive);
    if (pos == -1) return;
    html = html.mid(pos + 6);
    pos = html.indexOf(">");
    if (pos == -1) return;
    html = html.mid(pos + 1);

    // strip out everything starting with </body>
    pos = html.indexOf("</body>", 0, Qt::CaseInsensitive);
    if (pos == -1) return;
    html = html.left(pos);

    while (processParagraph(html))
        ;
}
void xTEXT::sceneToTXT(xTEXT::Scene scene) {
    enum { NONE, COVER, CHAPTER, SCENE, TRASH } type = NONE;
    for (const auto& tag: scene._tags) {
        if (tag == "cover") type = COVER;
        else if (tag == "chapter") type = CHAPTER;
        else if (tag == "trash") type = TRASH;
        else if (tag == "scene") type = SCENE;
    }
    if (type == COVER || type == TRASH) return;

    if (type == CHAPTER) _out << "\n\n\n\n\n\n\n\n\n\n";

    if (type != NONE) sceneToTXT(scene._html);
    for (auto& child: scene._children) sceneToTXT(child);
}

void xTEXT::novelToBook(QJsonObject obj, Tree& tree)
{
    const QJsonObject& doc = obj["document"].toObject();
    const QJsonObject& root = doc["root"].toObject();
    tree._top = objectToItem(root);

    _file.setFileName(_dir + _tree._top._name + ".txt");
    _file.open(QFile::WriteOnly | QFile::Text);
    _out.setDevice(&_file);
}


xTEXT::xTEXT(QString dir, QJsonObject obj) {
    if (dir == "") dir = "./";

    // Create new TEXT document
    novelToBook(obj, _tree);
    sceneToTXT(_tree._top);
    _file.close();
}
