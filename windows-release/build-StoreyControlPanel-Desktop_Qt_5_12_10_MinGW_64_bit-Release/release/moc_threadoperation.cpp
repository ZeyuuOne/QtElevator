/****************************************************************************
** Meta object code from reading C++ file 'threadoperation.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.10)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../StoreyControlPanel/threadoperation.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'threadoperation.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.10. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ThreadOperation_t {
    QByteArrayData data[8];
    char stringdata0[61];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ThreadOperation_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ThreadOperation_t qt_meta_stringdata_ThreadOperation = {
    {
QT_MOC_LITERAL(0, 0, 15), // "ThreadOperation"
QT_MOC_LITERAL(1, 16, 10), // "setMyFloor"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 2), // "up"
QT_MOC_LITERAL(4, 31, 4), // "down"
QT_MOC_LITERAL(5, 36, 8), // "upCancel"
QT_MOC_LITERAL(6, 45, 10), // "downCancel"
QT_MOC_LITERAL(7, 56, 4) // "open"

    },
    "ThreadOperation\0setMyFloor\0\0up\0down\0"
    "upCancel\0downCancel\0open"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ThreadOperation[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x0a /* Public */,
       3,    0,   47,    2, 0x0a /* Public */,
       4,    0,   48,    2, 0x0a /* Public */,
       5,    0,   49,    2, 0x0a /* Public */,
       6,    0,   50,    2, 0x0a /* Public */,
       7,    0,   51,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ThreadOperation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ThreadOperation *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setMyFloor((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->up(); break;
        case 2: _t->down(); break;
        case 3: _t->upCancel(); break;
        case 4: _t->downCancel(); break;
        case 5: _t->open(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ThreadOperation::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_ThreadOperation.data,
    qt_meta_data_ThreadOperation,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ThreadOperation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ThreadOperation::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ThreadOperation.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ThreadOperation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
