#ifndef HTML_H
#define HTML_H

#include "mainwindow.h"
#include "TextEdit.h"

class HTML {
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

    QString _cover;
    QString _dir;
    Tree _tree;
    bool _firstChapter = true;

    QString fixImages(QString html);
    Scene objectToItem(const QJsonObject& obj);
    Scene objectToScene(const QJsonObject& obj);
    bool recognizeTag(const QList<QString>& tags, const QString& tag);
    bool saveStringByTag(const QList<QString>& tags, QString& where, QString tag, const QString& html);
    void novelToBook(QJsonObject obj, TextEdit& edit, Tree& tree);
    void sceneToDocument(TextEdit& edit, const HTML::Scene& scene);

public:
    HTML(QString dir, QJsonObject obj);
};

#endif // HTML_H
