/****************************************************************************
** Meta object code from reading C++ file 'coptionswindow.h'
**
** Created: Tue Feb 26 14:11:03 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "coptionswindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'coptionswindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_COptionsWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   16,   15,   15, 0x0a,
      50,   15,   15,   15, 0x0a,
      68,   15,   15,   15, 0x0a,
      87,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_COptionsWindow[] = {
    "COptionsWindow\0\0n,s\0OnButtonsBaseClick(uint,bool)\0"
    "OnReSizeSpisokD()\0OnReSizeSpisokPs()\0"
    "OnReSizeEnabledD()\0"
};

const QMetaObject COptionsWindow::staticMetaObject = {
    { &CBaseWindow::staticMetaObject, qt_meta_stringdata_COptionsWindow,
      qt_meta_data_COptionsWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &COptionsWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *COptionsWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *COptionsWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_COptionsWindow))
        return static_cast<void*>(const_cast< COptionsWindow*>(this));
    return CBaseWindow::qt_metacast(_clname);
}

int COptionsWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CBaseWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: OnButtonsBaseClick((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: OnReSizeSpisokD(); break;
        case 2: OnReSizeSpisokPs(); break;
        case 3: OnReSizeEnabledD(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
