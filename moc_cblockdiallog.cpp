/****************************************************************************
** Meta object code from reading C++ file 'cblockdiallog.h'
**
** Created: Tue Feb 26 14:11:19 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "cblockdiallog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cblockdiallog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CBlockDiallog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      41,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      65,   61,   14,   14, 0x0a,
      97,   95,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CBlockDiallog[] = {
    "CBlockDiallog\0\0PressButtonStart(CWheel&)\0"
    "PressButtonCancel()\0n,v\0"
    "OnPressButtonStart(uint,bool)\0n\0"
    "OnClickLineTablet(uint)\0"
};

const QMetaObject CBlockDiallog::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CBlockDiallog,
      qt_meta_data_CBlockDiallog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CBlockDiallog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CBlockDiallog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CBlockDiallog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CBlockDiallog))
        return static_cast<void*>(const_cast< CBlockDiallog*>(this));
    return QWidget::qt_metacast(_clname);
}

int CBlockDiallog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: PressButtonStart((*reinterpret_cast< CWheel(*)>(_a[1]))); break;
        case 1: PressButtonCancel(); break;
        case 2: OnPressButtonStart((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: OnClickLineTablet((*reinterpret_cast< uint(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void CBlockDiallog::PressButtonStart(CWheel & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CBlockDiallog::PressButtonCancel()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
