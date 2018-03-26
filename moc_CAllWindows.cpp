/****************************************************************************
** Meta object code from reading C++ file 'CAllWindows.h'
**
** Created: Tue Feb 26 19:38:43 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "CAllWindows.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CAllWindows.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CAllWindows[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   13,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      35,   31,   12,   12, 0x08,
      61,   13,   12,   12, 0x28,
      82,   13,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CAllWindows[] = {
    "CAllWindows\0\0n\0NewWindow(uint)\0n,s\0"
    "OnButtonsClick(uint,bool)\0"
    "OnButtonsClick(uint)\0OnPressButton(uint)\0"
};

const QMetaObject CAllWindows::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CAllWindows,
      qt_meta_data_CAllWindows, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CAllWindows::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CAllWindows::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CAllWindows::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CAllWindows))
        return static_cast<void*>(const_cast< CAllWindows*>(this));
    return QWidget::qt_metacast(_clname);
}

int CAllWindows::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: NewWindow((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 1: OnButtonsClick((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: OnButtonsClick((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 3: OnPressButton((*reinterpret_cast< uint(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void CAllWindows::NewWindow(unsigned  _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
