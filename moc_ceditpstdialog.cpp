/****************************************************************************
** Meta object code from reading C++ file 'ceditpstdialog.h'
**
** Created: Tue Feb 26 14:11:16 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ceditpstdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ceditpstdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CEditPsDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   15,   14,   14, 0x0a,
      47,   45,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CEditPsDialog[] = {
    "CEditPsDialog\0\0n,b\0OnButtonsClick(uint,bool)\0"
    "n\0OnTableClickLine(uint)\0"
};

const QMetaObject CEditPsDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CEditPsDialog,
      qt_meta_data_CEditPsDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CEditPsDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CEditPsDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CEditPsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CEditPsDialog))
        return static_cast<void*>(const_cast< CEditPsDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int CEditPsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: OnButtonsClick((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: OnTableClickLine((*reinterpret_cast< uint(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
