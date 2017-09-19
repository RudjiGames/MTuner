/****************************************************************************
** Meta object code from reading C++ file 'projectsmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MTuner_pch.h"
#include "../../src/projectsmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'projectsmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ProjectsManager_t {
    QByteArrayData data[20];
    char stringdata0[255];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ProjectsManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ProjectsManager_t qt_meta_stringdata_ProjectsManager = {
    {
QT_MOC_LITERAL(0, 0, 15), // "ProjectsManager"
QT_MOC_LITERAL(1, 16, 14), // "captureCreated"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 5), // "_path"
QT_MOC_LITERAL(4, 38, 19), // "captureSetProcessID"
QT_MOC_LITERAL(5, 58, 8), // "uint64_t"
QT_MOC_LITERAL(6, 67, 4), // "_pid"
QT_MOC_LITERAL(7, 72, 9), // "buttonAdd"
QT_MOC_LITERAL(8, 82, 12), // "buttonRemove"
QT_MOC_LITERAL(9, 95, 9), // "buttonRun"
QT_MOC_LITERAL(10, 105, 17), // "textParamsChanged"
QT_MOC_LITERAL(11, 123, 23), // "projectSelectionChanged"
QT_MOC_LITERAL(12, 147, 16), // "browseExecutable"
QT_MOC_LITERAL(13, 164, 16), // "browseWorkingDir"
QT_MOC_LITERAL(14, 181, 10), // "dirChanged"
QT_MOC_LITERAL(15, 192, 7), // "restore"
QT_MOC_LITERAL(16, 200, 15), // "processFinished"
QT_MOC_LITERAL(17, 216, 9), // "_exitCode"
QT_MOC_LITERAL(18, 226, 20), // "QProcess::ExitStatus"
QT_MOC_LITERAL(19, 247, 7) // "_status"

    },
    "ProjectsManager\0captureCreated\0\0_path\0"
    "captureSetProcessID\0uint64_t\0_pid\0"
    "buttonAdd\0buttonRemove\0buttonRun\0"
    "textParamsChanged\0projectSelectionChanged\0"
    "browseExecutable\0browseWorkingDir\0"
    "dirChanged\0restore\0processFinished\0"
    "_exitCode\0QProcess::ExitStatus\0_status"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ProjectsManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       4,    1,   77,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   80,    2, 0x0a /* Public */,
       8,    0,   81,    2, 0x0a /* Public */,
       9,    0,   82,    2, 0x0a /* Public */,
      10,    0,   83,    2, 0x0a /* Public */,
      11,    0,   84,    2, 0x0a /* Public */,
      12,    0,   85,    2, 0x0a /* Public */,
      13,    0,   86,    2, 0x0a /* Public */,
      14,    1,   87,    2, 0x0a /* Public */,
      15,    0,   90,    2, 0x0a /* Public */,
      16,    2,   91,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, 0x80000000 | 5,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 18,   17,   19,

       0        // eod
};

void ProjectsManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ProjectsManager *_t = static_cast<ProjectsManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->captureCreated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->captureSetProcessID((*reinterpret_cast< uint64_t(*)>(_a[1]))); break;
        case 2: _t->buttonAdd(); break;
        case 3: _t->buttonRemove(); break;
        case 4: _t->buttonRun(); break;
        case 5: _t->textParamsChanged(); break;
        case 6: _t->projectSelectionChanged(); break;
        case 7: _t->browseExecutable(); break;
        case 8: _t->browseWorkingDir(); break;
        case 9: _t->dirChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->restore(); break;
        case 11: _t->processFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ProjectsManager::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ProjectsManager::captureCreated)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ProjectsManager::*_t)(uint64_t );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ProjectsManager::captureSetProcessID)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject ProjectsManager::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ProjectsManager.data,
      qt_meta_data_ProjectsManager,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ProjectsManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProjectsManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ProjectsManager.stringdata0))
        return static_cast<void*>(const_cast< ProjectsManager*>(this));
    return QDialog::qt_metacast(_clname);
}

int ProjectsManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void ProjectsManager::captureCreated(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ProjectsManager::captureSetProcessID(uint64_t _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
