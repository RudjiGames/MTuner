/****************************************************************************
** Meta object code from reading C++ file 'symbolstore.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MTuner_pch.h"
#include "../../src/symbolstore.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'symbolstore.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SymbolStore_t {
    QByteArrayData data[8];
    char stringdata0[79];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SymbolStore_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SymbolStore_t qt_meta_stringdata_SymbolStore = {
    {
QT_MOC_LITERAL(0, 0, 11), // "SymbolStore"
QT_MOC_LITERAL(1, 12, 16), // "selectLocalStore"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 19), // "defaultSymbolServer"
QT_MOC_LITERAL(4, 50, 9), // "visitMSDN"
QT_MOC_LITERAL(5, 60, 4), // "exec"
QT_MOC_LITERAL(6, 65, 6), // "accept"
QT_MOC_LITERAL(7, 72, 6) // "reject"

    },
    "SymbolStore\0selectLocalStore\0\0"
    "defaultSymbolServer\0visitMSDN\0exec\0"
    "accept\0reject"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SymbolStore[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    0,   45,    2, 0x0a /* Public */,
       4,    0,   46,    2, 0x0a /* Public */,
       5,    0,   47,    2, 0x0a /* Public */,
       6,    0,   48,    2, 0x0a /* Public */,
       7,    0,   49,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SymbolStore::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SymbolStore *_t = static_cast<SymbolStore *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->selectLocalStore(); break;
        case 1: _t->defaultSymbolServer(); break;
        case 2: _t->visitMSDN(); break;
        case 3: { int _r = _t->exec();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->accept(); break;
        case 5: _t->reject(); break;
        default: ;
        }
    }
}

const QMetaObject SymbolStore::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SymbolStore.data,
      qt_meta_data_SymbolStore,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SymbolStore::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SymbolStore::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SymbolStore.stringdata0))
        return static_cast<void*>(const_cast< SymbolStore*>(this));
    return QDialog::qt_metacast(_clname);
}

int SymbolStore::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
