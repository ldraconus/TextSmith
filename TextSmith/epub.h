#ifndef EPUB_H
#define EPUB_H

#include "mainwindow.h"
#include "TextEdit.h"
#include "Zippy/Zippy.hpp"

#include <QJsonObject>

class EPUB {
private:
    struct Scene {
        QList<QString> _tags;
        QString _html;
        QString _name;
        QList<struct Scene> _children;

        Scene(): _html(""), _name("") { }
        Scene(const Scene& s): _tags(s._tags), _html(s._html), _name(s._name), _children(s._children) { }

        Scene& operator=(const Scene& s) { if (this != &s) { _tags = s._tags; _html = s._html; _name = s._name; _children = s._children; } return *this; }
    };

    struct Tree {
        Scene _top;
    };

    struct Chapter {
        QString _name;
        QString _html;
        Chapter(): _name(""), _html("") { }
        Chapter(const QString& n): _name(n), _html("") { }
        Chapter(const Chapter& c): _name(c._name), _html(c._html) { }

        Chapter& operator=(const Chapter& c) { if (this != &c) { _name = c._name; _html = c._html; } return *this; }
    };

    Tree _tree;
    QString _name;
    QString _dir;
    QString _cover = "";
    QString _author = "Anonymous";
    QString _rights = "Public Domain";
    QString _language = "en-US";
    QString _publisher = "Independent";
    QString _id = "";
    QString _year = "";
    QMap<QString, QString> _images;

    QString chapterManifest(const QList<Chapter>& book);
    QString convertHTML(QString html, QString title);
    QString fixImages(QString html);
    QString navPoints(const QList<Chapter>& book);
    QString spineTOC(const QList<Chapter>& book);
    Scene objectToItem(const QJsonObject& obj);
    Scene objectToScene(const QJsonObject& obj);
    bool allWS(QString x);
    bool recognizeTag(const QList<QString>& tags, const QString& tag);
    bool saveStringByTag(const QList<QString>& tags, QString& where, QString tag, const QString& html);
    int chapterNumWidth(const QList<Chapter>& book);
    void loadCover(const QString& name, Zippy::ZipEntryData& jpg);
    void novelToBook(QJsonObject json, QList<Chapter>& book, Tree& tree);
    void sceneToDocument(QList<Chapter>& book, TextEdit& edit, const EPUB::Scene& scene);

public:
    EPUB(QString dir, QJsonObject json);
};

#endif // EPUB_H
