/****************************************************************************
** Meta object code from reading C++ file 'cblockscan.h'
**
** Created: Wed Feb 27 15:13:34 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "cblockscan.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cblockscan.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CBlockScan[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   12,   11,   11, 0x05,
      33,   31,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      55,   51,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CBlockScan[] = {
    "CBlockScan\0\0w\0NewWheel(CWheel)\0n\0"
    "PressButton(uint)\0n,v\0OnPressButton(uint,bool)\0"
};

const QMetaObject CBlockScan::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CBlockScan,
      qt_meta_data_CBlockScan, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CBlockScan::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CBlockScan::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CBlockScan::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CBlockScan))
        return static_cast<void*>(const_cast< CBlockScan*>(this));
    return QWidget::qt_metacast(_clname);
}

int CBlockScan::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: NewWheel((*reinterpret_cast< const CWheel(*)>(_a[1]))); break;
        case 1: PressButton((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 2: OnPressButton((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void CBlockScan::NewWheel(const CWheel & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CBlockScan::PressButton(unsigned  _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
