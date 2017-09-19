/****************************************************************************
** Meta object code from reading C++ file 'bigtable.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MTuner_pch.h"
#include "../../src/bigtable.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bigtable.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BigTable_t {
    QByteArrayData data[10];
    char stringdata0[119];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BigTable_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BigTable_t qt_meta_stringdata_BigTable = {
    {
QT_MOC_LITERAL(0, 0, 8), // "BigTable"
QT_MOC_LITERAL(1, 9, 12), // "itemSelected"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 16), // "itemRightClicked"
QT_MOC_LITERAL(4, 40, 6), // "scroll"
QT_MOC_LITERAL(5, 47, 11), // "rowSelected"
QT_MOC_LITERAL(6, 59, 17), // "QTableWidgetItem*"
QT_MOC_LITERAL(7, 77, 13), // "rowRightClick"
QT_MOC_LITERAL(8, 91, 13), // "sortSelection"
QT_MOC_LITERAL(9, 105, 13) // "Qt::SortOrder"

    },
    "BigTable\0itemSelected\0\0itemRightClicked\0"
    "scroll\0rowSelected\0QTableWidgetItem*\0"
    "rowRightClick\0sortSelection\0Qt::SortOrder"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BigTable[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       3,    2,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   52,    2, 0x0a /* Public */,
       5,    1,   55,    2, 0x0a /* Public */,
       7,    2,   58,    2, 0x0a /* Public */,
       8,    2,   63,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::VoidStar,    2,
    QMetaType::Void, QMetaType::VoidStar, QMetaType::QPoint,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void, 0x80000000 | 6, QMetaType::QPoint,    2,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 9,    2,    2,

       0        // eod
};

void BigTable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BigTable *_t = static_cast<BigTable *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->itemSelected((*reinterpret_cast< void*(*)>(_a[1]))); break;
        case 1: _t->itemRightClicked((*reinterpret_cast< void*(*)>(_a[1])),(*reinterpret_cast< const QPoint(*)>(_a[2]))); break;
        case 2: _t->scroll((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->rowSelected((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->rowRightClick((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1])),(*reinterpret_cast< const QPoint(*)>(_a[2]))); break;
        case 5: _t->sortSelection((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< Qt::SortOrder(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (BigTable::*_t)(void * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BigTable::itemSelected)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (BigTable::*_t)(void * , const QPoint & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BigTable::itemRightClicked)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject BigTable::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_BigTable.data,
      qt_meta_data_BigTable,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *BigTable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BigTable::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BigTable.stringdata0))
        return static_cast<void*>(const_cast< BigTable*>(this));
    return QWidget::qt_metacast(_clname);
}

int BigTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void BigTable::itemSelected(void * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BigTable::itemRightClicked(void * _t1, const QPoint & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
