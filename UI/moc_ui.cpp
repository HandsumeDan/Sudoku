/****************************************************************************
** Meta object code from reading C++ file 'ui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UI_t {
    QByteArrayData data[11];
    char stringdata0[102];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UI_t qt_meta_stringdata_UI = {
    {
QT_MOC_LITERAL(0, 0, 2), // "UI"
QT_MOC_LITERAL(1, 3, 16), // "create_sudokuBox"
QT_MOC_LITERAL(2, 20, 10), // "QGroupBox*"
QT_MOC_LITERAL(3, 31, 0), // ""
QT_MOC_LITERAL(4, 32, 8), // "tabIndex"
QT_MOC_LITERAL(5, 41, 11), // "checkSudoku"
QT_MOC_LITERAL(6, 53, 11), // "defineScore"
QT_MOC_LITERAL(7, 65, 8), // "getScore"
QT_MOC_LITERAL(8, 74, 11), // "updateScore"
QT_MOC_LITERAL(9, 86, 5), // "value"
QT_MOC_LITERAL(10, 92, 9) // "newSudoku"

    },
    "UI\0create_sudokuBox\0QGroupBox*\0\0"
    "tabIndex\0checkSudoku\0defineScore\0"
    "getScore\0updateScore\0value\0newSudoku"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    3, 0x0a /* Public */,
       5,    0,   47,    3, 0x0a /* Public */,
       6,    0,   48,    3, 0x0a /* Public */,
       7,    0,   49,    3, 0x0a /* Public */,
       8,    1,   50,    3, 0x0a /* Public */,
      10,    0,   53,    3, 0x0a /* Public */,

 // slots: parameters
    0x80000000 | 2, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,

       0        // eod
};

void UI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UI *_t = static_cast<UI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { QGroupBox* _r = _t->create_sudokuBox((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QGroupBox**>(_a[0]) = std::move(_r); }  break;
        case 1: _t->checkSudoku(); break;
        case 2: _t->defineScore(); break;
        case 3: { int _r = _t->getScore();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->updateScore((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->newSudoku(); break;
        default: ;
        }
    }
}

const QMetaObject UI::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_UI.data,
      qt_meta_data_UI,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *UI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UI.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int UI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
