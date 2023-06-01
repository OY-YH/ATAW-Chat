/****************************************************************************
** Meta object code from reading C++ file 'tcp_manage.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "tcp_manage.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcp_manage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_clientSock_t {
    uint offsetsAndSizes[32];
    char stringdata0[11];
    char stringdata1[15];
    char stringdata2[1];
    char stringdata3[14];
    char stringdata4[5];
    char stringdata5[8];
    char stringdata6[13];
    char stringdata7[7];
    char stringdata8[11];
    char stringdata9[15];
    char stringdata10[22];
    char stringdata11[20];
    char stringdata12[16];
    char stringdata13[13];
    char stringdata14[14];
    char stringdata15[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_clientSock_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_clientSock_t qt_meta_stringdata_clientSock = {
    {
        QT_MOC_LITERAL(0, 10),  // "clientSock"
        QT_MOC_LITERAL(11, 14),  // "recvFormServre"
        QT_MOC_LITERAL(26, 0),  // ""
        QT_MOC_LITERAL(27, 13),  // "signalMessage"
        QT_MOC_LITERAL(41, 4),  // "type"
        QT_MOC_LITERAL(46, 7),  // "dataVal"
        QT_MOC_LITERAL(54, 12),  // "signalStatus"
        QT_MOC_LITERAL(67, 6),  // "status"
        QT_MOC_LITERAL(74, 10),  // "registerOk"
        QT_MOC_LITERAL(85, 14),  // "ForgetPwdReply"
        QT_MOC_LITERAL(100, 21),  // "signalFindFriendReply"
        QT_MOC_LITERAL(122, 19),  // "signalGetOfflineMsg"
        QT_MOC_LITERAL(142, 15),  // "sltDisconnected"
        QT_MOC_LITERAL(158, 12),  // "sltConnected"
        QT_MOC_LITERAL(171, 13),  // "sltSendOnline"
        QT_MOC_LITERAL(185, 14)   // "sltSendOffline"
    },
    "clientSock",
    "recvFormServre",
    "",
    "signalMessage",
    "type",
    "dataVal",
    "signalStatus",
    "status",
    "registerOk",
    "ForgetPwdReply",
    "signalFindFriendReply",
    "signalGetOfflineMsg",
    "sltDisconnected",
    "sltConnected",
    "sltSendOnline",
    "sltSendOffline"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_clientSock[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   80,    2, 0x06,    1 /* Public */,
       3,    2,   83,    2, 0x06,    3 /* Public */,
       6,    1,   88,    2, 0x06,    6 /* Public */,
       8,    1,   91,    2, 0x06,    8 /* Public */,
       9,    1,   94,    2, 0x06,   10 /* Public */,
      10,    1,   97,    2, 0x06,   12 /* Public */,
      11,    1,  100,    2, 0x06,   14 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      12,    0,  103,    2, 0x08,   16 /* Private */,
      13,    0,  104,    2, 0x08,   17 /* Private */,
      14,    0,  105,    2, 0x08,   18 /* Private */,
      15,    0,  106,    2, 0x08,   19 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::UChar, QMetaType::QJsonValue,    4,    5,
    QMetaType::Void, QMetaType::UChar,    7,
    QMetaType::Void, QMetaType::QJsonValue,    5,
    QMetaType::Void, QMetaType::QJsonValue,    5,
    QMetaType::Void, QMetaType::QJsonValue,    5,
    QMetaType::Void, QMetaType::QJsonValue,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject clientSock::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_clientSock.offsetsAndSizes,
    qt_meta_data_clientSock,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_clientSock_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<clientSock, std::true_type>,
        // method 'recvFormServre'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'signalMessage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const quint8 &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QJsonValue &, std::false_type>,
        // method 'signalStatus'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const quint8, std::false_type>,
        // method 'registerOk'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QJsonValue &, std::false_type>,
        // method 'ForgetPwdReply'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QJsonValue &, std::false_type>,
        // method 'signalFindFriendReply'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QJsonValue &, std::false_type>,
        // method 'signalGetOfflineMsg'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QJsonValue &, std::false_type>,
        // method 'sltDisconnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sltConnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sltSendOnline'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sltSendOffline'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void clientSock::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<clientSock *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->recvFormServre((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->signalMessage((*reinterpret_cast< std::add_pointer_t<quint8>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QJsonValue>>(_a[2]))); break;
        case 2: _t->signalStatus((*reinterpret_cast< std::add_pointer_t<quint8>>(_a[1]))); break;
        case 3: _t->registerOk((*reinterpret_cast< std::add_pointer_t<QJsonValue>>(_a[1]))); break;
        case 4: _t->ForgetPwdReply((*reinterpret_cast< std::add_pointer_t<QJsonValue>>(_a[1]))); break;
        case 5: _t->signalFindFriendReply((*reinterpret_cast< std::add_pointer_t<QJsonValue>>(_a[1]))); break;
        case 6: _t->signalGetOfflineMsg((*reinterpret_cast< std::add_pointer_t<QJsonValue>>(_a[1]))); break;
        case 7: _t->sltDisconnected(); break;
        case 8: _t->sltConnected(); break;
        case 9: _t->sltSendOnline(); break;
        case 10: _t->sltSendOffline(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (clientSock::*)(QString );
            if (_t _q_method = &clientSock::recvFormServre; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (clientSock::*)(const quint8 & , const QJsonValue & );
            if (_t _q_method = &clientSock::signalMessage; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (clientSock::*)(const quint8 );
            if (_t _q_method = &clientSock::signalStatus; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (clientSock::*)(const QJsonValue & );
            if (_t _q_method = &clientSock::registerOk; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (clientSock::*)(const QJsonValue & );
            if (_t _q_method = &clientSock::ForgetPwdReply; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (clientSock::*)(const QJsonValue & );
            if (_t _q_method = &clientSock::signalFindFriendReply; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (clientSock::*)(const QJsonValue & );
            if (_t _q_method = &clientSock::signalGetOfflineMsg; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject *clientSock::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *clientSock::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_clientSock.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int clientSock::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void clientSock::recvFormServre(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void clientSock::signalMessage(const quint8 & _t1, const QJsonValue & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void clientSock::signalStatus(const quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void clientSock::registerOk(const QJsonValue & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void clientSock::ForgetPwdReply(const QJsonValue & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void clientSock::signalFindFriendReply(const QJsonValue & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void clientSock::signalGetOfflineMsg(const QJsonValue & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
namespace {
struct qt_meta_stringdata_clientFileSock_t {
    uint offsetsAndSizes[34];
    char stringdata0[15];
    char stringdata1[15];
    char stringdata2[1];
    char stringdata3[13];
    char stringdata4[15];
    char stringdata5[9];
    char stringdata6[19];
    char stringdata7[17];
    char stringdata8[5];
    char stringdata9[9];
    char stringdata10[9];
    char stringdata11[21];
    char stringdata12[9];
    char stringdata13[6];
    char stringdata14[15];
    char stringdata15[18];
    char stringdata16[24];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_clientFileSock_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_clientFileSock_t qt_meta_stringdata_clientFileSock = {
    {
        QT_MOC_LITERAL(0, 14),  // "clientFileSock"
        QT_MOC_LITERAL(15, 14),  // "sucessRecvfile"
        QT_MOC_LITERAL(30, 0),  // ""
        QT_MOC_LITERAL(31, 12),  // "recvFileName"
        QT_MOC_LITERAL(44, 14),  // "sendFileSucess"
        QT_MOC_LITERAL(59, 8),  // "fileName"
        QT_MOC_LITERAL(68, 18),  // "signalSendFinished"
        QT_MOC_LITERAL(87, 16),  // "signalFileRecvOk"
        QT_MOC_LITERAL(104, 4),  // "type"
        QT_MOC_LITERAL(109, 8),  // "filePath"
        QT_MOC_LITERAL(118, 8),  // "senderID"
        QT_MOC_LITERAL(127, 20),  // "signalUpdateProgress"
        QT_MOC_LITERAL(148, 8),  // "currSize"
        QT_MOC_LITERAL(157, 5),  // "total"
        QT_MOC_LITERAL(163, 14),  // "signalConnectd"
        QT_MOC_LITERAL(178, 17),  // "signalFileArrived"
        QT_MOC_LITERAL(196, 23)   // "sltUpdateClientProgress"
    },
    "clientFileSock",
    "sucessRecvfile",
    "",
    "recvFileName",
    "sendFileSucess",
    "fileName",
    "signalSendFinished",
    "signalFileRecvOk",
    "type",
    "filePath",
    "senderID",
    "signalUpdateProgress",
    "currSize",
    "total",
    "signalConnectd",
    "signalFileArrived",
    "sltUpdateClientProgress"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_clientFileSock[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   62,    2, 0x06,    1 /* Public */,
       4,    1,   65,    2, 0x06,    3 /* Public */,
       6,    2,   68,    2, 0x06,    5 /* Public */,
       7,    3,   73,    2, 0x06,    8 /* Public */,
      11,    2,   80,    2, 0x06,   12 /* Public */,
      14,    0,   85,    2, 0x06,   15 /* Public */,
      15,    1,   86,    2, 0x06,   16 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      16,    1,   89,    2, 0x08,   18 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::UChar, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::UChar, QMetaType::QString, QMetaType::Int,    8,    9,   10,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,   12,   13,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonValue,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::LongLong,    2,

       0        // eod
};

Q_CONSTINIT const QMetaObject clientFileSock::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_clientFileSock.offsetsAndSizes,
    qt_meta_data_clientFileSock,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_clientFileSock_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<clientFileSock, std::true_type>,
        // method 'sucessRecvfile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'sendFileSucess'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'signalSendFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint8, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'signalFileRecvOk'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const quint8 &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'signalUpdateProgress'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qint64, std::false_type>,
        QtPrivate::TypeAndForceComplete<qint64, std::false_type>,
        // method 'signalConnectd'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'signalFileArrived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QJsonValue &, std::false_type>,
        // method 'sltUpdateClientProgress'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qint64, std::false_type>
    >,
    nullptr
} };

void clientFileSock::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<clientFileSock *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->sucessRecvfile((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->sendFileSucess((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->signalSendFinished((*reinterpret_cast< std::add_pointer_t<quint8>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 3: _t->signalFileRecvOk((*reinterpret_cast< std::add_pointer_t<quint8>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 4: _t->signalUpdateProgress((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<qint64>>(_a[2]))); break;
        case 5: _t->signalConnectd(); break;
        case 6: _t->signalFileArrived((*reinterpret_cast< std::add_pointer_t<QJsonValue>>(_a[1]))); break;
        case 7: _t->sltUpdateClientProgress((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (clientFileSock::*)(QString );
            if (_t _q_method = &clientFileSock::sucessRecvfile; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (clientFileSock::*)(QString );
            if (_t _q_method = &clientFileSock::sendFileSucess; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (clientFileSock::*)(quint8 , QString );
            if (_t _q_method = &clientFileSock::signalSendFinished; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (clientFileSock::*)(const quint8 & , const QString & , int );
            if (_t _q_method = &clientFileSock::signalFileRecvOk; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (clientFileSock::*)(qint64 , qint64 );
            if (_t _q_method = &clientFileSock::signalUpdateProgress; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (clientFileSock::*)();
            if (_t _q_method = &clientFileSock::signalConnectd; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (clientFileSock::*)(const QJsonValue & );
            if (_t _q_method = &clientFileSock::signalFileArrived; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject *clientFileSock::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *clientFileSock::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_clientFileSock.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int clientFileSock::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void clientFileSock::sucessRecvfile(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void clientFileSock::sendFileSucess(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void clientFileSock::signalSendFinished(quint8 _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void clientFileSock::signalFileRecvOk(const quint8 & _t1, const QString & _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void clientFileSock::signalUpdateProgress(qint64 _t1, qint64 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void clientFileSock::signalConnectd()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void clientFileSock::signalFileArrived(const QJsonValue & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
