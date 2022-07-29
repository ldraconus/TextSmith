#ifndef SCRIPTSDIALOG_H
#define SCRIPTSDIALOG_H

#include <QAction>
#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
class ScriptsDialog;
}

class ScriptsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScriptsDialog(QWidget *parent = nullptr);
    ~ScriptsDialog();

private:
    Ui::ScriptsDialog *ui;

#include "connect"

public slots:
    void add();
    void deleteIt();
    void doubleClicked(QListWidgetItem*);
    void refresh();
    void run();
};

#endif // SCRIPTSDIALOG_H
