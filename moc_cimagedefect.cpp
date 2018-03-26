/****************************************************************************
** Meta object code from reading C++ file 'cimagedefect.h'
**
** Created: Tue Feb 26 19:38:31 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "cimagedefect.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cimagedefect.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CImageDefect[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   14,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CImageDefect[] = {
    "CImageDefect\0\0n,b\0OnButtonsClick(uint,bool)\0"
};

const QMetaObject CImageDefect::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CImageDefect,
      qt_meta_data_CImageDefect, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CImageDefect::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CImageDefect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CImageDefect::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CImageDefect))
        return static_cast<void*>(const_cast< CImageDefect*>(this));
    return QDialog::qt_metacast(_clname);
}

int CImageDefect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: OnButtonsClick((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
