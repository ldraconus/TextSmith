/********************************************************************************
** Form generated from reading UI file 'aboutdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTDIALOG_H
#define UI_ABOUTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AboutDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *AboutDialog)
    {
        if (AboutDialog->objectName().isEmpty())
            AboutDialog->setObjectName("AboutDialog");
        AboutDialog->resize(400, 373);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/TextSmith.ico"), QSize(), QIcon::Normal, QIcon::Off);
        AboutDialog->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(AboutDialog);
        verticalLayout->setObjectName("verticalLayout");
        label_4 = new QLabel(AboutDialog);
        label_4->setObjectName("label_4");
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/TextSmith.ico")));
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_4);

        label = new QLabel(AboutDialog);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(20);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        label_2 = new QLabel(AboutDialog);
        label_2->setObjectName("label_2");
        label_2->setWordWrap(true);

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(AboutDialog);
        label_3->setObjectName("label_3");
        QFont font1;
        font1.setPointSize(8);
        label_3->setFont(font1);
        label_3->setWordWrap(true);

        verticalLayout->addWidget(label_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(AboutDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(AboutDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, AboutDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, AboutDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(AboutDialog);
    } // setupUi

    void retranslateUi(QDialog *AboutDialog)
    {
        AboutDialog->setWindowTitle(QCoreApplication::translate("AboutDialog", "Dialog", nullptr));
        label_4->setText(QString());
        label->setText(QCoreApplication::translate("AboutDialog", "TextSmith v1.0.0", nullptr));
        label_2->setText(QCoreApplication::translate("AboutDialog", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:700;\">TextSmith</span><span style=\" font-size:10pt;\"> strives to be a distraction free novel editor while still supplying the tools needed to get the job done.  No fancy colors or cork board, just a simple tree layout for the document.  It also follows the OS with respect to dark mode so there is one less thing to fiddle with.</span></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("AboutDialog", "<html><head/><body><p><span style=\" font-size:8pt;\">Uses the </span><span style=\" font-size:8pt; font-weight:700;\">Qt</span><span style=\" font-size:8pt;\"> application framework v6 for the look and feel.<br/>Uses the </span><span style=\" font-size:8pt; font-weight:700;\">Zippy</span><span style=\" font-size:8pt;\"> zip file creation library to build epub files.<br/>Uses </span><span style=\" font-size:8pt; font-weight:700;\">Lua</span><span style=\" font-size:8pt;\"> as it's scripting language, found here: </span><a href=\"https://www.lua.org/\"><span style=\" text-decoration: underline; color:#007af4;\">https://www.lua.org/</span></a><span style=\" font-size:8pt;\"><br/></span><span style=\" font-size:8pt; font-weight:700;\">RTF </span><span style=\" font-size:8pt;\">export code based loosely on the code found on this web page: </span><a href=\"https://www.codeproject.com/Articles/10582/rtflib-v1-0\"><span style=\" text-decoration: underline; color:#007af4;\">https://www.codeproject.com/Articles/10582/r"
                        "tflib-v1-0</span></a><span style=\" font-size:8pt; font-weight:700;\"><br/>DarkMode</span><span style=\" font-size:8pt;\"> support based on code found on this web page: </span><a href=\"https://successfulsoftware.net/2021/03/31/how-to-add-a-dark-theme-to-your-qt-application/\"><span style=\" font-size:8pt; text-decoration: underline; color:#007af4;\">How to add a dark theme to your Qt application | Successful Software<br/></span></a></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AboutDialog: public Ui_AboutDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTDIALOG_H
