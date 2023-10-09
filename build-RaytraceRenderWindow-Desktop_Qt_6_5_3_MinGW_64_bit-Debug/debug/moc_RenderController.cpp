/****************************************************************************
** Meta object code from reading C++ file 'RenderController.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../RaytraceRenderWindow/RenderController.h"
#include <QtGui/qtextcursor.h>
#include <QtGui/qscreen.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RenderController.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSRenderControllerENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSRenderControllerENDCLASS = QtMocHelpers::stringData(
    "RenderController",
    "objectRotationChanged",
    "",
    "xTranslateChanged",
    "value",
    "yTranslateChanged",
    "zTranslateChanged",
    "fresnelRenderingCheckChanged",
    "state",
    "phongShadingCheckChanged",
    "interpolationCheckChanged",
    "shadowBoxCheckChanged",
    "reflectionBoxChanged",
    "refractionBoxChanged",
    "monteCarloBoxChanged",
    "orthographicBoxChanged",
    "raytraceCalled",
    "BeginScaledDrag",
    "whichButton",
    "x",
    "y",
    "ContinueScaledDrag",
    "EndScaledDrag"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSRenderControllerENDCLASS_t {
    uint offsetsAndSizes[46];
    char stringdata0[17];
    char stringdata1[22];
    char stringdata2[1];
    char stringdata3[18];
    char stringdata4[6];
    char stringdata5[18];
    char stringdata6[18];
    char stringdata7[29];
    char stringdata8[6];
    char stringdata9[25];
    char stringdata10[26];
    char stringdata11[22];
    char stringdata12[21];
    char stringdata13[21];
    char stringdata14[21];
    char stringdata15[23];
    char stringdata16[15];
    char stringdata17[16];
    char stringdata18[12];
    char stringdata19[2];
    char stringdata20[2];
    char stringdata21[19];
    char stringdata22[14];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSRenderControllerENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSRenderControllerENDCLASS_t qt_meta_stringdata_CLASSRenderControllerENDCLASS = {
    {
        QT_MOC_LITERAL(0, 16),  // "RenderController"
        QT_MOC_LITERAL(17, 21),  // "objectRotationChanged"
        QT_MOC_LITERAL(39, 0),  // ""
        QT_MOC_LITERAL(40, 17),  // "xTranslateChanged"
        QT_MOC_LITERAL(58, 5),  // "value"
        QT_MOC_LITERAL(64, 17),  // "yTranslateChanged"
        QT_MOC_LITERAL(82, 17),  // "zTranslateChanged"
        QT_MOC_LITERAL(100, 28),  // "fresnelRenderingCheckChanged"
        QT_MOC_LITERAL(129, 5),  // "state"
        QT_MOC_LITERAL(135, 24),  // "phongShadingCheckChanged"
        QT_MOC_LITERAL(160, 25),  // "interpolationCheckChanged"
        QT_MOC_LITERAL(186, 21),  // "shadowBoxCheckChanged"
        QT_MOC_LITERAL(208, 20),  // "reflectionBoxChanged"
        QT_MOC_LITERAL(229, 20),  // "refractionBoxChanged"
        QT_MOC_LITERAL(250, 20),  // "monteCarloBoxChanged"
        QT_MOC_LITERAL(271, 22),  // "orthographicBoxChanged"
        QT_MOC_LITERAL(294, 14),  // "raytraceCalled"
        QT_MOC_LITERAL(309, 15),  // "BeginScaledDrag"
        QT_MOC_LITERAL(325, 11),  // "whichButton"
        QT_MOC_LITERAL(337, 1),  // "x"
        QT_MOC_LITERAL(339, 1),  // "y"
        QT_MOC_LITERAL(341, 18),  // "ContinueScaledDrag"
        QT_MOC_LITERAL(360, 13)   // "EndScaledDrag"
    },
    "RenderController",
    "objectRotationChanged",
    "",
    "xTranslateChanged",
    "value",
    "yTranslateChanged",
    "zTranslateChanged",
    "fresnelRenderingCheckChanged",
    "state",
    "phongShadingCheckChanged",
    "interpolationCheckChanged",
    "shadowBoxCheckChanged",
    "reflectionBoxChanged",
    "refractionBoxChanged",
    "monteCarloBoxChanged",
    "orthographicBoxChanged",
    "raytraceCalled",
    "BeginScaledDrag",
    "whichButton",
    "x",
    "y",
    "ContinueScaledDrag",
    "EndScaledDrag"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSRenderControllerENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  110,    2, 0x0a,    1 /* Public */,
       3,    1,  111,    2, 0x0a,    2 /* Public */,
       5,    1,  114,    2, 0x0a,    4 /* Public */,
       6,    1,  117,    2, 0x0a,    6 /* Public */,
       7,    1,  120,    2, 0x0a,    8 /* Public */,
       9,    1,  123,    2, 0x0a,   10 /* Public */,
      10,    1,  126,    2, 0x0a,   12 /* Public */,
      11,    1,  129,    2, 0x0a,   14 /* Public */,
      12,    1,  132,    2, 0x0a,   16 /* Public */,
      13,    1,  135,    2, 0x0a,   18 /* Public */,
      14,    1,  138,    2, 0x0a,   20 /* Public */,
      15,    1,  141,    2, 0x0a,   22 /* Public */,
      16,    0,  144,    2, 0x0a,   24 /* Public */,
      17,    3,  145,    2, 0x0a,   25 /* Public */,
      21,    2,  152,    2, 0x0a,   29 /* Public */,
      22,    2,  157,    2, 0x0a,   32 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Float, QMetaType::Float,   18,   19,   20,
    QMetaType::Void, QMetaType::Float, QMetaType::Float,   19,   20,
    QMetaType::Void, QMetaType::Float, QMetaType::Float,   19,   20,

       0        // eod
};

Q_CONSTINIT const QMetaObject RenderController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSRenderControllerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSRenderControllerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSRenderControllerENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<RenderController, std::true_type>,
        // method 'objectRotationChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'xTranslateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'yTranslateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'zTranslateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'fresnelRenderingCheckChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'phongShadingCheckChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'interpolationCheckChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'shadowBoxCheckChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'reflectionBoxChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'refractionBoxChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'monteCarloBoxChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'orthographicBoxChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'raytraceCalled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'BeginScaledDrag'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<float, std::false_type>,
        QtPrivate::TypeAndForceComplete<float, std::false_type>,
        // method 'ContinueScaledDrag'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<float, std::false_type>,
        QtPrivate::TypeAndForceComplete<float, std::false_type>,
        // method 'EndScaledDrag'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<float, std::false_type>,
        QtPrivate::TypeAndForceComplete<float, std::false_type>
    >,
    nullptr
} };

void RenderController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RenderController *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->objectRotationChanged(); break;
        case 1: _t->xTranslateChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->yTranslateChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->zTranslateChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->fresnelRenderingCheckChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->phongShadingCheckChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->interpolationCheckChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->shadowBoxCheckChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 8: _t->reflectionBoxChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->refractionBoxChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 10: _t->monteCarloBoxChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->orthographicBoxChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 12: _t->raytraceCalled(); break;
        case 13: _t->BeginScaledDrag((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<float>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<float>>(_a[3]))); break;
        case 14: _t->ContinueScaledDrag((*reinterpret_cast< std::add_pointer_t<float>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<float>>(_a[2]))); break;
        case 15: _t->EndScaledDrag((*reinterpret_cast< std::add_pointer_t<float>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<float>>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject *RenderController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RenderController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSRenderControllerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int RenderController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
