/****************************************************************************
** Meta object code from reading C++ file 'scriptsdialog.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TextSmith/scriptsdialog.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scriptsdialog.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSScriptsDialogENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSScriptsDialogENDCLASS = QtMocHelpers::stringData(
    "ScriptsDialog",
    "add",
    "",
    "deleteIt",
    "doubleClicked",
    "QListWidgetItem*",
    "refresh",
    "run"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSScriptsDialogENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x0a,    1 /* Public */,
       3,    0,   45,    2, 0x0a,    2 /* Public */,
       4,    1,   46,    2, 0x0a,    3 /* Public */,
       6,    0,   49,    2, 0x0a,    5 /* Public */,
       7,    0,   50,    2, 0x0a,    6 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject ScriptsDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSScriptsDialogENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSScriptsDialogENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSScriptsDialogENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ScriptsDialog, std::true_type>,
        // method 'add'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'deleteIt'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'doubleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QListWidgetItem *, std::false_type>,
        // method 'refresh'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'run'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void ScriptsDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ScriptsDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->add(); break;
        case 1: _t->deleteIt(); break;
        case 2: _t->doubleClicked((*reinterpret_cast< std::add_pointer_t<QListWidgetItem*>>(_a[1]))); break;
        case 3: _t->refresh(); break;
        case 4: _t->run(); break;
        default: ;
        }
    }
}

const QMetaObject *ScriptsDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScriptsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSScriptsDialogENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int ScriptsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
