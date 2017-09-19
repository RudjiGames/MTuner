/****************************************************************************
** Meta object code from reading C++ file 'sourceview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MTuner_pch.h"
#include "../../src/sourceview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sourceview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SourceView_t {
    QByteArrayData data[13];
    char stringdata0[166];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SourceView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SourceView_t qt_meta_stringdata_SourceView = {
    {
QT_MOC_LITERAL(0, 0, 10), // "SourceView"
QT_MOC_LITERAL(1, 11, 25), // "updateLineNumberAreaWidth"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 14), // "_newBlockCount"
QT_MOC_LITERAL(4, 53, 20), // "highlightCurrentLine"
QT_MOC_LITERAL(5, 74, 20), // "updateLineNumberArea"
QT_MOC_LITERAL(6, 95, 8), // "openFile"
QT_MOC_LITERAL(7, 104, 5), // "_file"
QT_MOC_LITERAL(8, 110, 4), // "_row"
QT_MOC_LITERAL(9, 115, 7), // "_column"
QT_MOC_LITERAL(10, 123, 14), // "setTabWidthTo4"
QT_MOC_LITERAL(11, 138, 14), // "setTabWidthTo8"
QT_MOC_LITERAL(12, 153, 12) // "openInEditor"

    },
    "SourceView\0updateLineNumberAreaWidth\0"
    "\0_newBlockCount\0highlightCurrentLine\0"
    "updateLineNumberArea\0openFile\0_file\0"
    "_row\0_column\0setTabWidthTo4\0setTabWidthTo8\0"
    "openInEditor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SourceView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x08 /* Private */,
       4,    0,   52,    2, 0x08 /* Private */,
       5,    2,   53,    2, 0x08 /* Private */,
       6,    3,   58,    2, 0x08 /* Private */,
      10,    0,   65,    2, 0x08 /* Private */,
      11,    0,   66,    2, 0x08 /* Private */,
      12,    0,   67,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QRect, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,    7,    8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SourceView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SourceView *_t = static_cast<SourceView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateLineNumberAreaWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->highlightCurrentLine(); break;
        case 2: _t->updateLineNumberArea((*reinterpret_cast< const QRect(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->openFile((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 4: _t->setTabWidthTo4(); break;
        case 5: _t->setTabWidthTo8(); break;
        case 6: _t->openInEditor(); break;
        default: ;
        }
    }
}

const QMetaObject SourceView::staticMetaObject = {
    { &QPlainTextEdit::staticMetaObject, qt_meta_stringdata_SourceView.data,
      qt_meta_data_SourceView,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SourceView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SourceView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SourceView.stringdata0))
        return static_cast<void*>(const_cast< SourceView*>(this));
    return QPlainTextEdit::qt_metacast(_clname);
}

int SourceView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPlainTextEdit::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
