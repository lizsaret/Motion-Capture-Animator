/****************************************************************************
** Meta object code from reading C++ file 'player.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MotionCaptureAnimator/player.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'player.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Player_t {
    QByteArrayData data[8];
    char stringdata0[74];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Player_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Player_t qt_meta_stringdata_Player = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Player"
QT_MOC_LITERAL(1, 7, 12), // "outputsReady"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 20), // "outputFramesToWindow"
QT_MOC_LITERAL(4, 42, 6), // "image1"
QT_MOC_LITERAL(5, 49, 6), // "image2"
QT_MOC_LITERAL(6, 56, 6), // "image3"
QT_MOC_LITERAL(7, 63, 10) // "endOfVideo"

    },
    "Player\0outputsReady\0\0outputFramesToWindow\0"
    "image1\0image2\0image3\0endOfVideo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Player[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    3,   30,    2, 0x06 /* Public */,
       7,    0,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QImage, QMetaType::QImage, QMetaType::QImage,    4,    5,    6,
    QMetaType::Void,

       0        // eod
};

void Player::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Player *_t = static_cast<Player *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->outputsReady(); break;
        case 1: _t->outputFramesToWindow((*reinterpret_cast< const QImage(*)>(_a[1])),(*reinterpret_cast< const QImage(*)>(_a[2])),(*reinterpret_cast< const QImage(*)>(_a[3]))); break;
        case 2: _t->endOfVideo(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (Player::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Player::outputsReady)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Player::*_t)(const QImage & , const QImage & , const QImage & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Player::outputFramesToWindow)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Player::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Player::endOfVideo)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Player::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_Player.data,
      qt_meta_data_Player,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Player::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Player::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Player.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int Player::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void Player::outputsReady()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Player::outputFramesToWindow(const QImage & _t1, const QImage & _t2, const QImage & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Player::endOfVideo()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
