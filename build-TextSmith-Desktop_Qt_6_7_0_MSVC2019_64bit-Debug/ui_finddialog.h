/********************************************************************************
** Form generated from reading UI file 'finddialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDDIALOG_H
#define UI_FINDDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FindDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QRadioButton *selectionRadioButton;
    QRadioButton *sceneRadioButton;
    QRadioButton *childrenRadioButton;
    QRadioButton *siblingsRadioButton;
    QRadioButton *bookRadioButton;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *FindDialog)
    {
        if (FindDialog->objectName().isEmpty())
            FindDialog->setObjectName("FindDialog");
        FindDialog->resize(400, 243);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/TextSmith.ico"), QSize(), QIcon::Normal, QIcon::Off);
        FindDialog->setWindowIcon(icon);
        FindDialog->setModal(true);
        verticalLayout_2 = new QVBoxLayout(FindDialog);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(FindDialog);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(FindDialog);
        lineEdit->setObjectName("lineEdit");

        horizontalLayout->addWidget(lineEdit);


        verticalLayout_2->addLayout(horizontalLayout);

        groupBox = new QGroupBox(FindDialog);
        groupBox->setObjectName("groupBox");
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(5, -1, -1, -1);
        selectionRadioButton = new QRadioButton(groupBox);
        selectionRadioButton->setObjectName("selectionRadioButton");

        verticalLayout->addWidget(selectionRadioButton);

        sceneRadioButton = new QRadioButton(groupBox);
        sceneRadioButton->setObjectName("sceneRadioButton");

        verticalLayout->addWidget(sceneRadioButton);

        childrenRadioButton = new QRadioButton(groupBox);
        childrenRadioButton->setObjectName("childrenRadioButton");

        verticalLayout->addWidget(childrenRadioButton);

        siblingsRadioButton = new QRadioButton(groupBox);
        siblingsRadioButton->setObjectName("siblingsRadioButton");

        verticalLayout->addWidget(siblingsRadioButton);

        bookRadioButton = new QRadioButton(groupBox);
        bookRadioButton->setObjectName("bookRadioButton");

        verticalLayout->addWidget(bookRadioButton);


        verticalLayout_3->addLayout(verticalLayout);


        verticalLayout_2->addWidget(groupBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(FindDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(FindDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, FindDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, FindDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(FindDialog);
    } // setupUi

    void retranslateUi(QDialog *FindDialog)
    {
        FindDialog->setWindowTitle(QCoreApplication::translate("FindDialog", "Search", nullptr));
        label->setText(QCoreApplication::translate("FindDialog", "Find:", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("FindDialog", "Look For?", nullptr));
        groupBox->setTitle(QCoreApplication::translate("FindDialog", "Search:", nullptr));
        selectionRadioButton->setText(QCoreApplication::translate("FindDialog", "Current Selection", nullptr));
        sceneRadioButton->setText(QCoreApplication::translate("FindDialog", "Current Scene", nullptr));
        childrenRadioButton->setText(QCoreApplication::translate("FindDialog", "Current Scene and Children", nullptr));
        siblingsRadioButton->setText(QCoreApplication::translate("FindDialog", "Current Scene, Siblings and Children", nullptr));
        bookRadioButton->setText(QCoreApplication::translate("FindDialog", "All Scenes", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FindDialog: public Ui_FindDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDDIALOG_H
