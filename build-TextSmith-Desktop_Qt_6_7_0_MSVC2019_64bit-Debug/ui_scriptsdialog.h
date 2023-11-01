/********************************************************************************
** Form generated from reading UI file 'scriptsdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCRIPTSDIALOG_H
#define UI_SCRIPTSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ScriptsDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QListWidget *listWidget;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *runButton;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QSpacerItem *verticalSpacer_2;
    QPushButton *refreshButton;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ScriptsDialog)
    {
        if (ScriptsDialog->objectName().isEmpty())
            ScriptsDialog->setObjectName("ScriptsDialog");
        ScriptsDialog->resize(400, 300);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/TextSmith.ico"), QSize(), QIcon::Normal, QIcon::Off);
        ScriptsDialog->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(ScriptsDialog);
        verticalLayout->setObjectName("verticalLayout");
        frame = new QFrame(ScriptsDialog);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Plain);
        frame->setLineWidth(0);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        listWidget = new QListWidget(frame);
        listWidget->setObjectName("listWidget");

        horizontalLayout->addWidget(listWidget);

        frame_2 = new QFrame(frame);
        frame_2->setObjectName("frame_2");
        frame_2->setFrameShape(QFrame::NoFrame);
        frame_2->setFrameShadow(QFrame::Plain);
        frame_2->setLineWidth(0);
        verticalLayout_2 = new QVBoxLayout(frame_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        runButton = new QPushButton(frame_2);
        runButton->setObjectName("runButton");
        runButton->setAutoDefault(false);

        verticalLayout_2->addWidget(runButton);

        addButton = new QPushButton(frame_2);
        addButton->setObjectName("addButton");

        verticalLayout_2->addWidget(addButton);

        deleteButton = new QPushButton(frame_2);
        deleteButton->setObjectName("deleteButton");
        deleteButton->setAutoDefault(false);

        verticalLayout_2->addWidget(deleteButton);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        refreshButton = new QPushButton(frame_2);
        refreshButton->setObjectName("refreshButton");
        refreshButton->setAutoDefault(false);

        verticalLayout_2->addWidget(refreshButton);


        horizontalLayout->addWidget(frame_2);


        verticalLayout->addWidget(frame);

        buttonBox = new QDialogButtonBox(ScriptsDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(ScriptsDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, ScriptsDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, ScriptsDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(ScriptsDialog);
    } // setupUi

    void retranslateUi(QDialog *ScriptsDialog)
    {
        ScriptsDialog->setWindowTitle(QCoreApplication::translate("ScriptsDialog", "Dialog", nullptr));
        runButton->setText(QCoreApplication::translate("ScriptsDialog", "Run Script", nullptr));
        addButton->setText(QCoreApplication::translate("ScriptsDialog", "Add Script", nullptr));
        deleteButton->setText(QCoreApplication::translate("ScriptsDialog", "Delete Script", nullptr));
        refreshButton->setText(QCoreApplication::translate("ScriptsDialog", "Refresh", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ScriptsDialog: public Ui_ScriptsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCRIPTSDIALOG_H
