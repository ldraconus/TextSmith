#ifndef TEXT_H
#define TEXT_H

#include <QFile>
#include <QObject>
#include <QTextStream>

class xTEXT {
private:
    struct Scene {
        QList<QString> _tags;
        QString _html;
        QString _name;
        QList<struct Scene> _children;

        Scene(): _html("") { }
        Scene(const Scene& s): _tags(s._tags), _html(s._html), _name(s._name), _children(s._children) { }

        Scene& operator=(const Scene& s) { if (this != &s) { _tags = s._tags; _html = s._html; _name = s._name; _children = s._children; } return *this; }
    };

    struct Tree {
        Scene _top;
    };

    QFile _file;
    QString _dir;
    QTextStream _out;
    Tree _tree;
    bool _indent;

    enum ALIGNMENT { LEFT, CENTER, RIGHT, JUSTIFY };

    ALIGNMENT _align;
    ALIGNMENT _alignment = LEFT;

    QString formatParagraph(ALIGNMENT align, QString& text);
    Scene objectToItem(const QJsonObject& obj);
    Scene objectToScene(const QJsonObject& obj);
    bool processCharacters(QString& para, QString& text);
    bool processParagraph(QString& html);
    void novelToBook(QJsonObject obj, Tree& tree);
    void processAlignment(QString style);
    void sceneToTXT(QString html);
    void sceneToTXT(xTEXT::Scene scene);

public:
    xTEXT(QString dir, QJsonObject obj);
};

#endif // TEXT_H
