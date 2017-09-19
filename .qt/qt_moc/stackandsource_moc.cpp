/****************************************************************************
** Meta object code from reading C++ file 'stackandsource.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MTuner_pch.h"
#include "../../src/stackandsource.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'stackandsource.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_StackAndSource_t {
    QByteArrayData data[6];
    char stringdata0[75];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StackAndSource_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StackAndSource_t qt_meta_stringdata_StackAndSource = {
    {
QT_MOC_LITERAL(0, 0, 14), // "StackAndSource"
QT_MOC_LITERAL(1, 15, 10), // "setContext"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 15), // "CaptureContext*"
QT_MOC_LITERAL(4, 43, 13), // "setStackTrace"
QT_MOC_LITERAL(5, 57, 17) // "rtm::StackTrace**"

    },
    "StackAndSource\0setContext\0\0CaptureContext*\0"
    "setStackTrace\0rtm::StackTrace**"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StackAndSource[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x0a /* Public */,
       4,    2,   27,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5, QMetaType::Int,    2,    2,

       0        // eod
};

void StackAndSource::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StackAndSource *_t = static_cast<StackAndSource *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setContext((*reinterpret_cast< CaptureContext*(*)>(_a[1]))); break;
        case 1: _t->setStackTrace((*reinterpret_cast< rtm::StackTrace**(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject StackAndSource::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_StackAndSource.data,
      qt_meta_data_StackAndSource,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *StackAndSource::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StackAndSource::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StackAndSource.stringdata0))
        return static_cast<void*>(const_cast< StackAndSource*>(this));
    return QWidget::qt_metacast(_clname);
}

int StackAndSource::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
