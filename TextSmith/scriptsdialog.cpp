#include "scriptsdialog.h"
#include "mainwindow.h"
#include "ui_scriptsdialog.h"

#include <QDir>
#include <QFileDialog>
#include <QStandardPaths>

ScriptsDialog::ScriptsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScriptsDialog)
{
    ui->setupUi(this);
    refresh();

    connect(ui->addButton,     SIGNAL(clicked()),                           SLOT(add()));
    connect(ui->deleteButton,  SIGNAL(clicked()),                           SLOT(deleteIt()));
    connect(ui->refreshButton, SIGNAL(clicked()),                           SLOT(refresh()));
    connect(ui->runButton,     SIGNAL(clicked()),                           SLOT(run()));
    connect(ui->listWidget,    SIGNAL(itemDoubleClicked(QListWidgetItem*)), SLOT(doubleClicked(QListWidgetItem*)));
}

ScriptsDialog::~ScriptsDialog()
{
    delete ui;
}

void ScriptsDialog::add() {
    QString docs = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString fname = QFileDialog::getOpenFileName(this, "Add script", docs, "Scripts (*.lua)");
    int pos = fname.lastIndexOf("/");
    QString name = fname;
    if (pos != -1) name = fname.mid(pos + 1);
    if (fname.isEmpty()) return;

    QString dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/scripts";
    QDir dirOp;
    dirOp.mkpath(dir);
    QFile::copy(fname, dir + "/" + name);
    refresh();
}

void ScriptsDialog::deleteIt() {
    QString filename = ui->listWidget->currentItem()->text();
    QString dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/scripts";
    QFile::remove(dir + "/" + filename);
    refresh();
}

void ScriptsDialog::doubleClicked(QListWidgetItem*) {
    run();
}

void ScriptsDialog::refresh() {
    QString dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/scripts";
    QDir dirOp;
    dirOp.mkpath(dir);

    // MainWindow::main_window()->Statement(("DIR: " + dir + "/scripts").toStdString().c_str());
    dirOp = dir;
    QStringList filter;
    filter << "*.lua";
    dirOp.setNameFilters(filter);
    QStringList scripts = dirOp.entryList();
    ui->listWidget->clear();
    ui->listWidget->addItems(scripts);
}

void ScriptsDialog::run() {
    QString filename = ui->listWidget->currentItem()->text();
    QString dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/scripts";
    QString exe = dir + "/" + filename;
    luaL_dofile(MainWindow::main_window()->Lua(), exe.toStdString().c_str());
}
