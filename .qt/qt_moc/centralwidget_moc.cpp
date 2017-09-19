/****************************************************************************
** Meta object code from reading C++ file 'centralwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MTuner_pch.h"
#include "../../src/centralwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'centralwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CentralWidget_t {
    QByteArrayData data[14];
    char stringdata0[193];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CentralWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CentralWidget_t qt_meta_stringdata_CentralWidget = {
    {
QT_MOC_LITERAL(0, 0, 13), // "CentralWidget"
QT_MOC_LITERAL(1, 14, 14), // "contextChanged"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 15), // "CaptureContext*"
QT_MOC_LITERAL(4, 46, 5), // "_view"
QT_MOC_LITERAL(5, 52, 17), // "changeWindowTitle"
QT_MOC_LITERAL(6, 70, 13), // "setStackTrace"
QT_MOC_LITERAL(7, 84, 17), // "rtm::StackTrace**"
QT_MOC_LITERAL(8, 102, 19), // "setFilteringEnabled"
QT_MOC_LITERAL(9, 122, 19), // "tabSelectionChanged"
QT_MOC_LITERAL(10, 142, 9), // "_tabIndex"
QT_MOC_LITERAL(11, 152, 8), // "tabClose"
QT_MOC_LITERAL(12, 161, 6), // "_index"
QT_MOC_LITERAL(13, 168, 24) // "updateFilterDataIfNeeded"

    },
    "CentralWidget\0contextChanged\0\0"
    "CaptureContext*\0_view\0changeWindowTitle\0"
    "setStackTrace\0rtm::StackTrace**\0"
    "setFilteringEnabled\0tabSelectionChanged\0"
    "_tabIndex\0tabClose\0_index\0"
    "updateFilterDataIfNeeded"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CentralWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       5,    1,   52,    2, 0x06 /* Public */,
       6,    2,   55,    2, 0x06 /* Public */,
       8,    2,   60,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   65,    2, 0x0a /* Public */,
      11,    1,   68,    2, 0x0a /* Public */,
      13,    0,   71,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 7, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,

       0        // eod
};

void CentralWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CentralWidget *_t = static_cast<CentralWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->contextChanged((*reinterpret_cast< CaptureContext*(*)>(_a[1]))); break;
        case 1: _t->changeWindowTitle((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->setStackTrace((*reinterpret_cast< rtm::StackTrace**(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->setFilteringEnabled((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 4: _t->tabSelectionChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->tabClose((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->updateFilterDataIfNeeded(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CentralWidget::*_t)(CaptureContext * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CentralWidget::contextChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CentralWidget::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CentralWidget::changeWindowTitle)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (CentralWidget::*_t)(rtm::StackTrace * * , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CentralWidget::setStackTrace)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (CentralWidget::*_t)(bool , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CentralWidget::setFilteringEnabled)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject CentralWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CentralWidget.data,
      qt_meta_data_CentralWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CentralWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CentralWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CentralWidget.stringdata0))
        return static_cast<void*>(const_cast< CentralWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int CentralWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void CentralWidget::contextChanged(CaptureContext * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CentralWidget::changeWindowTitle(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CentralWidget::setStackTrace(rtm::StackTrace * * _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CentralWidget::setFilteringEnabled(bool _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
