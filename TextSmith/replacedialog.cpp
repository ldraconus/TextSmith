#include "replacedialog.h"
#include "ui_replacedialog.h"
#include "mainwindow.h"
#include <QPushButton>

ReplaceDialog::ReplaceDialog(bool selection, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReplaceDialog)
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

    connect(ui->lineEdit, SIGNAL(textChanged(const QString &)), SLOT(changedText(const QString &)));
    connect(box, SIGNAL(accepted()), SLOT(accept()));
    connect(box, SIGNAL(rejected()), SLOT(reject()));}

ReplaceDialog::~ReplaceDialog()
{
    delete ui;
}

SearchType ReplaceDialog::getType()
{
    if (ui->selectionRadioButton->isChecked()) return bySelection;
    if (ui->sceneRadioButton->isChecked()) return byScene;
    if (ui->childrenRadioButton->isChecked()) return bySceneChildren;
    if (ui->siblingsRadioButton->isChecked()) return bySiblingChildren;
    return byAll;
}

QString ReplaceDialog::getSearchString()
{
    return ui->lineEdit->text();
}

QString ReplaceDialog::getReplaceString()
{
    return ui->lineEdit_2->text();
}

void ReplaceDialog::setSearchString(QString x) {
    ui->lineEdit->setText(x);
}

void ReplaceDialog::setReplaceString(QString x) {
    ui->lineEdit_2->setText(x);
}


void ReplaceDialog::changedText(const QString &text)
{
    QDialogButtonBox* box = ui->buttonBox;
    QPushButton* ok = box->button(QDialogButtonBox::StandardButton::Ok);
    ok->setEnabled(!text.isEmpty());
}
