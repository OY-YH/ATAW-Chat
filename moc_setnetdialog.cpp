/****************************************************************************
** Meta object code from reading C++ file 'setnetdialog.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "chat_Client/setnetdialog.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'setnetdialog.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_setnetDialog_t {
    uint offsetsAndSizes[16];
    char stringdata0[13];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[5];
    char stringdata4[7];
    char stringdata5[3];
    char stringdata6[20];
    char stringdata7[24];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_setnetDialog_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_setnetDialog_t qt_meta_stringdata_setnetDialog = {
    {
        QT_MOC_LITERAL(0, 12),  // "setnetDialog"
        QT_MOC_LITERAL(13, 12),  // "sendIpandAdd"
        QT_MOC_LITERAL(26, 0),  // ""
        QT_MOC_LITERAL(27, 4),  // "port"
        QT_MOC_LITERAL(32, 6),  // "string"
        QT_MOC_LITERAL(39, 2),  // "ip"
        QT_MOC_LITERAL(42, 19),  // "on_okButton_clicked"
        QT_MOC_LITERAL(62, 23)   // "on_cancelButton_clicked"
    },
    "setnetDialog",
    "sendIpandAdd",
    "",
    "port",
    "string",
    "ip",
    "on_okButton_clicked",
    "on_cancelButton_clicked"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_setnetDialog[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   32,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    0,   37,    2, 0x08,    4 /* Private */,
       7,    0,   38,    2, 0x08,    5 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::UShort, 0x80000000 | 4,    3,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject setnetDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_setnetDialog.offsetsAndSizes,
    qt_meta_data_setnetDialog,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_setnetDialog_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<setnetDialog, std::true_type>,
        // method 'sendIpandAdd'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<unsigned short, std::false_type>,
        QtPrivate::TypeAndForceComplete<string, std::false_type>,
        // method 'on_okButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_cancelButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void setnetDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<setnetDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->sendIpandAdd((*reinterpret_cast< std::add_pointer_t<ushort>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[2]))); break;
        case 1: _t->on_okButton_clicked(); break;
        case 2: _t->on_cancelButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (setnetDialog::*)(unsigned short , string );
            if (_t _q_method = &setnetDialog::sendIpandAdd; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *setnetDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *setnetDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_setnetDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int setnetDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void setnetDialog::sendIpandAdd(unsigned short _t1, string _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
