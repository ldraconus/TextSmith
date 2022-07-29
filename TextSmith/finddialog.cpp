#include "finddialog.h"
#include "mainwindow.h"
#include "ui_finddialog.h"
#include <QRadioButton>
#include <QDialogButtonBox>
#include <QPushButton>

FindDialog::FindDialog(bool selection, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindDialog)
{
    ui->setupUi(this);
    QRadioButton* select = ui->selectionRadioButton;
    QRadioButton* scene = ui->sceneRadioButton;
    select->setEnabled(selection);
    if (selection) select->setChecked(true);
    else scene->setChecked(true);
    QDialogButtonBox* box = ui->buttonBox;
    QPushButton* ok = box->button(QDialogButtonBox::StandardButton::Ok);
    ok->setEnabled(false);

    connect(ui->lineEdit, SIGNAL(textChanged(QString)), SLOT(changedText(QString)));
}

FindDialog::~FindDialog()
{
    delete ui;
}

SearchType FindDialog::getType()
{
    if (ui->selectionRadioButton->isChecked()) return bySelection;
    if (ui->sceneRadioButton->isChecked()) return byScene;
    if (ui->childrenRadioButton->isChecked()) return bySceneChildren;
    if (ui->siblingsRadioButton->isChecked()) return bySiblingChildren;
    return byAll;
}

QString FindDialog::getSearchString()
{
    return ui->lineEdit->text();
}

void FindDialog::setSearchString(QString x)
{
    ui->lineEdit->setText(x);
}

void FindDialog::changedText(QString text)
{
    QDialogButtonBox* box = ui->buttonBox;
    QPushButton* ok = box->button(QDialogButtonBox::StandardButton::Ok);
    ok->setEnabled(!text.isEmpty());
}
