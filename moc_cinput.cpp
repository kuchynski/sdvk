/****************************************************************************
** Meta object code from reading C++ file 'cinput.h'
**
** Created: Wed Feb 27 15:13:40 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "cinput.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cinput.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CInput[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,    8,    7,    7, 0x0a,
      46,    7,    7,    7, 0x0a,
      65,   63,    7,    7, 0x0a,
      94,    7,    7,    7, 0x0a,
     119,  117,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CInput[] = {
    "CInput\0\0type,w,l\0OnBlockState(uint,uint,uint)\0"
    "OnPressButton1()\0w\0OnPressButtonStart2(CWheel&)\0"
    "OnPressButtonCancel2()\0n\0OnPressButton3(uint)\0"
};

const QMetaObject CInput::staticMetaObject = {
    { &CAllWindows::staticMetaObject, qt_meta_stringdata_CInput,
      qt_meta_data_CInput, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CInput::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CInput::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CInput::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CInput))
        return static_cast<void*>(const_cast< CInput*>(this));
    return CAllWindows::qt_metacast(_clname);
}

int CInput::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CAllWindows::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: OnBlockState((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3]))); break;
        case 1: OnPressButton1(); break;
        case 2: OnPressButtonStart2((*reinterpret_cast< CWheel(*)>(_a[1]))); break;
        case 3: OnPressButtonCancel2(); break;
        case 4: OnPressButton3((*reinterpret_cast< uint(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
