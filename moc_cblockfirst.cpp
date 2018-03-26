/****************************************************************************
** Meta object code from reading C++ file 'cblockfirst.h'
**
** Created: Wed Feb 27 15:13:31 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "cblockfirst.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cblockfirst.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CBlockFirst[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      36,   27,   12,   12, 0x0a,
      69,   65,   12,   12, 0x0a,
      92,   86,   12,   12, 0x0a,
     130,  126,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CBlockFirst[] = {
    "CBlockFirst\0\0PressButton()\0type,w,l\0"
    "OnBlockState(uint,uint,uint)\0res\0"
    "OnEndReload(int)\0n,tmp\0"
    "on_checked_portChanged(uint,bool)\0n,v\0"
    "OnPressButtonStart(uint,bool)\0"
};

const QMetaObject CBlockFirst::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CBlockFirst,
      qt_meta_data_CBlockFirst, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CBlockFirst::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CBlockFirst::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CBlockFirst::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CBlockFirst))
        return static_cast<void*>(const_cast< CBlockFirst*>(this));
    return QWidget::qt_metacast(_clname);
}

int CBlockFirst::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: PressButton(); break;
        case 1: OnBlockState((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3]))); break;
        case 2: OnEndReload((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: on_checked_portChanged((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 4: OnPressButtonStart((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void CBlockFirst::PressButton()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
