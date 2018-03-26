/****************************************************************************
** Meta object code from reading C++ file 'cinputmain.h'
**
** Created: Wed Feb 27 15:13:44 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "cinputmain.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cinputmain.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CInputMain[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   12,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      31,   12,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CInputMain[] = {
    "CInputMain\0\0w\0NewWheel(CWheel)\0"
    "OnNewWheel(CWheel)\0"
};

const QMetaObject CInputMain::staticMetaObject = {
    { &CBaseWindow::staticMetaObject, qt_meta_stringdata_CInputMain,
      qt_meta_data_CInputMain, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CInputMain::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CInputMain::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CInputMain::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CInputMain))
        return static_cast<void*>(const_cast< CInputMain*>(this));
    return CBaseWindow::qt_metacast(_clname);
}

int CInputMain::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CBaseWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: NewWheel((*reinterpret_cast< const CWheel(*)>(_a[1]))); break;
        case 1: OnNewWheel((*reinterpret_cast< const CWheel(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void CInputMain::NewWheel(const CWheel & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
