/****************************************************************************
** Meta object code from reading C++ file 'Scene.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CG_Curs_Fire/Scene.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Scene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Scene_t {
    QByteArrayData data[11];
    char stringdata[129];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Scene_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Scene_t qt_meta_stringdata_Scene = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Scene"
QT_MOC_LITERAL(1, 6, 14), // "throwException"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 10), // "Exception&"
QT_MOC_LITERAL(4, 33, 12), // "throwMessage"
QT_MOC_LITERAL(5, 46, 12), // "updateParams"
QT_MOC_LITERAL(6, 59, 12), // "QVector<int>"
QT_MOC_LITERAL(7, 72, 16), // "setParamReciever"
QT_MOC_LITERAL(8, 89, 12), // "paramChanged"
QT_MOC_LITERAL(9, 102, 11), // "saveAdjusts"
QT_MOC_LITERAL(10, 114, 14) // "restoreAdjusts"

    },
    "Scene\0throwException\0\0Exception&\0"
    "throwMessage\0updateParams\0QVector<int>\0"
    "setParamReciever\0paramChanged\0saveAdjusts\0"
    "restoreAdjusts"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Scene[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    1,   52,    2, 0x06 /* Public */,
       5,    1,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   58,    2, 0x0a /* Public */,
       8,    1,   59,    2, 0x0a /* Public */,
       9,    0,   62,    2, 0x0a /* Public */,
      10,    0,   63,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 6,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Scene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Scene *_t = static_cast<Scene *>(_o);
        switch (_id) {
        case 0: _t->throwException((*reinterpret_cast< Exception(*)>(_a[1]))); break;
        case 1: _t->throwMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->updateParams((*reinterpret_cast< const QVector<int>(*)>(_a[1]))); break;
        case 3: _t->setParamReciever(); break;
        case 4: _t->paramChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->saveAdjusts(); break;
        case 6: _t->restoreAdjusts(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<int> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Scene::*_t)(Exception & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Scene::throwException)) {
                *result = 0;
            }
        }
        {
            typedef void (Scene::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Scene::throwMessage)) {
                *result = 1;
            }
        }
        {
            typedef void (Scene::*_t)(const QVector<int> & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Scene::updateParams)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject Scene::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Scene.data,
      qt_meta_data_Scene,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Scene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Scene::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Scene.stringdata))
        return static_cast<void*>(const_cast< Scene*>(this));
    return QObject::qt_metacast(_clname);
}

int Scene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void Scene::throwException(Exception & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Scene::throwMessage(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Scene::updateParams(const QVector<int> & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
