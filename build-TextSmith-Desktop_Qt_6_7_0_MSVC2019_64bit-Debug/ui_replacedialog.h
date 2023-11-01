/********************************************************************************
** Form generated from reading UI file 'replacedialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REPLACEDIALOG_H
#define UI_REPLACEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ReplaceDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QFormLayout *formLayout;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLabel *label;
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

    void setupUi(QDialog *ReplaceDialog)
    {
        if (ReplaceDialog->objectName().isEmpty())
            ReplaceDialog->setObjectName("ReplaceDialog");
        ReplaceDialog->setWindowModality(Qt::NonModal);
        ReplaceDialog->resize(400, 278);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/TextSmith.ico"), QSize(), QIcon::Normal, QIcon::Off);
        ReplaceDialog->setWindowIcon(icon);
        ReplaceDialog->setModal(true);
        verticalLayout_2 = new QVBoxLayout(ReplaceDialog);
        verticalLayout_2->setObjectName("verticalLayout_2");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        lineEdit = new QLineEdit(ReplaceDialog);
        lineEdit->setObjectName("lineEdit");

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit);

        label_2 = new QLabel(ReplaceDialog);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        lineEdit_2 = new QLineEdit(ReplaceDialog);
        lineEdit_2->setObjectName("lineEdit_2");

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEdit_2);

        label = new QLabel(ReplaceDialog);
        label->setObjectName("label");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(0, QFormLayout::LabelRole, label);


        verticalLayout_2->addLayout(formLayout);

        groupBox = new QGroupBox(ReplaceDialog);
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

        buttonBox = new QDialogButtonBox(ReplaceDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(ReplaceDialog);

        QMetaObject::connectSlotsByName(ReplaceDialog);
    } // setupUi

    void retranslateUi(QDialog *ReplaceDialog)
    {
        ReplaceDialog->setWindowTitle(QCoreApplication::translate("ReplaceDialog", "Replace", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("ReplaceDialog", "Look For?", nullptr));
        label_2->setText(QCoreApplication::translate("ReplaceDialog", "Replace:", nullptr));
        lineEdit_2->setPlaceholderText(QCoreApplication::translate("ReplaceDialog", "Replace With?", nullptr));
        label->setText(QCoreApplication::translate("ReplaceDialog", "Find:", nullptr));
        groupBox->setTitle(QCoreApplication::translate("ReplaceDialog", "Search:", nullptr));
        selectionRadioButton->setText(QCoreApplication::translate("ReplaceDialog", "Current Selection", nullptr));
        sceneRadioButton->setText(QCoreApplication::translate("ReplaceDialog", "Current Scene", nullptr));
        childrenRadioButton->setText(QCoreApplication::translate("ReplaceDialog", "Current Scene and Children", nullptr));
        siblingsRadioButton->setText(QCoreApplication::translate("ReplaceDialog", "Current Scene, Siblings and Children", nullptr));
        bookRadioButton->setText(QCoreApplication::translate("ReplaceDialog", "All Scenes", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ReplaceDialog: public Ui_ReplaceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPLACEDIALOG_H
