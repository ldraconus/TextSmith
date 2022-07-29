#include "fullscreen.h"
#include "mainwindow.h"
#include "ui_fullscreen.h"

#include <QClipboard>
#include <QKeyCombination>
#include <QKeyEvent>
#include <QMimeData>

FullScreen* FullScreen::_fullScreen = nullptr;
QSoundEffect* FullScreen::_keySound = nullptr;
QSoundEffect* FullScreen::_spaceSound = nullptr;

FullScreen::FullScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FullScreen) {
    ui->setupUi(this);
    showFullScreen();
    if (_keySound == nullptr) {
        _keySound = new QSoundEffect;
        _keySound->setSource(QUrl("qrc:/fx/typewriter-hit.wav"));
        _keySound->setVolume(0.5);
        _keySound->setLoopCount(1);
    }
    if (_spaceSound == nullptr) {
        _spaceSound = new QSoundEffect;
        _spaceSound->setSource(QUrl("qrc:/fx/spacebar.wav"));
        _spaceSound->setVolume(0.5);
        _spaceSound->setLoopCount(1);
    }
    connect(ui->textEdit, SIGNAL(textChanged()), SLOT(textChanged()));
}

FullScreen::~FullScreen() {
    delete ui;
}

void FullScreen::dir(QString d) {
    _dir = d;
    ui->textEdit->setDir(d);
}
QList<int> FullScreen::sizes() {
    return ui->splitter->sizes();
}

void FullScreen::setSizes(QList<int> sz) {
    ui->splitter->setSizes(sz);
}

void FullScreen::setText(QString x) {
    ui->textEdit->setHtml(x);
    _dirty = false;
}

void FullScreen::bold() {
    QTextEdit* text = ui->textEdit;
    QTextCursor cursor = text->textCursor();
    QTextCharFormat is = cursor.charFormat();
    QTextCharFormat fmt;
    fmt.setFontWeight(is.fontWeight() != QFont::Bold ? QFont::Bold : QFont::Normal);
    cursor.mergeCharFormat(fmt);
    text->mergeCurrentCharFormat(fmt);
    _dirty = true;
}

void FullScreen::centerJustify() {
    ui->textEdit->setAlignment(Qt::AlignCenter);
    _dirty = true;
}

void FullScreen::copy() {
    ui->textEdit->copy();
}

void FullScreen::cut() {
    ui->textEdit->cut();
    _dirty = true;
}

int FullScreen::cursor() {
    auto c = ui->textEdit->textCursor();
    return c.anchor();
}

void FullScreen::leftJustify() {
    ui->textEdit->setAlignment(Qt::AlignLeft);
    _dirty = true;
}

void FullScreen::fullJustify() {
    ui->textEdit->setAlignment(Qt::AlignJustify);
    _dirty = true;
}

void FullScreen::indent() {
    QTextEdit* text = ui->textEdit;
    QTextCursor cursor = text->textCursor();
    QTextBlockFormat blk = cursor.blockFormat();
    int indent = blk.indent();
    if (indent == 0) blk.setIndent(indent + 1);
    else blk.setIndent(indent - 1);
    cursor.setBlockFormat(blk);
    text->setTextCursor(cursor);
    _dirty = true;
}

void FullScreen::italic() {
    QTextEdit* text = ui->textEdit;
    QTextCursor cursor = text->textCursor();
    QTextCharFormat is = cursor.charFormat();
    QTextCharFormat fmt;
    fmt.setFontItalic(!is.fontItalic());
    cursor.mergeCharFormat(fmt);
    text->mergeCurrentCharFormat(fmt);
    _dirty = true;
}

void FullScreen::paste() {
    TextEdit text(MainWindow::main_window()->dir());
    if (text.canPaste()) {
        TextEdit* edit = ui->textEdit;
        const QClipboard* cb = QApplication::clipboard();
        const QMimeData* md = cb->mimeData();
        if (md->hasText()) {
            text.paste();
            QString txt = text.document()->toPlainText();
            edit->insertPlainText(txt);
        }
        else if (md->hasImage()) edit->paste();
        _dirty = true;
    }
}

void FullScreen::rightJustify() {
    ui->textEdit->setAlignment(Qt::AlignRight);
    _dirty = true;
}

void FullScreen::save() {
    MainWindow* mw = MainWindow::main_window();
    mw->syncFullScreen(*this);
    mw->save();
    _dirty = false;
}

void FullScreen::setCursor(int x) {
    auto c = ui->textEdit->textCursor();
    c.setPosition(x);
    ui->textEdit->setTextCursor(c);
}

QString FullScreen::text() {
    return ui->textEdit->toHtml();
}

void FullScreen::textChanged() {
    _dirty = true;
}

