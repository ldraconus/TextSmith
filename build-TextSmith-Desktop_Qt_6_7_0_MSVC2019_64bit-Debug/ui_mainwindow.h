/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>
#include "textedit.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_New;
    QAction *action_Open;
    QAction *action_Close;
    QAction *action_Save;
    QAction *actionSave_As;
    QAction *actionE_xit;
    QAction *action_Cut;
    QAction *actionC_opy;
    QAction *action_Paste;
    QAction *action_Bold;
    QAction *action_Italic;
    QAction *action_Underline;
    QAction *action_Left_JUstify;
    QAction *action_Center;
    QAction *action_Full_Justify;
    QAction *action_Right_Justify;
    QAction *action_Distraction_Free;
    QAction *action_Scripts;
    QAction *action_Contents_Open;
    QAction *action_Contents_Close;
    QAction *actionClose_Below;
    QAction *action_Open_Below;
    QAction *action_About;
    QAction *action_Documentation;
    QAction *action_Options;
    QAction *action_Word_Count;
    QAction *action_Undo;
    QAction *action_Search;
    QAction *actionRepl_ace;
    QAction *action_PDF;
    QAction *action_EPUB;
    QAction *action_HTML;
    QAction *action_Markdown;
    QAction *action_RTF;
    QAction *action_Image;
    QAction *action_Text;
    QAction *action_Standard_Text;
    QAction *actionNew_Group;
    QAction *actionOpen_Group;
    QAction *actionClolse_Group;
    QAction *actionRemove_Group;
    QAction *actionNew_Scene;
    QAction *actionRemove_Scene;
    QAction *actionMove_Up;
    QAction *actionMove_Down;
    QAction *actionMove_In;
    QAction *actionMove_Out;
    QAction *actionIndent;
    QAction *actionOutdent;
    QAction *actionTags;
    QAction *action_Redo;
    QAction *action_Replace;
    QAction *actionRepalce_All;
    QAction *actionFind_Next;
    QAction *actionReplace_Selection;
    QAction *actionReplace_All;
    QAction *actionRead_Aloud;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter;
    QTreeWidget *treeWidget;
    TextEdit *textEdit;
    QMenuBar *menubar;
    QMenu *menu_File;
    QMenu *menu_Export;
    QMenu *menu_Import;
    QMenu *menu_Edit;
    QMenu *menu_View;
    QMenu *menu_Help;
    QMenu *menu_Structure;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(607, 456);
        MainWindow->setContextMenuPolicy(Qt::PreventContextMenu);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/TextSmith.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        action_New = new QAction(MainWindow);
        action_New->setObjectName("action_New");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new.ico"), QSize(), QIcon::Normal, QIcon::On);
        action_New->setIcon(icon1);
        action_Open = new QAction(MainWindow);
        action_Open->setObjectName("action_Open");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/file.ico"), QSize(), QIcon::Normal, QIcon::On);
        action_Open->setIcon(icon2);
        action_Close = new QAction(MainWindow);
        action_Close->setObjectName("action_Close");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/close.ico"), QSize(), QIcon::Normal, QIcon::On);
        action_Close->setIcon(icon3);
        action_Save = new QAction(MainWindow);
        action_Save->setObjectName("action_Save");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/save.ico"), QSize(), QIcon::Normal, QIcon::On);
        action_Save->setIcon(icon4);
        actionSave_As = new QAction(MainWindow);
        actionSave_As->setObjectName("actionSave_As");
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/saveAs.ico"), QSize(), QIcon::Normal, QIcon::On);
        actionSave_As->setIcon(icon5);
        actionE_xit = new QAction(MainWindow);
        actionE_xit->setObjectName("actionE_xit");
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/exit.ico"), QSize(), QIcon::Normal, QIcon::On);
        actionE_xit->setIcon(icon6);
        actionE_xit->setShortcutContext(Qt::ApplicationShortcut);
        action_Cut = new QAction(MainWindow);
        action_Cut->setObjectName("action_Cut");
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/cut.ico"), QSize(), QIcon::Normal, QIcon::On);
        action_Cut->setIcon(icon7);
        action_Cut->setShortcutContext(Qt::ApplicationShortcut);
        actionC_opy = new QAction(MainWindow);
        actionC_opy->setObjectName("actionC_opy");
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/copy.ico"), QSize(), QIcon::Normal, QIcon::On);
        actionC_opy->setIcon(icon8);
        actionC_opy->setShortcutContext(Qt::ApplicationShortcut);
        action_Paste = new QAction(MainWindow);
        action_Paste->setObjectName("action_Paste");
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/paste.ico"), QSize(), QIcon::Normal, QIcon::On);
        action_Paste->setIcon(icon9);
        action_Paste->setShortcutContext(Qt::ApplicationShortcut);
        action_Bold = new QAction(MainWindow);
        action_Bold->setObjectName("action_Bold");
        action_Bold->setCheckable(true);
        action_Bold->setChecked(false);
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/bold.ico"), QSize(), QIcon::Normal, QIcon::On);
        action_Bold->setIcon(icon10);
        action_Italic = new QAction(MainWindow);
        action_Italic->setObjectName("action_Italic");
        action_Italic->setCheckable(true);
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/italic.ico"), QSize(), QIcon::Normal, QIcon::On);
        action_Italic->setIcon(icon11);
        action_Underline = new QAction(MainWindow);
        action_Underline->setObjectName("action_Underline");
        action_Underline->setCheckable(true);
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/underline.ico"), QSize(), QIcon::Normal, QIcon::On);
        action_Underline->setIcon(icon12);
        action_Left_JUstify = new QAction(MainWindow);
        action_Left_JUstify->setObjectName("action_Left_JUstify");
        action_Left_JUstify->setCheckable(true);
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/leftJustify.ico"), QSize(), QIcon::Normal, QIcon::On);
        action_Left_JUstify->setIcon(icon13);
        action_Center = new QAction(MainWindow);
        action_Center->setObjectName("action_Center");
        action_Center->setCheckable(true);
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/center.ico"), QSize(), QIcon::Normal, QIcon::On);
        action_Center->setIcon(icon14);
        action_Full_Justify = new QAction(MainWindow);
        action_Full_Justify->setObjectName("action_Full_Justify");
        action_Full_Justify->setCheckable(true);
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/fullJustify.ico"), QSize(), QIcon::Normal, QIcon::On);
        action_Full_Justify->setIcon(icon15);
        action_Right_Justify = new QAction(MainWindow);
        action_Right_Justify->setObjectName("action_Right_Justify");
        action_Right_Justify->setCheckable(true);
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/rightJustify.ico"), QSize(), QIcon::Normal, QIcon::On);
        action_Right_Justify->setIcon(icon16);
        action_Distraction_Free = new QAction(MainWindow);
        action_Distraction_Free->setObjectName("action_Distraction_Free");
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/fullScreen.ico"), QSize(), QIcon::Normal, QIcon::On);
        action_Distraction_Free->setIcon(icon17);
        action_Scripts = new QAction(MainWindow);
        action_Scripts->setObjectName("action_Scripts");
        QIcon icon18;
        icon18.addFile(QString::fromUtf8(":/script.ico"), QSize(), QIcon::Normal, QIcon::On);
        action_Scripts->setIcon(icon18);
        action_Contents_Open = new QAction(MainWindow);
        action_Contents_Open->setObjectName("action_Contents_Open");
        action_Contents_Close = new QAction(MainWindow);
        action_Contents_Close->setObjectName("action_Contents_Close");
        actionClose_Below = new QAction(MainWindow);
        actionClose_Below->setObjectName("actionClose_Below");
        action_Open_Below = new QAction(MainWindow);
        action_Open_Below->setObjectName("action_Open_Below");
        action_About = new QAction(MainWindow);
        action_About->setObjectName("action_About");
        QIcon icon19;
        icon19.addFile(QString::fromUtf8(":/about.ico"), QSize(), QIcon::Normal, QIcon::On);
        action_About->setIcon(icon19);
        action_Documentation = new QAction(MainWindow);
        action_Documentation->setObjectName("action_Documentation");
        QIcon icon20;
        icon20.addFile(QString::fromUtf8(":/help.ico"), QSize(), QIcon::Normal, QIcon::On);
        action_Documentation->setIcon(icon20);
        action_Options = new QAction(MainWindow);
        action_Options->setObjectName("action_Options");
        QIcon icon21;
        icon21.addFile(QString::fromUtf8(":/settings.ico"), QSize(), QIcon::Normal, QIcon::On);
        action_Options->setIcon(icon21);
        action_Word_Count = new QAction(MainWindow);
        action_Word_Count->setObjectName("action_Word_Count");
        QIcon icon22;
        icon22.addFile(QString::fromUtf8(":/wc.ico"), QSize(), QIcon::Normal, QIcon::On);
        action_Word_Count->setIcon(icon22);
        action_Undo = new QAction(MainWindow);
        action_Undo->setObjectName("action_Undo");
        action_Undo->setEnabled(false);
        QIcon icon23;
        icon23.addFile(QString::fromUtf8(":/undo.ico"), QSize(), QIcon::Normal, QIcon::On);
        action_Undo->setIcon(icon23);
        action_Search = new QAction(MainWindow);
        action_Search->setObjectName("action_Search");
        QIcon icon24;
        icon24.addFile(QString::fromUtf8(":/search.ico"), QSize(), QIcon::Normal, QIcon::On);
        action_Search->setIcon(icon24);
        actionRepl_ace = new QAction(MainWindow);
        actionRepl_ace->setObjectName("actionRepl_ace");
        QIcon icon25;
        icon25.addFile(QString::fromUtf8(":/replace.ico"), QSize(), QIcon::Normal, QIcon::On);
        actionRepl_ace->setIcon(icon25);
        action_PDF = new QAction(MainWindow);
        action_PDF->setObjectName("action_PDF");
        QIcon icon26;
        icon26.addFile(QString::fromUtf8(":/pdf.ico"), QSize(), QIcon::Normal, QIcon::On);
        action_PDF->setIcon(icon26);
        action_EPUB = new QAction(MainWindow);
        action_EPUB->setObjectName("action_EPUB");
        QIcon icon27;
        icon27.addFile(QString::fromUtf8(":/epub.ico"), QSize(), QIcon::Normal, QIcon::On);
        action_EPUB->setIcon(icon27);
        action_HTML = new QAction(MainWindow);
        action_HTML->setObjectName("action_HTML");
        QIcon icon28;
        icon28.addFile(QString::fromUtf8(":/html.ico"), QSize(), QIcon::Normal, QIcon::On);
        action_HTML->setIcon(icon28);
        action_Markdown = new QAction(MainWindow);
        action_Markdown->setObjectName("action_Markdown");
        QIcon icon29;
        icon29.addFile(QString::fromUtf8(":/markdown.ico"), QSize(), QIcon::Normal, QIcon::On);
        action_Markdown->setIcon(icon29);
        action_RTF = new QAction(MainWindow);
        action_RTF->setObjectName("action_RTF");
        QIcon icon30;
        icon30.addFile(QString::fromUtf8(":/rtf.ico"), QSize(), QIcon::Normal, QIcon::On);
        action_RTF->setIcon(icon30);
        action_Image = new QAction(MainWindow);
        action_Image->setObjectName("action_Image");
        QIcon icon31;
        icon31.addFile(QString::fromUtf8(":/image.ico"), QSize(), QIcon::Normal, QIcon::On);
        action_Image->setIcon(icon31);
        action_Text = new QAction(MainWindow);
        action_Text->setObjectName("action_Text");
        QIcon icon32;
        icon32.addFile(QString::fromUtf8(":/imp_text.ico"), QSize(), QIcon::Normal, QIcon::On);
        action_Text->setIcon(icon32);
        action_Standard_Text = new QAction(MainWindow);
        action_Standard_Text->setObjectName("action_Standard_Text");
        QIcon icon33;
        icon33.addFile(QString::fromUtf8(":/text.ico"), QSize(), QIcon::Normal, QIcon::On);
        action_Standard_Text->setIcon(icon33);
        actionNew_Group = new QAction(MainWindow);
        actionNew_Group->setObjectName("actionNew_Group");
        QIcon icon34;
        icon34.addFile(QString::fromUtf8(":/NewGroup.ico"), QSize(), QIcon::Normal, QIcon::On);
        actionNew_Group->setIcon(icon34);
        actionOpen_Group = new QAction(MainWindow);
        actionOpen_Group->setObjectName("actionOpen_Group");
        actionClolse_Group = new QAction(MainWindow);
        actionClolse_Group->setObjectName("actionClolse_Group");
        actionRemove_Group = new QAction(MainWindow);
        actionRemove_Group->setObjectName("actionRemove_Group");
        QIcon icon35;
        icon35.addFile(QString::fromUtf8(":/RemoveGroup.ico"), QSize(), QIcon::Normal, QIcon::On);
        actionRemove_Group->setIcon(icon35);
        actionNew_Scene = new QAction(MainWindow);
        actionNew_Scene->setObjectName("actionNew_Scene");
        QIcon icon36;
        icon36.addFile(QString::fromUtf8(":/scene.ico"), QSize(), QIcon::Normal, QIcon::On);
        actionNew_Scene->setIcon(icon36);
        actionRemove_Scene = new QAction(MainWindow);
        actionRemove_Scene->setObjectName("actionRemove_Scene");
        QIcon icon37;
        icon37.addFile(QString::fromUtf8(":/delete.ico"), QSize(), QIcon::Normal, QIcon::On);
        actionRemove_Scene->setIcon(icon37);
        actionMove_Up = new QAction(MainWindow);
        actionMove_Up->setObjectName("actionMove_Up");
        QIcon icon38;
        icon38.addFile(QString::fromUtf8(":/moveUp.ico"), QSize(), QIcon::Normal, QIcon::On);
        actionMove_Up->setIcon(icon38);
        actionMove_Down = new QAction(MainWindow);
        actionMove_Down->setObjectName("actionMove_Down");
        QIcon icon39;
        icon39.addFile(QString::fromUtf8(":/moveDown.ico"), QSize(), QIcon::Normal, QIcon::On);
        actionMove_Down->setIcon(icon39);
        actionMove_In = new QAction(MainWindow);
        actionMove_In->setObjectName("actionMove_In");
        QIcon icon40;
        icon40.addFile(QString::fromUtf8(":/moveIn.ico"), QSize(), QIcon::Normal, QIcon::On);
        actionMove_In->setIcon(icon40);
        actionMove_Out = new QAction(MainWindow);
        actionMove_Out->setObjectName("actionMove_Out");
        QIcon icon41;
        icon41.addFile(QString::fromUtf8(":/moveOut.ico"), QSize(), QIcon::Normal, QIcon::On);
        actionMove_Out->setIcon(icon41);
        actionIndent = new QAction(MainWindow);
        actionIndent->setObjectName("actionIndent");
        actionIndent->setCheckable(true);
        QIcon icon42;
        icon42.addFile(QString::fromUtf8(":/indent.ico"), QSize(), QIcon::Normal, QIcon::On);
        actionIndent->setIcon(icon42);
        actionOutdent = new QAction(MainWindow);
        actionOutdent->setObjectName("actionOutdent");
        actionTags = new QAction(MainWindow);
        actionTags->setObjectName("actionTags");
        QIcon icon43;
        icon43.addFile(QString::fromUtf8(":/tags.ico"), QSize(), QIcon::Normal, QIcon::On);
        actionTags->setIcon(icon43);
        action_Redo = new QAction(MainWindow);
        action_Redo->setObjectName("action_Redo");
        action_Redo->setEnabled(false);
        QIcon icon44;
        icon44.addFile(QString::fromUtf8(":/redo.ico"), QSize(), QIcon::Normal, QIcon::Off);
        action_Redo->setIcon(icon44);
        action_Replace = new QAction(MainWindow);
        action_Replace->setObjectName("action_Replace");
        actionRepalce_All = new QAction(MainWindow);
        actionRepalce_All->setObjectName("actionRepalce_All");
        actionFind_Next = new QAction(MainWindow);
        actionFind_Next->setObjectName("actionFind_Next");
        QIcon icon45;
        icon45.addFile(QString::fromUtf8(":/search.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionFind_Next->setIcon(icon45);
        actionReplace_Selection = new QAction(MainWindow);
        actionReplace_Selection->setObjectName("actionReplace_Selection");
        QIcon icon46;
        icon46.addFile(QString::fromUtf8(":/replace.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionReplace_Selection->setIcon(icon46);
        actionReplace_All = new QAction(MainWindow);
        actionReplace_All->setObjectName("actionReplace_All");
        actionReplace_All->setIcon(icon46);
        actionRead_Aloud = new QAction(MainWindow);
        actionRead_Aloud->setObjectName("actionRead_Aloud");
        QIcon icon47;
        icon47.addFile(QString::fromUtf8(":/speech.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionRead_Aloud->setIcon(icon47);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setContextMenuPolicy(Qt::PreventContextMenu);
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName("splitter");
        splitter->setContextMenuPolicy(Qt::ActionsContextMenu);
        splitter->setOrientation(Qt::Horizontal);
        splitter->setHandleWidth(2);
        treeWidget = new QTreeWidget(splitter);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName("treeWidget");
        treeWidget->setContextMenuPolicy(Qt::NoContextMenu);
        treeWidget->setAcceptDrops(true);
        treeWidget->setEditTriggers(QAbstractItemView::SelectedClicked);
        treeWidget->setDragEnabled(true);
        treeWidget->setDragDropMode(QAbstractItemView::InternalMove);
        treeWidget->setDefaultDropAction(Qt::MoveAction);
        splitter->addWidget(treeWidget);
        treeWidget->header()->setVisible(false);
        textEdit = new TextEdit(splitter);
        textEdit->setObjectName("textEdit");
        textEdit->setContextMenuPolicy(Qt::ActionsContextMenu);
        textEdit->setStyleSheet(QString::fromUtf8("p { text-indent: 30px; }"));
        textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        splitter->addWidget(textEdit);

        horizontalLayout->addWidget(splitter);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 607, 21));
        menubar->setContextMenuPolicy(Qt::NoContextMenu);
        menu_File = new QMenu(menubar);
        menu_File->setObjectName("menu_File");
        menu_File->setContextMenuPolicy(Qt::NoContextMenu);
        menu_Export = new QMenu(menu_File);
        menu_Export->setObjectName("menu_Export");
        menu_Export->setContextMenuPolicy(Qt::NoContextMenu);
        QIcon icon48;
        icon48.addFile(QString::fromUtf8(":/export.ico"), QSize(), QIcon::Normal, QIcon::On);
        menu_Export->setIcon(icon48);
        menu_Import = new QMenu(menu_File);
        menu_Import->setObjectName("menu_Import");
        menu_Import->setContextMenuPolicy(Qt::NoContextMenu);
        QIcon icon49;
        icon49.addFile(QString::fromUtf8(":/import.ico"), QSize(), QIcon::Normal, QIcon::On);
        menu_Import->setIcon(icon49);
        menu_Edit = new QMenu(menubar);
        menu_Edit->setObjectName("menu_Edit");
        menu_Edit->setContextMenuPolicy(Qt::NoContextMenu);
        menu_View = new QMenu(menubar);
        menu_View->setObjectName("menu_View");
        menu_View->setContextMenuPolicy(Qt::NoContextMenu);
        menu_Help = new QMenu(menubar);
        menu_Help->setObjectName("menu_Help");
        menu_Help->setContextMenuPolicy(Qt::NoContextMenu);
        menu_Structure = new QMenu(menubar);
        menu_Structure->setObjectName("menu_Structure");
        menu_Structure->setContextMenuPolicy(Qt::NoContextMenu);
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        statusbar->setContextMenuPolicy(Qt::NoContextMenu);
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        toolBar->setContextMenuPolicy(Qt::NoContextMenu);
        toolBar->setMovable(false);
        toolBar->setIconSize(QSize(16, 16));
        toolBar->setFloatable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menu_File->menuAction());
        menubar->addAction(menu_Structure->menuAction());
        menubar->addAction(menu_Edit->menuAction());
        menubar->addAction(menu_View->menuAction());
        menubar->addAction(menu_Help->menuAction());
        menu_File->addAction(action_New);
        menu_File->addAction(action_Open);
        menu_File->addSeparator();
        menu_File->addAction(action_Save);
        menu_File->addAction(actionSave_As);
        menu_File->addSeparator();
        menu_File->addAction(menu_Export->menuAction());
        menu_File->addAction(menu_Import->menuAction());
        menu_File->addSeparator();
        menu_File->addAction(actionE_xit);
        menu_Export->addAction(action_PDF);
        menu_Export->addAction(action_EPUB);
        menu_Export->addAction(action_HTML);
        menu_Export->addAction(action_Markdown);
        menu_Export->addAction(action_RTF);
        menu_Export->addAction(action_Standard_Text);
        menu_Import->addAction(action_Image);
        menu_Import->addAction(action_Text);
        menu_Edit->addAction(action_Undo);
        menu_Edit->addAction(action_Redo);
        menu_Edit->addSeparator();
        menu_Edit->addAction(action_Cut);
        menu_Edit->addAction(actionC_opy);
        menu_Edit->addAction(action_Paste);
        menu_Edit->addSeparator();
        menu_Edit->addAction(action_Search);
        menu_Edit->addAction(actionFind_Next);
        menu_Edit->addAction(actionRepl_ace);
        menu_Edit->addAction(actionReplace_Selection);
        menu_Edit->addAction(actionReplace_All);
        menu_Edit->addSeparator();
        menu_Edit->addAction(action_Bold);
        menu_Edit->addAction(action_Italic);
        menu_Edit->addAction(action_Underline);
        menu_Edit->addSeparator();
        menu_Edit->addAction(action_Left_JUstify);
        menu_Edit->addAction(action_Center);
        menu_Edit->addAction(action_Full_Justify);
        menu_Edit->addAction(action_Right_Justify);
        menu_Edit->addSeparator();
        menu_Edit->addAction(actionIndent);
        menu_View->addAction(action_Distraction_Free);
        menu_View->addAction(action_Scripts);
        menu_View->addSeparator();
        menu_View->addAction(action_Word_Count);
        menu_View->addAction(actionRead_Aloud);
        menu_Help->addAction(action_About);
        menu_Help->addAction(action_Documentation);
        menu_Help->addAction(action_Options);
        menu_Structure->addAction(actionNew_Scene);
        menu_Structure->addAction(actionRemove_Scene);
        menu_Structure->addSeparator();
        menu_Structure->addAction(actionMove_Up);
        menu_Structure->addAction(actionMove_Down);
        menu_Structure->addAction(actionMove_In);
        menu_Structure->addAction(actionMove_Out);
        menu_Structure->addSeparator();
        menu_Structure->addAction(actionTags);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        action_New->setText(QCoreApplication::translate("MainWindow", "&New", nullptr));
#if QT_CONFIG(shortcut)
        action_New->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Open->setText(QCoreApplication::translate("MainWindow", "&Open", nullptr));
#if QT_CONFIG(shortcut)
        action_Open->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Close->setText(QCoreApplication::translate("MainWindow", "&Close", nullptr));
#if QT_CONFIG(shortcut)
        action_Close->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+W", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Save->setText(QCoreApplication::translate("MainWindow", "&Save", nullptr));
#if QT_CONFIG(shortcut)
        action_Save->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave_As->setText(QCoreApplication::translate("MainWindow", "Save &As", nullptr));
#if QT_CONFIG(shortcut)
        actionSave_As->setShortcut(QCoreApplication::translate("MainWindow", "F12", nullptr));
#endif // QT_CONFIG(shortcut)
        actionE_xit->setText(QCoreApplication::translate("MainWindow", "E&xit", nullptr));
#if QT_CONFIG(shortcut)
        actionE_xit->setShortcut(QCoreApplication::translate("MainWindow", "Alt+X", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Cut->setText(QCoreApplication::translate("MainWindow", "&Cut", nullptr));
#if QT_CONFIG(shortcut)
        action_Cut->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+X", nullptr));
#endif // QT_CONFIG(shortcut)
        actionC_opy->setText(QCoreApplication::translate("MainWindow", "C&opy", nullptr));
#if QT_CONFIG(shortcut)
        actionC_opy->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+C", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Paste->setText(QCoreApplication::translate("MainWindow", "&Paste", nullptr));
#if QT_CONFIG(shortcut)
        action_Paste->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+V", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Bold->setText(QCoreApplication::translate("MainWindow", "&Bold", nullptr));
#if QT_CONFIG(shortcut)
        action_Bold->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+B", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Italic->setText(QCoreApplication::translate("MainWindow", "&Italic", nullptr));
#if QT_CONFIG(shortcut)
        action_Italic->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+I", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Underline->setText(QCoreApplication::translate("MainWindow", "&Underline", nullptr));
#if QT_CONFIG(shortcut)
        action_Underline->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+U", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Left_JUstify->setText(QCoreApplication::translate("MainWindow", "&Left Justify", nullptr));
#if QT_CONFIG(shortcut)
        action_Left_JUstify->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+L", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Center->setText(QCoreApplication::translate("MainWindow", "C&enter", nullptr));
#if QT_CONFIG(shortcut)
        action_Center->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+E", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Full_Justify->setText(QCoreApplication::translate("MainWindow", "&Full Justify", nullptr));
#if QT_CONFIG(shortcut)
        action_Full_Justify->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+J", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Right_Justify->setText(QCoreApplication::translate("MainWindow", "&Right Justify", nullptr));
#if QT_CONFIG(shortcut)
        action_Right_Justify->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+R", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Distraction_Free->setText(QCoreApplication::translate("MainWindow", "&Distraction Free", nullptr));
#if QT_CONFIG(shortcut)
        action_Distraction_Free->setShortcut(QCoreApplication::translate("MainWindow", "F11", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Scripts->setText(QCoreApplication::translate("MainWindow", "&Scripts", nullptr));
#if QT_CONFIG(shortcut)
        action_Scripts->setShortcut(QCoreApplication::translate("MainWindow", "Alt+S", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Contents_Open->setText(QCoreApplication::translate("MainWindow", "C&ontents Open", nullptr));
        action_Contents_Close->setText(QCoreApplication::translate("MainWindow", "&Contents Close", nullptr));
        actionClose_Below->setText(QCoreApplication::translate("MainWindow", "Close &Below", nullptr));
        action_Open_Below->setText(QCoreApplication::translate("MainWindow", "&Open Below", nullptr));
        action_About->setText(QCoreApplication::translate("MainWindow", "&About", nullptr));
#if QT_CONFIG(shortcut)
        action_About->setShortcut(QCoreApplication::translate("MainWindow", "Alt+Enter", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Documentation->setText(QCoreApplication::translate("MainWindow", "&Documentation", nullptr));
#if QT_CONFIG(shortcut)
        action_Documentation->setShortcut(QCoreApplication::translate("MainWindow", "F1", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Options->setText(QCoreApplication::translate("MainWindow", "&Options", nullptr));
#if QT_CONFIG(shortcut)
        action_Options->setShortcut(QCoreApplication::translate("MainWindow", "Alt+Shift+/", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Word_Count->setText(QCoreApplication::translate("MainWindow", "&Word Count", nullptr));
#if QT_CONFIG(shortcut)
        action_Word_Count->setShortcut(QCoreApplication::translate("MainWindow", "Alt+W", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Undo->setText(QCoreApplication::translate("MainWindow", "&Undo", nullptr));
#if QT_CONFIG(shortcut)
        action_Undo->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Z", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Search->setText(QCoreApplication::translate("MainWindow", "&Find", nullptr));
#if QT_CONFIG(shortcut)
        action_Search->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+F", nullptr));
#endif // QT_CONFIG(shortcut)
        actionRepl_ace->setText(QCoreApplication::translate("MainWindow", "Repl&ace", nullptr));
#if QT_CONFIG(shortcut)
        actionRepl_ace->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+H", nullptr));
#endif // QT_CONFIG(shortcut)
        action_PDF->setText(QCoreApplication::translate("MainWindow", "&PDF", nullptr));
        action_EPUB->setText(QCoreApplication::translate("MainWindow", "&EPUB", nullptr));
        action_HTML->setText(QCoreApplication::translate("MainWindow", "&HTML", nullptr));
        action_Markdown->setText(QCoreApplication::translate("MainWindow", "&Markdown", nullptr));
        action_RTF->setText(QCoreApplication::translate("MainWindow", "&RTF", nullptr));
        action_Image->setText(QCoreApplication::translate("MainWindow", "&Image", nullptr));
        action_Text->setText(QCoreApplication::translate("MainWindow", "&Text", nullptr));
        action_Standard_Text->setText(QCoreApplication::translate("MainWindow", "&Text", nullptr));
        actionNew_Group->setText(QCoreApplication::translate("MainWindow", "New Group", nullptr));
#if QT_CONFIG(shortcut)
        actionNew_Group->setShortcut(QCoreApplication::translate("MainWindow", "Alt+Ins", nullptr));
#endif // QT_CONFIG(shortcut)
        actionOpen_Group->setText(QCoreApplication::translate("MainWindow", "Open Group", nullptr));
        actionClolse_Group->setText(QCoreApplication::translate("MainWindow", "Close Group", nullptr));
        actionRemove_Group->setText(QCoreApplication::translate("MainWindow", "Remove Group", nullptr));
#if QT_CONFIG(shortcut)
        actionRemove_Group->setShortcut(QCoreApplication::translate("MainWindow", "Alt+Del", nullptr));
#endif // QT_CONFIG(shortcut)
        actionNew_Scene->setText(QCoreApplication::translate("MainWindow", "New Scene", nullptr));
#if QT_CONFIG(shortcut)
        actionNew_Scene->setShortcut(QCoreApplication::translate("MainWindow", "Shift+Ins", nullptr));
#endif // QT_CONFIG(shortcut)
        actionRemove_Scene->setText(QCoreApplication::translate("MainWindow", "Remove Scene", nullptr));
#if QT_CONFIG(shortcut)
        actionRemove_Scene->setShortcut(QCoreApplication::translate("MainWindow", "Shift+Del", nullptr));
#endif // QT_CONFIG(shortcut)
        actionMove_Up->setText(QCoreApplication::translate("MainWindow", "Move Up", nullptr));
#if QT_CONFIG(shortcut)
        actionMove_Up->setShortcut(QCoreApplication::translate("MainWindow", "Alt+Up", nullptr));
#endif // QT_CONFIG(shortcut)
        actionMove_Down->setText(QCoreApplication::translate("MainWindow", "Move Down", nullptr));
#if QT_CONFIG(shortcut)
        actionMove_Down->setShortcut(QCoreApplication::translate("MainWindow", "Alt+Down", nullptr));
#endif // QT_CONFIG(shortcut)
        actionMove_In->setText(QCoreApplication::translate("MainWindow", "Move In", nullptr));
#if QT_CONFIG(shortcut)
        actionMove_In->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+=", nullptr));
#endif // QT_CONFIG(shortcut)
        actionMove_Out->setText(QCoreApplication::translate("MainWindow", "Move Out", nullptr));
#if QT_CONFIG(shortcut)
        actionMove_Out->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+=", nullptr));
#endif // QT_CONFIG(shortcut)
        actionIndent->setText(QCoreApplication::translate("MainWindow", "Indent", nullptr));
#if QT_CONFIG(shortcut)
        actionIndent->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Tab", nullptr));
#endif // QT_CONFIG(shortcut)
        actionOutdent->setText(QCoreApplication::translate("MainWindow", "Outdent", nullptr));
        actionTags->setText(QCoreApplication::translate("MainWindow", "Tags", nullptr));
#if QT_CONFIG(shortcut)
        actionTags->setShortcut(QCoreApplication::translate("MainWindow", "Alt+T", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Redo->setText(QCoreApplication::translate("MainWindow", "&Redo", nullptr));
#if QT_CONFIG(shortcut)
        action_Redo->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Y", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Replace->setText(QCoreApplication::translate("MainWindow", "&Replace", nullptr));
#if QT_CONFIG(shortcut)
        action_Replace->setShortcut(QCoreApplication::translate("MainWindow", "F4", nullptr));
#endif // QT_CONFIG(shortcut)
        actionRepalce_All->setText(QCoreApplication::translate("MainWindow", "Repalce &All", nullptr));
#if QT_CONFIG(shortcut)
        actionRepalce_All->setShortcut(QCoreApplication::translate("MainWindow", "F5", nullptr));
#endif // QT_CONFIG(shortcut)
        actionFind_Next->setText(QCoreApplication::translate("MainWindow", "Find &Next", nullptr));
#if QT_CONFIG(shortcut)
        actionFind_Next->setShortcut(QCoreApplication::translate("MainWindow", "F3", nullptr));
#endif // QT_CONFIG(shortcut)
        actionReplace_Selection->setText(QCoreApplication::translate("MainWindow", "Replace &Selection", nullptr));
#if QT_CONFIG(shortcut)
        actionReplace_Selection->setShortcut(QCoreApplication::translate("MainWindow", "F5", nullptr));
#endif // QT_CONFIG(shortcut)
        actionReplace_All->setText(QCoreApplication::translate("MainWindow", "Replace &All", nullptr));
#if QT_CONFIG(shortcut)
        actionReplace_All->setShortcut(QCoreApplication::translate("MainWindow", "F6", nullptr));
#endif // QT_CONFIG(shortcut)
        actionRead_Aloud->setText(QCoreApplication::translate("MainWindow", "Read Aloud", nullptr));
#if QT_CONFIG(shortcut)
        actionRead_Aloud->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+R", nullptr));
#endif // QT_CONFIG(shortcut)
        menu_File->setTitle(QCoreApplication::translate("MainWindow", "&File", nullptr));
        menu_Export->setTitle(QCoreApplication::translate("MainWindow", "&Export", nullptr));
        menu_Import->setTitle(QCoreApplication::translate("MainWindow", "&Import", nullptr));
        menu_Edit->setTitle(QCoreApplication::translate("MainWindow", "&Edit", nullptr));
        menu_View->setTitle(QCoreApplication::translate("MainWindow", "&Utilities", nullptr));
        menu_Help->setTitle(QCoreApplication::translate("MainWindow", "&Help", nullptr));
        menu_Structure->setTitle(QCoreApplication::translate("MainWindow", "&Structure", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
