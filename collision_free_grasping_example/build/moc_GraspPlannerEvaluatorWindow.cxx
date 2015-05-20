/****************************************************************************
** Meta object code from reading C++ file 'GraspPlannerEvaluatorWindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../GraspPlannerEvaluatorWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GraspPlannerEvaluatorWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GraspPlannerEvaluatorWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      29,   28,   28,   28, 0x0a,
      42,   36,   28,   28, 0x0a,
      67,   28,   28,   28, 0x0a,
      85,   28,   28,   28, 0x0a,
      96,   28,   28,   28, 0x0a,
     106,   28,   28,   28, 0x0a,
     117,   28,   28,   28, 0x0a,
     136,   28,   28,   28, 0x0a,
     149,   28,   28,   28, 0x0a,
     161,   28,   28,   28, 0x0a,
     168,   28,   28,   28, 0x0a,
     204,  191,  175,   28, 0x0a,
     251,  244,  175,   28, 0x0a,
     291,   28,   28,   28, 0x0a,
     310,   28,   28,   28, 0x0a,
     329,   28,   28,   28, 0x0a,
     341,   28,   28,   28, 0x0a,
     381,  355,   28,   28, 0x0a,
     437,  420,   28,   28, 0x2a,
     491,  477,  472,   28, 0x0a,
     532,  522,  472,   28, 0x0a,
     568,  563,  472,   28, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GraspPlannerEvaluatorWindow[] = {
    "GraspPlannerEvaluatorWindow\0\0quit()\0"
    "event\0closeEvent(QCloseEvent*)\0"
    "resetSceneryAll()\0closeEEF()\0openEEF()\0"
    "colModel()\0frictionConeVisu()\0"
    "showGrasps()\0buildVisu()\0plan()\0save()\0"
    "Eigen::Matrix3f\0vector,theta\0"
    "rodriguesFormula(Eigen::Vector3f,float)\0"
    "vector\0getSkewSymmetricMatrix(Eigen::Vector3f)\0"
    "perturbatedGrasp()\0perturbateObject()\0"
    "resetPose()\0normalGrasp()\0"
    "approachDir,step,maxLoops\0"
    "moveEEFAway(Eigen::Vector3f,float,int)\0"
    "approachDir,step\0moveEEFAway(Eigen::Vector3f,float)\0"
    "bool\0deltaPosition\0updateEEFPose(Eigen::Vector3f)\0"
    "deltaPose\0updateEEFPose(Eigen::Matrix4f)\0"
    "pose\0setEEFPose(Eigen::Matrix4f)\0"
};

void GraspPlannerEvaluatorWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GraspPlannerEvaluatorWindow *_t = static_cast<GraspPlannerEvaluatorWindow *>(_o);
        switch (_id) {
        case 0: _t->quit(); break;
        case 1: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 2: _t->resetSceneryAll(); break;
        case 3: _t->closeEEF(); break;
        case 4: _t->openEEF(); break;
        case 5: _t->colModel(); break;
        case 6: _t->frictionConeVisu(); break;
        case 7: _t->showGrasps(); break;
        case 8: _t->buildVisu(); break;
        case 9: _t->plan(); break;
        case 10: _t->save(); break;
        case 11: { Eigen::Matrix3f _r = _t->rodriguesFormula((*reinterpret_cast< Eigen::Vector3f(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< Eigen::Matrix3f*>(_a[0]) = _r; }  break;
        case 12: { Eigen::Matrix3f _r = _t->getSkewSymmetricMatrix((*reinterpret_cast< Eigen::Vector3f(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< Eigen::Matrix3f*>(_a[0]) = _r; }  break;
        case 13: _t->perturbatedGrasp(); break;
        case 14: _t->perturbateObject(); break;
        case 15: _t->resetPose(); break;
        case 16: _t->normalGrasp(); break;
        case 17: _t->moveEEFAway((*reinterpret_cast< const Eigen::Vector3f(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 18: _t->moveEEFAway((*reinterpret_cast< const Eigen::Vector3f(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 19: { bool _r = _t->updateEEFPose((*reinterpret_cast< const Eigen::Vector3f(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 20: { bool _r = _t->updateEEFPose((*reinterpret_cast< const Eigen::Matrix4f(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 21: { bool _r = _t->setEEFPose((*reinterpret_cast< const Eigen::Matrix4f(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GraspPlannerEvaluatorWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GraspPlannerEvaluatorWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_GraspPlannerEvaluatorWindow,
      qt_meta_data_GraspPlannerEvaluatorWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GraspPlannerEvaluatorWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GraspPlannerEvaluatorWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GraspPlannerEvaluatorWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GraspPlannerEvaluatorWindow))
        return static_cast<void*>(const_cast< GraspPlannerEvaluatorWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int GraspPlannerEvaluatorWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
