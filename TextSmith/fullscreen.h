#ifndef FULLSCREEN_H
#define FULLSCREEN_H

#include <QDialog>
#include <QtMultimedia/QSoundEffect>

namespace Ui {
class FullScreen;
}

class FullScreen : public QDialog {
    Q_OBJECT

public:
    explicit FullScreen(QWidget *parent = nullptr);
    ~FullScreen();

    static FullScreen* fullscreen() { return _fullScreen; }

    bool dirty() { return _dirty; }
    void clean() { _dirty = false; }
    void dir(QString d);

    QList<int> sizes();
    int cursor();
    void bold();
    void centerJustify();
    void copy();
    void cut();
    void fullJustify();
    void indent();
    void italic();
    void leftJustify();
    void paste();
    void rightJustify();
    void save();
    void setCursor(int x);
    void setSizes(QList<int> sz);
    void setText(QString txt);
    void underline();
    QString text();

    void keyReleaseEvent(QKeyEvent* e) override;

    static QSoundEffect* _keySound;
    static QSoundEffect* _spaceSound;

private:
    Ui::FullScreen *ui;

    bool _dirty = false;
    QString _dir = "./";

    static FullScreen* _fullScreen;

public slots:
    void textChanged();
};

#endif // FULLSCREEN_H
