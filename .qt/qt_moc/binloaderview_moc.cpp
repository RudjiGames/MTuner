/****************************************************************************
** Meta object code from reading C++ file 'binloaderview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MTuner_pch.h"
#include "../../src/binloaderview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'binloaderview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BinLoaderView_t {
    QByteArrayData data[9];
    char stringdata0[112];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BinLoaderView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BinLoaderView_t qt_meta_stringdata_BinLoaderView = {
    {
QT_MOC_LITERAL(0, 0, 13), // "BinLoaderView"
QT_MOC_LITERAL(1, 14, 13), // "setStackTrace"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 17), // "rtm::StackTrace**"
QT_MOC_LITERAL(4, 47, 13), // "highlightTime"
QT_MOC_LITERAL(5, 61, 8), // "uint64_t"
QT_MOC_LITERAL(6, 70, 14), // "highlightRange"
QT_MOC_LITERAL(7, 85, 11), // "selectRange"
QT_MOC_LITERAL(8, 97, 14) // "saveStackTrace"

    },
    "BinLoaderView\0setStackTrace\0\0"
    "rtm::StackTrace**\0highlightTime\0"
    "uint64_t\0highlightRange\0selectRange\0"
    "saveStackTrace"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BinLoaderView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x06 /* Public */,
       4,    1,   44,    2, 0x06 /* Public */,
       6,    2,   47,    2, 0x06 /* Public */,
       7,    2,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    2,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 5,    2,    2,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 5,    2,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,

       0        // eod
};

void BinLoaderView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BinLoaderView *_t = static_cast<BinLoaderView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setStackTrace((*reinterpret_cast< rtm::StackTrace**(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->highlightTime((*reinterpret_cast< uint64_t(*)>(_a[1]))); break;
        case 2: _t->highlightRange((*reinterpret_cast< uint64_t(*)>(_a[1])),(*reinterpret_cast< uint64_t(*)>(_a[2]))); break;
        case 3: _t->selectRange((*reinterpret_cast< uint64_t(*)>(_a[1])),(*reinterpret_cast< uint64_t(*)>(_a[2]))); break;
        case 4: _t->saveStackTrace((*reinterpret_cast< rtm::StackTrace**(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (BinLoaderView::*_t)(rtm::StackTrace * * , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BinLoaderView::setStackTrace)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (BinLoaderView::*_t)(uint64_t );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BinLoaderView::highlightTime)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (BinLoaderView::*_t)(uint64_t , uint64_t );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BinLoaderView::highlightRange)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (BinLoaderView::*_t)(uint64_t , uint64_t );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BinLoaderView::selectRange)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject BinLoaderView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_BinLoaderView.data,
      qt_meta_data_BinLoaderView,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *BinLoaderView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BinLoaderView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BinLoaderView.stringdata0))
        return static_cast<void*>(const_cast< BinLoaderView*>(this));
    return QWidget::qt_metacast(_clname);
}

int BinLoaderView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void BinLoaderView::setStackTrace(rtm::StackTrace * * _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BinLoaderView::highlightTime(uint64_t _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void BinLoaderView::highlightRange(uint64_t _t1, uint64_t _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void BinLoaderView::selectRange(uint64_t _t1, uint64_t _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
