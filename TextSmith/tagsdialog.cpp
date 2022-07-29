#include "tagsdialog.h"
#include "ui_tagsdialog.h"
#include "mainwindow.h"

#include <QKeyEvent>
#include <QPushButton>

TagsDialog::TagsDialog(Scene& s, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TagsDialog),
    _scene(&s) {
    ui->setupUi(this);

    QRect d = MainWindow::main_window()->_tagsDialog;
    QRect pos = geometry();
    int width = pos.width();
    int height = pos.height();
    if (d.top() >= 0) {
        pos.setTop(d.top());
        if (d.left() >= 0) pos.setLeft(d.left());
        pos.setWidth(width);
        pos.setHeight(height);
        setGeometry(pos);
    }

    connect(ui->lineEdit_2, SIGNAL(returnPressed()),             SLOT(returnPressedAction()));
    connect(ui->lineEdit,   SIGNAL(textChanged(const QString&)), SLOT(textChangedAction(const QString&)));

    ui->lineEdit->setText(_scene->name());
    addTags(_scene->tags());
}

TagsDialog::~TagsDialog() {
    delete ui;
}

void TagsDialog::addTagButton(int i, const QString& tag) {
    QFrame* edit = ui->frame;
    QPushButton *button = new QPushButton(tag, edit);
    button->setCheckable(true);

    int x = (i % 3) * button->geometry().width() + (i % 3 + 1) * 6;
    int y = (i / 3) * button->geometry().height() + (i / 3 + 1) * 6;
    QRect g = button->geometry();
    g.setX(x);
    g.setY(y);
    button->setGeometry(g.x(), g.y(), g.x() + g.width(), g.y() + g.height());

    connect(button, SIGNAL(clicked()), this, SLOT(buttonClickedAction()));
    _buttons.append(button);
    button->setEnabled(true);
    button->setVisible(true);
    repaint();
}

void TagsDialog::addTags(const QList<QString>& tags) {
    int i = 0;
    for (auto x: tags) addTagButton(i++, x);
}

void TagsDialog::buttonClickedAction() {
    for (auto x: _buttons) {
        if (x->isChecked()) {
            QString tag = x->text();
            _scene->tags().removeOne(tag);
        }
    }

    for (auto x: _buttons) delete x;
    _buttons.clear();

    addTags(_scene->tags());
}

void TagsDialog::returnPressedAction() {
    QLineEdit* edit = findChild<QLineEdit*>("lineEdit_2");
    QString text = edit->text();
    if (text == "") return;

    edit->setText("");

    if (_scene->tags().indexOf(text) != -1) return;

    _scene->tags().append(text);
    for (auto x: _buttons) delete x;
    _buttons.clear();

    addTags(_scene->tags());
}

void TagsDialog::textChangedAction(const QString& text) {
    _scene->name(text);
}

void TagsDialog::keyPressEvent(QKeyEvent* e) {
    if (e->key() == Qt::Key_Return) return;
    QDialog::keyPressEvent(e);
}
