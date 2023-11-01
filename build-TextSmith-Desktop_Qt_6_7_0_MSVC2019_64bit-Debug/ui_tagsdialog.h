/********************************************************************************
** Form generated from reading UI file 'tagsdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TAGSDIALOG_H
#define UI_TAGSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TagsDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame4;
    QHBoxLayout *horizontalLayout;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QLabel *label_2;
    QFrame *frame_3;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QFrame *frame;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *TagsDialog)
    {
        if (TagsDialog->objectName().isEmpty())
            TagsDialog->setObjectName("TagsDialog");
        TagsDialog->setWindowModality(Qt::ApplicationModal);
        TagsDialog->resize(422, 348);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TagsDialog->sizePolicy().hasHeightForWidth());
        TagsDialog->setSizePolicy(sizePolicy);
        TagsDialog->setFocusPolicy(Qt::StrongFocus);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/TextSmith.ico"), QSize(), QIcon::Normal, QIcon::Off);
        TagsDialog->setWindowIcon(icon);
        TagsDialog->setModal(true);
        verticalLayout = new QVBoxLayout(TagsDialog);
        verticalLayout->setObjectName("verticalLayout");
        frame4 = new QFrame(TagsDialog);
        frame4->setObjectName("frame4");
        frame4->setFrameShape(QFrame::NoFrame);
        frame4->setFrameShadow(QFrame::Plain);
        frame4->setLineWidth(0);
        horizontalLayout = new QHBoxLayout(frame4);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        frame_2 = new QFrame(frame4);
        frame_2->setObjectName("frame_2");
        frame_2->setFrameShape(QFrame::NoFrame);
        frame_2->setFrameShadow(QFrame::Plain);
        frame_2->setLineWidth(0);
        verticalLayout_3 = new QVBoxLayout(frame_2);
        verticalLayout_3->setSpacing(9);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(9, 4, 3, 4);
        label = new QLabel(frame_2);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_3->addWidget(label);

        label_2 = new QLabel(frame_2);
        label_2->setObjectName("label_2");
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_3->addWidget(label_2);


        horizontalLayout->addWidget(frame_2);

        frame_3 = new QFrame(frame4);
        frame_3->setObjectName("frame_3");
        frame_3->setFrameShape(QFrame::NoFrame);
        frame_3->setFrameShadow(QFrame::Plain);
        frame_3->setLineWidth(0);
        verticalLayout_2 = new QVBoxLayout(frame_3);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(frame_3);
        lineEdit->setObjectName("lineEdit");

        verticalLayout_2->addWidget(lineEdit);

        lineEdit_2 = new QLineEdit(frame_3);
        lineEdit_2->setObjectName("lineEdit_2");

        verticalLayout_2->addWidget(lineEdit_2);


        horizontalLayout->addWidget(frame_3);


        verticalLayout->addWidget(frame4);

        frame = new QFrame(TagsDialog);
        frame->setObjectName("frame");
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setMinimumSize(QSize(0, 200));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Plain);
        frame->setLineWidth(0);

        verticalLayout->addWidget(frame);

        buttonBox = new QDialogButtonBox(TagsDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(TagsDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, TagsDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, TagsDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(TagsDialog);
    } // setupUi

    void retranslateUi(QDialog *TagsDialog)
    {
        TagsDialog->setWindowTitle(QCoreApplication::translate("TagsDialog", "Details", nullptr));
        label->setText(QCoreApplication::translate("TagsDialog", "Name:", nullptr));
        label_2->setText(QCoreApplication::translate("TagsDialog", "Tag:", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("TagsDialog", "<unnamed>", nullptr));
        lineEdit_2->setPlaceholderText(QCoreApplication::translate("TagsDialog", "<hit ENTER to save tag, press button to delete tag>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TagsDialog: public Ui_TagsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TAGSDIALOG_H
