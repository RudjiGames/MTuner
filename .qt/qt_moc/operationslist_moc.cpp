/****************************************************************************
** Meta object code from reading C++ file 'operationslist.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MTuner_pch.h"
#include "../../src/operationslist.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'operationslist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_OperationsList_t {
    QByteArrayData data[11];
    char stringdata0[151];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OperationsList_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OperationsList_t qt_meta_stringdata_OperationsList = {
    {
QT_MOC_LITERAL(0, 0, 14), // "OperationsList"
QT_MOC_LITERAL(1, 15, 13), // "setStackTrace"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 17), // "rtm::StackTrace**"
QT_MOC_LITERAL(4, 48, 13), // "highlightTime"
QT_MOC_LITERAL(5, 62, 8), // "uint64_t"
QT_MOC_LITERAL(6, 71, 16), // "selectionChanged"
QT_MOC_LITERAL(7, 88, 14), // "selectPrevious"
QT_MOC_LITERAL(8, 103, 10), // "selectNext"
QT_MOC_LITERAL(9, 114, 19), // "selectNextByAddress"
QT_MOC_LITERAL(10, 134, 16) // "selectNextBySize"

    },
    "OperationsList\0setStackTrace\0\0"
    "rtm::StackTrace**\0highlightTime\0"
    "uint64_t\0selectionChanged\0selectPrevious\0"
    "selectNext\0selectNextByAddress\0"
    "selectNextBySize"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OperationsList[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   49,    2, 0x06 /* Public */,
       4,    1,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   57,    2, 0x0a /* Public */,
       7,    0,   60,    2, 0x0a /* Public */,
       8,    0,   61,    2, 0x0a /* Public */,
       9,    1,   62,    2, 0x0a /* Public */,
      10,    1,   65,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 5,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::VoidStar,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 5,    2,

       0        // eod
};

void OperationsList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OperationsList *_t = static_cast<OperationsList *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setStackTrace((*reinterpret_cast< rtm::StackTrace**(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->highlightTime((*reinterpret_cast< uint64_t(*)>(_a[1]))); break;
        case 2: _t->selectionChanged((*reinterpret_cast< void*(*)>(_a[1]))); break;
        case 3: _t->selectPrevious(); break;
        case 4: _t->selectNext(); break;
        case 5: _t->selectNextByAddress((*reinterpret_cast< uint64_t(*)>(_a[1]))); break;
        case 6: _t->selectNextBySize((*reinterpret_cast< uint64_t(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (OperationsList::*_t)(rtm::StackTrace * * , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OperationsList::setStackTrace)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (OperationsList::*_t)(uint64_t );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OperationsList::highlightTime)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject OperationsList::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_OperationsList.data,
      qt_meta_data_OperationsList,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *OperationsList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OperationsList::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_OperationsList.stringdata0))
        return static_cast<void*>(const_cast< OperationsList*>(this));
    return QWidget::qt_metacast(_clname);
}

int OperationsList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void OperationsList::setStackTrace(rtm::StackTrace * * _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void OperationsList::highlightTime(uint64_t _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
