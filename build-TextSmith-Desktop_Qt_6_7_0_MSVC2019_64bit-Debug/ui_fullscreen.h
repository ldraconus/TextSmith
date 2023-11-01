/********************************************************************************
** Form generated from reading UI file 'fullscreen.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FULLSCREEN_H
#define UI_FULLSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "textedit.h"

QT_BEGIN_NAMESPACE

class Ui_FullScreen
{
public:
    QHBoxLayout *horizontalLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QSplitter *splitter;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout;
    TextEdit *textEdit;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;

    void setupUi(QDialog *FullScreen)
    {
        if (FullScreen->objectName().isEmpty())
            FullScreen->setObjectName("FullScreen");
        FullScreen->setWindowModality(Qt::ApplicationModal);
        FullScreen->resize(400, 300);
        FullScreen->setStyleSheet(QString::fromUtf8("background=rgb(255, 255, 255)"));
        horizontalLayout = new QHBoxLayout(FullScreen);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(FullScreen);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        splitter = new QSplitter(frame);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Horizontal);
        widget = new QWidget(splitter);
        widget->setObjectName("widget");
        widget->setToolTipDuration(-1);
        widget->setAutoFillBackground(true);
        widget->setStyleSheet(QString::fromUtf8("background=rgb(0, 0, 0)"));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName("label");
        label->setPixmap(QPixmap(QString::fromUtf8(":/black.png")));
        label->setScaledContents(true);

        verticalLayout_2->addWidget(label);

        splitter->addWidget(widget);
        frame_2 = new QFrame(splitter);
        frame_2->setObjectName("frame_2");
        frame_2->setAutoFillBackground(true);
        frame_2->setStyleSheet(QString::fromUtf8("bacground=#FFFFFF"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame_2);
        verticalLayout->setObjectName("verticalLayout");
        textEdit = new TextEdit(frame_2);
        textEdit->setObjectName("textEdit");
        textEdit->setContextMenuPolicy(Qt::NoContextMenu);

        verticalLayout->addWidget(textEdit);

        splitter->addWidget(frame_2);
        widget_2 = new QWidget(splitter);
        widget_2->setObjectName("widget_2");
        widget_2->setAutoFillBackground(true);
        widget_2->setStyleSheet(QString::fromUtf8("backgroiund=#000000"));
        verticalLayout_3 = new QVBoxLayout(widget_2);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget_2);
        label_2->setObjectName("label_2");
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/black.png")));
        label_2->setScaledContents(true);

        verticalLayout_3->addWidget(label_2);

        splitter->addWidget(widget_2);

        horizontalLayout_2->addWidget(splitter);


        horizontalLayout->addWidget(frame);


        retranslateUi(FullScreen);

        QMetaObject::connectSlotsByName(FullScreen);
    } // setupUi

    void retranslateUi(QDialog *FullScreen)
    {
        FullScreen->setWindowTitle(QString());
        label->setText(QString());
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FullScreen: public Ui_FullScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FULLSCREEN_H
