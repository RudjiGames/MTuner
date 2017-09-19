/****************************************************************************
** Meta object code from reading C++ file 'gcc.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MTuner_pch.h"
#include "../../src/gcc.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gcc.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GCCSetup_t {
    QByteArrayData data[16];
    char stringdata0[214];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GCCSetup_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GCCSetup_t qt_meta_stringdata_GCCSetup = {
    {
QT_MOC_LITERAL(0, 0, 8), // "GCCSetup"
QT_MOC_LITERAL(1, 9, 17), // "toolchainSelected"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 6), // "_index"
QT_MOC_LITERAL(4, 35, 16), // "toolchainRenamed"
QT_MOC_LITERAL(5, 52, 11), // "envEdited32"
QT_MOC_LITERAL(6, 64, 12), // "pathEdited32"
QT_MOC_LITERAL(7, 77, 12), // "pathBrowse32"
QT_MOC_LITERAL(8, 90, 14), // "prefixEdited32"
QT_MOC_LITERAL(9, 105, 11), // "envEdited64"
QT_MOC_LITERAL(10, 117, 12), // "pathEdited64"
QT_MOC_LITERAL(11, 130, 12), // "pathBrowse64"
QT_MOC_LITERAL(12, 143, 14), // "prefixEdited64"
QT_MOC_LITERAL(13, 158, 17), // "envEditedProDGps3"
QT_MOC_LITERAL(14, 176, 18), // "pathEditedProDGps3"
QT_MOC_LITERAL(15, 195, 18) // "pathBrowseProDGps3"

    },
    "GCCSetup\0toolchainSelected\0\0_index\0"
    "toolchainRenamed\0envEdited32\0pathEdited32\0"
    "pathBrowse32\0prefixEdited32\0envEdited64\0"
    "pathEdited64\0pathBrowse64\0prefixEdited64\0"
    "envEditedProDGps3\0pathEditedProDGps3\0"
    "pathBrowseProDGps3"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GCCSetup[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x0a /* Public */,
       4,    1,   82,    2, 0x0a /* Public */,
       5,    1,   85,    2, 0x0a /* Public */,
       6,    1,   88,    2, 0x0a /* Public */,
       7,    0,   91,    2, 0x0a /* Public */,
       8,    1,   92,    2, 0x0a /* Public */,
       9,    1,   95,    2, 0x0a /* Public */,
      10,    1,   98,    2, 0x0a /* Public */,
      11,    0,  101,    2, 0x0a /* Public */,
      12,    1,  102,    2, 0x0a /* Public */,
      13,    1,  105,    2, 0x0a /* Public */,
      14,    1,  108,    2, 0x0a /* Public */,
      15,    0,  111,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,

       0        // eod
};

void GCCSetup::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GCCSetup *_t = static_cast<GCCSetup *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->toolchainSelected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->toolchainRenamed((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->envEdited32((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->pathEdited32((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->pathBrowse32(); break;
        case 5: _t->prefixEdited32((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->envEdited64((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->pathEdited64((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->pathBrowse64(); break;
        case 9: _t->prefixEdited64((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->envEditedProDGps3((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->pathEditedProDGps3((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->pathBrowseProDGps3(); break;
        default: ;
        }
    }
}

const QMetaObject GCCSetup::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_GCCSetup.data,
      qt_meta_data_GCCSetup,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *GCCSetup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GCCSetup::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GCCSetup.stringdata0))
        return static_cast<void*>(const_cast< GCCSetup*>(this));
    return QDialog::qt_metacast(_clname);
}

int GCCSetup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
