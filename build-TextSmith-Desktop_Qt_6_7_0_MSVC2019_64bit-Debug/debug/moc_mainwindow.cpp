/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TextSmith/mainwindow.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSFindDialogENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSFindDialogENDCLASS = QtMocHelpers::stringData(
    "FindDialog",
    "changedText",
    ""
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSFindDialogENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   20,    2, 0x0a,    1 /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

Q_CONSTINIT const QMetaObject FindDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSFindDialogENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSFindDialogENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSFindDialogENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<FindDialog, std::true_type>,
        // method 'changedText'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>
    >,
    nullptr
} };

void FindDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FindDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->changedText((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *FindDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FindDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSFindDialogENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int FindDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
    }
    return _id;
}
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSReplaceDialogENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSReplaceDialogENDCLASS = QtMocHelpers::stringData(
    "ReplaceDialog",
    "changedText",
    "",
    "text"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSReplaceDialogENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   20,    2, 0x0a,    1 /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

Q_CONSTINIT const QMetaObject ReplaceDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSReplaceDialogENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSReplaceDialogENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSReplaceDialogENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ReplaceDialog, std::true_type>,
        // method 'changedText'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
    >,
    nullptr
} };

void ReplaceDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ReplaceDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->changedText((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *ReplaceDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ReplaceDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSReplaceDialogENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int ReplaceDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
    }
    return _id;
}
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "newMenuItem",
    "",
    "openMenuItem",
    "saveMenuItem",
    "saveAsMenuItem",
    "aboutToShowExportMenu",
    "aboutToHideExportMenu",
    "pdfMenuItem",
    "epubMenuItem",
    "htmlMenuItem",
    "markdownMenuItem",
    "rtfMenuItem",
    "standardTextMenuItem",
    "aboutToShowImportMenu",
    "aboutToHideImportMenu",
    "imageMenuItem",
    "textMenuItem",
    "exitClicked",
    "newSceneMenuItem",
    "removeSceneMenuItem",
    "moveUpMenuItem",
    "moveDownMenuItem",
    "moveInMenuItem",
    "moveOutMenuItem",
    "tagsMenuItem",
    "undoMenuItem",
    "redoMenuItem",
    "cutMenuItem",
    "copyMenuItem",
    "pasteMenuItem",
    "searchMenuItem",
    "replaceMenuItem",
    "replaceSelectionMenuItem",
    "replaceAllMenuItem",
    "findNextMenuItem",
    "boldMenuItem",
    "italicMenuItem",
    "underlineMenuItem",
    "leftJustifyMenuItem",
    "centerMenuItem",
    "fullJustifyMenuItem",
    "rightJustifyMenuItem",
    "indentMenuItem",
    "fullScreenMenuItem",
    "scriptsMenuItem",
    "wordCountMenuItem",
    "readAloudMenuItem",
    "aboutMenuItem",
    "documentationMenuItem",
    "optionsMenuItem",
    "currentItemChanged",
    "QTreeWidgetItem*",
    "current",
    "previous",
    "itemDoubleClicked",
    "column",
    "redoAvailable",
    "available",
    "setEditButtons",
    "undoAvailable",
    "textChanged",
    "autoSave",
    "checkDarkMode",
    "cleanIt"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      58,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  362,    2, 0x0a,    1 /* Public */,
       3,    0,  363,    2, 0x0a,    2 /* Public */,
       4,    0,  364,    2, 0x0a,    3 /* Public */,
       5,    0,  365,    2, 0x0a,    4 /* Public */,
       6,    0,  366,    2, 0x0a,    5 /* Public */,
       7,    0,  367,    2, 0x0a,    6 /* Public */,
       8,    0,  368,    2, 0x0a,    7 /* Public */,
       9,    0,  369,    2, 0x0a,    8 /* Public */,
      10,    0,  370,    2, 0x0a,    9 /* Public */,
      11,    0,  371,    2, 0x0a,   10 /* Public */,
      12,    0,  372,    2, 0x0a,   11 /* Public */,
      13,    0,  373,    2, 0x0a,   12 /* Public */,
      14,    0,  374,    2, 0x0a,   13 /* Public */,
      15,    0,  375,    2, 0x0a,   14 /* Public */,
      16,    0,  376,    2, 0x0a,   15 /* Public */,
      17,    0,  377,    2, 0x0a,   16 /* Public */,
      18,    0,  378,    2, 0x0a,   17 /* Public */,
      19,    0,  379,    2, 0x0a,   18 /* Public */,
      20,    0,  380,    2, 0x0a,   19 /* Public */,
      21,    0,  381,    2, 0x0a,   20 /* Public */,
      22,    0,  382,    2, 0x0a,   21 /* Public */,
      23,    0,  383,    2, 0x0a,   22 /* Public */,
      24,    0,  384,    2, 0x0a,   23 /* Public */,
      25,    0,  385,    2, 0x0a,   24 /* Public */,
      26,    0,  386,    2, 0x0a,   25 /* Public */,
      27,    0,  387,    2, 0x0a,   26 /* Public */,
      28,    0,  388,    2, 0x0a,   27 /* Public */,
      29,    0,  389,    2, 0x0a,   28 /* Public */,
      30,    0,  390,    2, 0x0a,   29 /* Public */,
      31,    0,  391,    2, 0x0a,   30 /* Public */,
      32,    0,  392,    2, 0x0a,   31 /* Public */,
      33,    0,  393,    2, 0x0a,   32 /* Public */,
      34,    0,  394,    2, 0x0a,   33 /* Public */,
      35,    0,  395,    2, 0x0a,   34 /* Public */,
      36,    0,  396,    2, 0x0a,   35 /* Public */,
      37,    0,  397,    2, 0x0a,   36 /* Public */,
      38,    0,  398,    2, 0x0a,   37 /* Public */,
      39,    0,  399,    2, 0x0a,   38 /* Public */,
      40,    0,  400,    2, 0x0a,   39 /* Public */,
      41,    0,  401,    2, 0x0a,   40 /* Public */,
      42,    0,  402,    2, 0x0a,   41 /* Public */,
      43,    0,  403,    2, 0x0a,   42 /* Public */,
      44,    0,  404,    2, 0x0a,   43 /* Public */,
      45,    0,  405,    2, 0x0a,   44 /* Public */,
      46,    0,  406,    2, 0x0a,   45 /* Public */,
      47,    0,  407,    2, 0x0a,   46 /* Public */,
      48,    0,  408,    2, 0x0a,   47 /* Public */,
      49,    0,  409,    2, 0x0a,   48 /* Public */,
      50,    0,  410,    2, 0x0a,   49 /* Public */,
      51,    2,  411,    2, 0x0a,   50 /* Public */,
      55,    2,  416,    2, 0x0a,   53 /* Public */,
      57,    1,  421,    2, 0x0a,   56 /* Public */,
      59,    0,  424,    2, 0x0a,   58 /* Public */,
      60,    1,  425,    2, 0x0a,   59 /* Public */,
      61,    0,  428,    2, 0x0a,   61 /* Public */,
      62,    0,  429,    2, 0x0a,   62 /* Public */,
      63,    0,  430,    2, 0x0a,   63 /* Public */,
      64,    0,  431,    2, 0x0a,   64 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 52, 0x80000000 | 52,   53,   54,
    QMetaType::Void, 0x80000000 | 52, QMetaType::Int,   53,   56,
    QMetaType::Void, QMetaType::Bool,   58,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   58,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'newMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'openMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveAsMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'aboutToShowExportMenu'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'aboutToHideExportMenu'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pdfMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'epubMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'htmlMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'markdownMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'rtfMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'standardTextMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'aboutToShowImportMenu'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'aboutToHideImportMenu'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'imageMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'textMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'exitClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'newSceneMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'removeSceneMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'moveUpMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'moveDownMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'moveInMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'moveOutMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'tagsMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'undoMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'redoMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'cutMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'copyMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pasteMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'searchMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'replaceMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'replaceSelectionMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'replaceAllMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'findNextMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'boldMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'italicMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'underlineMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'leftJustifyMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'centerMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'fullJustifyMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'rightJustifyMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'indentMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'fullScreenMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'scriptsMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'wordCountMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'readAloudMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'aboutMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'documentationMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'optionsMenuItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'currentItemChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QTreeWidgetItem *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QTreeWidgetItem *, std::false_type>,
        // method 'itemDoubleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QTreeWidgetItem *, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'redoAvailable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setEditButtons'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'undoAvailable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'textChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'autoSave'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'checkDarkMode'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'cleanIt'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->newMenuItem(); break;
        case 1: _t->openMenuItem(); break;
        case 2: _t->saveMenuItem(); break;
        case 3: _t->saveAsMenuItem(); break;
        case 4: _t->aboutToShowExportMenu(); break;
        case 5: _t->aboutToHideExportMenu(); break;
        case 6: _t->pdfMenuItem(); break;
        case 7: _t->epubMenuItem(); break;
        case 8: _t->htmlMenuItem(); break;
        case 9: _t->markdownMenuItem(); break;
        case 10: _t->rtfMenuItem(); break;
        case 11: _t->standardTextMenuItem(); break;
        case 12: _t->aboutToShowImportMenu(); break;
        case 13: _t->aboutToHideImportMenu(); break;
        case 14: _t->imageMenuItem(); break;
        case 15: _t->textMenuItem(); break;
        case 16: _t->exitClicked(); break;
        case 17: _t->newSceneMenuItem(); break;
        case 18: _t->removeSceneMenuItem(); break;
        case 19: _t->moveUpMenuItem(); break;
        case 20: _t->moveDownMenuItem(); break;
        case 21: _t->moveInMenuItem(); break;
        case 22: _t->moveOutMenuItem(); break;
        case 23: _t->tagsMenuItem(); break;
        case 24: _t->undoMenuItem(); break;
        case 25: _t->redoMenuItem(); break;
        case 26: _t->cutMenuItem(); break;
        case 27: _t->copyMenuItem(); break;
        case 28: _t->pasteMenuItem(); break;
        case 29: _t->searchMenuItem(); break;
        case 30: _t->replaceMenuItem(); break;
        case 31: _t->replaceSelectionMenuItem(); break;
        case 32: _t->replaceAllMenuItem(); break;
        case 33: _t->findNextMenuItem(); break;
        case 34: _t->boldMenuItem(); break;
        case 35: _t->italicMenuItem(); break;
        case 36: _t->underlineMenuItem(); break;
        case 37: _t->leftJustifyMenuItem(); break;
        case 38: _t->centerMenuItem(); break;
        case 39: _t->fullJustifyMenuItem(); break;
        case 40: _t->rightJustifyMenuItem(); break;
        case 41: _t->indentMenuItem(); break;
        case 42: _t->fullScreenMenuItem(); break;
        case 43: _t->scriptsMenuItem(); break;
        case 44: _t->wordCountMenuItem(); break;
        case 45: _t->readAloudMenuItem(); break;
        case 46: _t->aboutMenuItem(); break;
        case 47: _t->documentationMenuItem(); break;
        case 48: _t->optionsMenuItem(); break;
        case 49: _t->currentItemChanged((*reinterpret_cast< std::add_pointer_t<QTreeWidgetItem*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QTreeWidgetItem*>>(_a[2]))); break;
        case 50: _t->itemDoubleClicked((*reinterpret_cast< std::add_pointer_t<QTreeWidgetItem*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 51: _t->redoAvailable((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 52: _t->setEditButtons(); break;
        case 53: _t->undoAvailable((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 54: _t->textChanged(); break;
        case 55: _t->autoSave(); break;
        case 56: _t->checkDarkMode(); break;
        case 57: _t->cleanIt(); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 58)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 58;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 58)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 58;
    }
    return _id;
}
QT_WARNING_POP