void FullScreen::underline() {
    QTextEdit* text = ui->textEdit;
    QTextCursor cursor = text->textCursor();
    QTextCharFormat is = cursor.charFormat();
    QTextCharFormat fmt;
    fmt.setFontUnderline(!is.fontUnderline());
    cursor.mergeCharFormat(fmt);
    text->mergeCurrentCharFormat(fmt);
    _dirty = true;
}

void FullScreen::keyReleaseEvent(QKeyEvent* e) {
    static QKeyCombination Bold(Qt::CTRL, Qt::Key_B);
    static QKeyCombination CenterJustify(Qt::CTRL, Qt::Key_E);
    static QKeyCombination Copy(Qt::CTRL, Qt::Key_C);
    static QKeyCombination Cut(Qt::CTRL, Qt::Key_X);
    static QKeyCombination Esc(Qt::Key_Escape);
    static QKeyCombination FullJustify(Qt::CTRL, Qt::Key_J);
    static QKeyCombination Indent(Qt::CTRL, Qt::Key_Tab);
    static QKeyCombination Italic(Qt::CTRL, Qt::Key_I);
    static QKeyCombination LeftJustify(Qt::CTRL, Qt::Key_L);
    static QKeyCombination Paste(Qt::CTRL, Qt::Key_V);
    static QKeyCombination RightJustify(Qt::CTRL, Qt::Key_R);
    static QKeyCombination Save(Qt::CTRL, Qt::Key_S);
    static QKeyCombination Underline(Qt::CTRL, Qt::Key_U);

    if (e->keyCombination() == Bold) bold();
    else if (e->keyCombination() == CenterJustify) centerJustify();
    else if (e->keyCombination() == Copy) copy();
    else if (e->keyCombination() == Cut) cut();
    else if (e->keyCombination() == Esc) close();
    else if (e->keyCombination() == FullJustify) fullJustify();
    else if (e->keyCombination() == Indent) indent();
    else if (e->keyCombination() == Italic) italic();
    else if (e->keyCombination() == LeftJustify) leftJustify();
    else if (e->keyCombination() == Paste) paste();
    else if (e->keyCombination() == RightJustify) rightJustify();
    else if (e->keyCombination() == Save) save();
    else if (e->keyCombination() == Underline) underline();
    else {
        if (MainWindow::main_window()->typewriterSounds())
            if (e->modifiers() == Qt::NoModifier ||
                e->modifiers() == Qt::ShiftModifier) {
                if (e->key() == Qt::Key_Space) _spaceSound->play();
                else if (e->key() != Qt::Key_Shift && e->key() != Qt::Key_Control && e->key() != Qt::Key_Alt && e->key() != Qt::Key_Meta &&
                         e->key() != Qt::Key_Delete && e->key() != Qt::Key_Backspace && e->key() != Qt::Key_Enter && e->key() != Qt::Key_Return && e->key() != Qt::Key_Escape &&
                         e->key() != Qt::Key_Home && e->key() != Qt::Key_End && e->key() != Qt::Key_PageUp && e->key() != Qt::Key_PageDown && e->key() != Qt::Key_Insert &&
                         e->key() != Qt::Key_Print && e->key() != Qt::Key_ScrollLock && e->key() != Qt::Key_Pause && e->key() != Qt::Key_VolumeUp && e->key() != Qt::Key_VolumeDown &&
                         e->key() != Qt::Key_VolumeMute && e->key() != Qt::Key_CapsLock && e->key() != Qt::Key_NumLock && e->key() != Qt::Key_Calculator && e->key() != Qt::Key_Explorer &&
                         e->key() != Qt::Key_KeyboardBrightnessDown && e->key() != Qt::Key_KeyboardBrightnessUp && e->key() != Qt::Key_Find && e->key() != Qt::Key_AudioRewind &&
                         e->key() != Qt::Key_AudioForward &&  e->key() != Qt::Key_MediaPlay && e->key() != Qt::Key_MediaPause && e->key() != Qt::Key_Display && e->key() != Qt::Key_F1 &&
                         e->key() != Qt::Key_F1 && e->key() != Qt::Key_F2 && e->key() != Qt::Key_F3 && e->key() != Qt::Key_F4 && e->key() != Qt::Key_F5 && e->key() != Qt::Key_F6 &&
                         e->key() != Qt::Key_F7 && e->key() != Qt::Key_F8 && e->key() != Qt::Key_F9 && e->key() != Qt::Key_F10 && e->key() != Qt::Key_F11 && e->key() != Qt::Key_F12 &&
                         e->key() != Qt::Key_Left && e->key() != Qt::Key_Right && e->key() != Qt::Key_Up && e->key() != Qt::Key_Down) _keySound->play();
            }
        e->ignore();
    }
}
