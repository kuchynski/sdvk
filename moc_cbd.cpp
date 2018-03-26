/****************************************************************************
** Meta object code from reading C++ file 'cbd.h'
**
** Created: Tue Feb 26 19:38:27 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "cbd.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cbd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CBd[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    5,    4,    4, 0x0a,
      41,   39,    4,    4, 0x0a,
      71,   39,    4,    4, 0x0a,
     102,   97,    4,    4, 0x0a,
     121,    4,    4,    4, 0x0a,
     139,  137,    4,    4, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CBd[] = {
    "CBd\0\0n,s\0OnButtonsBaseClick(uint,bool)\0"
    ",\0OnButtonsMainClick(uint,bool)\0"
    "OnButtonsClick(uint,bool)\0line\0"
    "OnTableClick(uint)\0OnReSizeTable()\0w\0"
    "OnNewWheel(CWheel)\0"
};

const QMetaObject CBd::staticMetaObject = {
    { &CBaseWindow::staticMetaObject, qt_meta_stringdata_CBd,
      qt_meta_data_CBd, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CBd::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CBd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CBd::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CBd))
        return static_cast<void*>(const_cast< CBd*>(this));
    return CBaseWindow::qt_metacast(_clname);
}

int CBd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CBaseWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: OnButtonsBaseClick((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: OnButtonsMainClick((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: OnButtonsClick((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: OnTableClick((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 4: OnReSizeTable(); break;
        case 5: OnNewWheel((*reinterpret_cast< const CWheel(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
