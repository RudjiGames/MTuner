/****************************************************************************
** Meta object code from reading C++ file 'hotspots.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MTuner_pch.h"
#include "../../src/hotspots.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hotspots.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HotspotsWidget_t {
    QByteArrayData data[11];
    char stringdata0[168];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HotspotsWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HotspotsWidget_t qt_meta_stringdata_HotspotsWidget = {
    {
QT_MOC_LITERAL(0, 0, 14), // "HotspotsWidget"
QT_MOC_LITERAL(1, 15, 13), // "setStackTrace"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 17), // "rtm::StackTrace**"
QT_MOC_LITERAL(4, 48, 16), // "usageSortingDone"
QT_MOC_LITERAL(5, 65, 13), // "GroupMapping*"
QT_MOC_LITERAL(6, 79, 20), // "peakUsageSortingDone"
QT_MOC_LITERAL(7, 100, 20), // "peakCountSortingDone"
QT_MOC_LITERAL(8, 121, 16), // "leaksSortingDone"
QT_MOC_LITERAL(9, 138, 11), // "rowSelected"
QT_MOC_LITERAL(10, 150, 17) // "QTableWidgetItem*"

    },
    "HotspotsWidget\0setStackTrace\0\0"
    "rtm::StackTrace**\0usageSortingDone\0"
    "GroupMapping*\0peakUsageSortingDone\0"
    "peakCountSortingDone\0leaksSortingDone\0"
    "rowSelected\0QTableWidgetItem*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HotspotsWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   49,    2, 0x0a /* Public */,
       6,    1,   52,    2, 0x0a /* Public */,
       7,    1,   55,    2, 0x0a /* Public */,
       8,    1,   58,    2, 0x0a /* Public */,
       9,    1,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 10,    2,

       0        // eod
};

void HotspotsWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HotspotsWidget *_t = static_cast<HotspotsWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setStackTrace((*reinterpret_cast< rtm::StackTrace**(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->usageSortingDone((*reinterpret_cast< GroupMapping*(*)>(_a[1]))); break;
        case 2: _t->peakUsageSortingDone((*reinterpret_cast< GroupMapping*(*)>(_a[1]))); break;
        case 3: _t->peakCountSortingDone((*reinterpret_cast< GroupMapping*(*)>(_a[1]))); break;
        case 4: _t->leaksSortingDone((*reinterpret_cast< GroupMapping*(*)>(_a[1]))); break;
        case 5: _t->rowSelected((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (HotspotsWidget::*_t)(rtm::StackTrace * * , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HotspotsWidget::setStackTrace)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject HotspotsWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_HotspotsWidget.data,
      qt_meta_data_HotspotsWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *HotspotsWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HotspotsWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_HotspotsWidget.stringdata0))
        return static_cast<void*>(const_cast< HotspotsWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int HotspotsWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void HotspotsWidget::setStackTrace(rtm::StackTrace * * _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
