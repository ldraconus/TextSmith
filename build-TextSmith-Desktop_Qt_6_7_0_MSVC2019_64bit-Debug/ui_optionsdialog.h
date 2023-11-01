/********************************************************************************
** Form generated from reading UI file 'optionsdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONSDIALOG_H
#define UI_OPTIONSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_OptionsDialog
{
public:
    QVBoxLayout *verticalLayout;
    QCheckBox *openCheckBox;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *autoSaveCheckBox;
    QSpinBox *minuteSpinBox;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *soundsCheckBox;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QComboBox *voiceComboBox;
    QSpacerItem *horizontalSpacer_3;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QPushButton *fontButton;
    QSpacerItem *horizontalSpacer;
    QTextEdit *fontExampleTextEdit;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *OptionsDialog)
    {
        if (OptionsDialog->objectName().isEmpty())
            OptionsDialog->setObjectName("OptionsDialog");
        OptionsDialog->resize(400, 348);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/TextSmith.ico"), QSize(), QIcon::Normal, QIcon::Off);
        OptionsDialog->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(OptionsDialog);
        verticalLayout->setObjectName("verticalLayout");
        openCheckBox = new QCheckBox(OptionsDialog);
        openCheckBox->setObjectName("openCheckBox");

        verticalLayout->addWidget(openCheckBox);

        frame_2 = new QFrame(OptionsDialog);
        frame_2->setObjectName("frame_2");
        frame_2->setFrameShape(QFrame::NoFrame);
        frame_2->setFrameShadow(QFrame::Plain);
        frame_2->setLineWidth(0);
        horizontalLayout_2 = new QHBoxLayout(frame_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        autoSaveCheckBox = new QCheckBox(frame_2);
        autoSaveCheckBox->setObjectName("autoSaveCheckBox");

        horizontalLayout_2->addWidget(autoSaveCheckBox);

        minuteSpinBox = new QSpinBox(frame_2);
        minuteSpinBox->setObjectName("minuteSpinBox");
        minuteSpinBox->setMinimum(1);

        horizontalLayout_2->addWidget(minuteSpinBox);

        label_2 = new QLabel(frame_2);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(frame_2);

        soundsCheckBox = new QCheckBox(OptionsDialog);
        soundsCheckBox->setObjectName("soundsCheckBox");

        verticalLayout->addWidget(soundsCheckBox);

        frame_3 = new QFrame(OptionsDialog);
        frame_3->setObjectName("frame_3");
        frame_3->setFrameShape(QFrame::NoFrame);
        frame_3->setFrameShadow(QFrame::Plain);
        frame_3->setLineWidth(0);
        horizontalLayout_3 = new QHBoxLayout(frame_3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(18, 0, 0, 0);
        label_3 = new QLabel(frame_3);
        label_3->setObjectName("label_3");

        horizontalLayout_3->addWidget(label_3);

        voiceComboBox = new QComboBox(frame_3);
        voiceComboBox->setObjectName("voiceComboBox");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(voiceComboBox->sizePolicy().hasHeightForWidth());
        voiceComboBox->setSizePolicy(sizePolicy);
        voiceComboBox->setMinimumSize(QSize(100, 0));
        voiceComboBox->setBaseSize(QSize(100, 0));
        voiceComboBox->setContextMenuPolicy(Qt::NoContextMenu);

        horizontalLayout_3->addWidget(voiceComboBox);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout->addWidget(frame_3);

        frame = new QFrame(OptionsDialog);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        frame->setLineWidth(0);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(18, 0, 0, 0);
        label = new QLabel(frame);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        fontButton = new QPushButton(frame);
        fontButton->setObjectName("fontButton");
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(fontButton->sizePolicy().hasHeightForWidth());
        fontButton->setSizePolicy(sizePolicy1);
        fontButton->setMinimumSize(QSize(20, 20));
        fontButton->setMaximumSize(QSize(20, 20));
        fontButton->setBaseSize(QSize(20, 20));

        horizontalLayout->addWidget(fontButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addWidget(frame);

        fontExampleTextEdit = new QTextEdit(OptionsDialog);
        fontExampleTextEdit->setObjectName("fontExampleTextEdit");
        fontExampleTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        fontExampleTextEdit->setReadOnly(true);

        verticalLayout->addWidget(fontExampleTextEdit);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(OptionsDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(OptionsDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, OptionsDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, OptionsDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(OptionsDialog);
    } // setupUi

    void retranslateUi(QDialog *OptionsDialog)
    {
        OptionsDialog->setWindowTitle(QCoreApplication::translate("OptionsDialog", "Dialog", nullptr));
        openCheckBox->setText(QCoreApplication::translate("OptionsDialog", "Open all items when novel opened", nullptr));
        autoSaveCheckBox->setText(QCoreApplication::translate("OptionsDialog", "Autosave every", nullptr));
        label_2->setText(QCoreApplication::translate("OptionsDialog", "minutes", nullptr));
        soundsCheckBox->setText(QCoreApplication::translate("OptionsDialog", "Typewriter sounds in distaction free editor", nullptr));
        label_3->setText(QCoreApplication::translate("OptionsDialog", "Set Voice:", nullptr));
        voiceComboBox->setPlaceholderText(QCoreApplication::translate("OptionsDialog", "Pick a voice", nullptr));
        label->setText(QCoreApplication::translate("OptionsDialog", "<html><head/><body><p>Change the default text font in the text editor</p></body></html>", nullptr));
        fontButton->setText(QCoreApplication::translate("OptionsDialog", "...", nullptr));
        fontExampleTextEdit->setHtml(QCoreApplication::translate("OptionsDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Lorem ipsum dolor sit amen, consectetur adipiscing elt, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostroud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariature. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OptionsDialog: public Ui_OptionsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONSDIALOG_H
