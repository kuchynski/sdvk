/****************************************************************************
** Meta object code from reading C++ file 'clabelchange.h'
**
** Created: Mon Feb 25 18:58:02 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "clabelchange.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clabelchange.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CLabelChange[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_CLabelChange[] = {
    "CLabelChange\0\0IAmReSize()\0"
};

const QMetaObject CLabelChange::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CLabelChange,
      qt_meta_data_CLabelChange, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CLabelChange::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CLabelChange::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CLabelChange::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CLabelChange))
        return static_cast<void*>(const_cast< CLabelChange*>(this));
    return QWidget::qt_metacast(_clname);
}

int CLabelChange::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: IAmReSize(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void CLabelChange::IAmReSize()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
