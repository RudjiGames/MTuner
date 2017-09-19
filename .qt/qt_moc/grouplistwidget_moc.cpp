/****************************************************************************
** Meta object code from reading C++ file 'grouplistwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MTuner_pch.h"
#include "../../src/grouplistwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'grouplistwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GroupList_t {
    QByteArrayData data[20];
    char stringdata0[308];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GroupList_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GroupList_t qt_meta_stringdata_GroupList = {
    {
QT_MOC_LITERAL(0, 0, 9), // "GroupList"
QT_MOC_LITERAL(1, 10, 13), // "setStackTrace"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 17), // "rtm::StackTrace**"
QT_MOC_LITERAL(4, 43, 16), // "usageSortingDone"
QT_MOC_LITERAL(5, 60, 13), // "GroupMapping*"
QT_MOC_LITERAL(6, 74, 20), // "peakUsageSortingDone"
QT_MOC_LITERAL(7, 95, 20), // "peakCountSortingDone"
QT_MOC_LITERAL(8, 116, 16), // "leaksSortingDone"
QT_MOC_LITERAL(9, 133, 13), // "highlightTime"
QT_MOC_LITERAL(10, 147, 8), // "uint64_t"
QT_MOC_LITERAL(11, 156, 14), // "highlightRange"
QT_MOC_LITERAL(12, 171, 11), // "selectRange"
QT_MOC_LITERAL(13, 183, 16), // "selectionChanged"
QT_MOC_LITERAL(14, 200, 15), // "groupRightClick"
QT_MOC_LITERAL(15, 216, 16), // "sortingDoneUsage"
QT_MOC_LITERAL(16, 233, 20), // "sortingDonePeakUsage"
QT_MOC_LITERAL(17, 254, 20), // "sortingDonePeakCount"
QT_MOC_LITERAL(18, 275, 16), // "sortingDoneLeaks"
QT_MOC_LITERAL(19, 292, 15) // "selectTriggered"

    },
    "GroupList\0setStackTrace\0\0rtm::StackTrace**\0"
    "usageSortingDone\0GroupMapping*\0"
    "peakUsageSortingDone\0peakCountSortingDone\0"
    "leaksSortingDone\0highlightTime\0uint64_t\0"
    "highlightRange\0selectRange\0selectionChanged\0"
    "groupRightClick\0sortingDoneUsage\0"
    "sortingDonePeakUsage\0sortingDonePeakCount\0"
    "sortingDoneLeaks\0selectTriggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GroupList[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   89,    2, 0x06 /* Public */,
       4,    1,   94,    2, 0x06 /* Public */,
       6,    1,   97,    2, 0x06 /* Public */,
       7,    1,  100,    2, 0x06 /* Public */,
       8,    1,  103,    2, 0x06 /* Public */,
       9,    1,  106,    2, 0x06 /* Public */,
      11,    2,  109,    2, 0x06 /* Public */,
      12,    2,  114,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    1,  119,    2, 0x0a /* Public */,
      14,    2,  122,    2, 0x0a /* Public */,
      15,    0,  127,    2, 0x0a /* Public */,
      16,    0,  128,    2, 0x0a /* Public */,
      17,    0,  129,    2, 0x0a /* Public */,
      18,    0,  130,    2, 0x0a /* Public */,
      19,    0,  131,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 10,    2,
    QMetaType::Void, 0x80000000 | 10, 0x80000000 | 10,    2,    2,
    QMetaType::Void, 0x80000000 | 10, 0x80000000 | 10,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::VoidStar,    2,
    QMetaType::Void, QMetaType::VoidStar, QMetaType::QPoint,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GroupList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GroupList *_t = static_cast<GroupList *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setStackTrace((*reinterpret_cast< rtm::StackTrace**(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->usageSortingDone((*reinterpret_cast< GroupMapping*(*)>(_a[1]))); break;
        case 2: _t->peakUsageSortingDone((*reinterpret_cast< GroupMapping*(*)>(_a[1]))); break;
        case 3: _t->peakCountSortingDone((*reinterpret_cast< GroupMapping*(*)>(_a[1]))); break;
        case 4: _t->leaksSortingDone((*reinterpret_cast< GroupMapping*(*)>(_a[1]))); break;
        case 5: _t->highlightTime((*reinterpret_cast< uint64_t(*)>(_a[1]))); break;
        case 6: _t->highlightRange((*reinterpret_cast< uint64_t(*)>(_a[1])),(*reinterpret_cast< uint64_t(*)>(_a[2]))); break;
        case 7: _t->selectRange((*reinterpret_cast< uint64_t(*)>(_a[1])),(*reinterpret_cast< uint64_t(*)>(_a[2]))); break;
        case 8: _t->selectionChanged((*reinterpret_cast< void*(*)>(_a[1]))); break;
        case 9: _t->groupRightClick((*reinterpret_cast< void*(*)>(_a[1])),(*reinterpret_cast< const QPoint(*)>(_a[2]))); break;
        case 10: _t->sortingDoneUsage(); break;
        case 11: _t->sortingDonePeakUsage(); break;
        case 12: _t->sortingDonePeakCount(); break;
        case 13: _t->sortingDoneLeaks(); break;
        case 14: _t->selectTriggered(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GroupList::*_t)(rtm::StackTrace * * , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GroupList::setStackTrace)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (GroupList::*_t)(GroupMapping * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GroupList::usageSortingDone)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (GroupList::*_t)(GroupMapping * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GroupList::peakUsageSortingDone)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (GroupList::*_t)(GroupMapping * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GroupList::peakCountSortingDone)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (GroupList::*_t)(GroupMapping * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GroupList::leaksSortingDone)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (GroupList::*_t)(uint64_t );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GroupList::highlightTime)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (GroupList::*_t)(uint64_t , uint64_t );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GroupList::highlightRange)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (GroupList::*_t)(uint64_t , uint64_t );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GroupList::selectRange)) {
                *result = 7;
                return;
            }
        }
    }
}

const QMetaObject GroupList::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GroupList.data,
      qt_meta_data_GroupList,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *GroupList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GroupList::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GroupList.stringdata0))
        return static_cast<void*>(const_cast< GroupList*>(this));
    return QWidget::qt_metacast(_clname);
}

int GroupList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void GroupList::setStackTrace(rtm::StackTrace * * _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GroupList::usageSortingDone(GroupMapping * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GroupList::peakUsageSortingDone(GroupMapping * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GroupList::peakCountSortingDone(GroupMapping * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GroupList::leaksSortingDone(GroupMapping * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void GroupList::highlightTime(uint64_t _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void GroupList::highlightRange(uint64_t _t1, uint64_t _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void GroupList::selectRange(uint64_t _t1, uint64_t _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
