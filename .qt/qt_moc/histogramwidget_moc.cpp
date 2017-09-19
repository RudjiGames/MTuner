/****************************************************************************
** Meta object code from reading C++ file 'histogramwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MTuner_pch.h"
#include "../../src/histogramwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'histogramwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HistogramWidget_t {
    QByteArrayData data[9];
    char stringdata0[106];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HistogramWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HistogramWidget_t qt_meta_stringdata_HistogramWidget = {
    {
QT_MOC_LITERAL(0, 0, 15), // "HistogramWidget"
QT_MOC_LITERAL(1, 16, 10), // "binClicked"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 8), // "updateUI"
QT_MOC_LITERAL(4, 37, 18), // "displayTypeChanged"
QT_MOC_LITERAL(5, 56, 6), // "_index"
QT_MOC_LITERAL(6, 63, 18), // "displayModeChanged"
QT_MOC_LITERAL(7, 82, 16), // "showPeaksChanged"
QT_MOC_LITERAL(8, 99, 6) // "_state"

    },
    "HistogramWidget\0binClicked\0\0updateUI\0"
    "displayTypeChanged\0_index\0displayModeChanged\0"
    "showPeaksChanged\0_state"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HistogramWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   40,    2, 0x0a /* Public */,
       4,    1,   41,    2, 0x0a /* Public */,
       6,    1,   44,    2, 0x0a /* Public */,
       7,    1,   47,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    8,

       0        // eod
};

void HistogramWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HistogramWidget *_t = static_cast<HistogramWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->binClicked(); break;
        case 1: _t->updateUI(); break;
        case 2: _t->displayTypeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->displayModeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->showPeaksChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (HistogramWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HistogramWidget::binClicked)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject HistogramWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_HistogramWidget.data,
      qt_meta_data_HistogramWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *HistogramWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HistogramWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_HistogramWidget.stringdata0))
        return static_cast<void*>(const_cast< HistogramWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int HistogramWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void HistogramWidget::binClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
