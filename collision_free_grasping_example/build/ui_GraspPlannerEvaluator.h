/********************************************************************************
** Form generated from reading UI file 'GraspPlannerEvaluator.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRASPPLANNEREVALUATOR_H
#define UI_GRASPPLANNEREVALUATOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GraspPlannerEvaluator
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QFrame *frameViewer;
    QGroupBox *groupBox_1;
    QPushButton *pushButtonReset;
    QLabel *label_10;
    QCheckBox *checkBoxColModel;
    QCheckBox *checkBoxCones;
    QCheckBox *checkBoxGrasps;
    QPushButton *pushButtonPlan;
    QGroupBox *groupBox_2;
    QCheckBox *checkBoxFoceClosure;
    QSpinBox *spinBoxGraspNumber;
    QLabel *label_11;
    QLabel *label_12;
    QSpinBox *spinBoxTimeOut;
    QLabel *label_13;
    QDoubleSpinBox *doubleSpinBoxQuality;
    QPushButton *pushButtonSave;
    QPushButton *pushButtonClose;
    QPushButton *pushButtonOpen;
    QLabel *labelInfo;
    QCheckBox *checkBoxHighlight;
    QPushButton *pushButtonResetPose;
    QPushButton *pushButtonPerturbedGrasp;
    QLabel *labelPertAngle;
    QLabel *label;
    QPushButton *pushButtonNormalGrasp;
    QLabel *labelGraspNum;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QFrame *line;
    QSpinBox *spinBoxGraspNum;
    QDoubleSpinBox *doubleSpinBoxPertAngle;
    QDoubleSpinBox *doubleSpinBoxPertDistance;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *GraspPlannerEvaluator)
    {
        if (GraspPlannerEvaluator->objectName().isEmpty())
            GraspPlannerEvaluator->setObjectName(QString::fromUtf8("GraspPlannerEvaluator"));
        GraspPlannerEvaluator->resize(1209, 882);
        centralwidget = new QWidget(GraspPlannerEvaluator);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        frameViewer = new QFrame(centralwidget);
        frameViewer->setObjectName(QString::fromUtf8("frameViewer"));
        frameViewer->setFrameShape(QFrame::StyledPanel);
        frameViewer->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(frameViewer, 0, 0, 1, 1);

        groupBox_1 = new QGroupBox(centralwidget);
        groupBox_1->setObjectName(QString::fromUtf8("groupBox_1"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_1->sizePolicy().hasHeightForWidth());
        groupBox_1->setSizePolicy(sizePolicy);
        groupBox_1->setMaximumSize(QSize(250, 16777215));
        pushButtonReset = new QPushButton(groupBox_1);
        pushButtonReset->setObjectName(QString::fromUtf8("pushButtonReset"));
        pushButtonReset->setGeometry(QRect(50, 20, 171, 28));
        label_10 = new QLabel(groupBox_1);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 630, 81, 16));
        checkBoxColModel = new QCheckBox(groupBox_1);
        checkBoxColModel->setObjectName(QString::fromUtf8("checkBoxColModel"));
        checkBoxColModel->setGeometry(QRect(20, 660, 141, 17));
        checkBoxCones = new QCheckBox(groupBox_1);
        checkBoxCones->setObjectName(QString::fromUtf8("checkBoxCones"));
        checkBoxCones->setGeometry(QRect(20, 680, 141, 17));
        checkBoxGrasps = new QCheckBox(groupBox_1);
        checkBoxGrasps->setObjectName(QString::fromUtf8("checkBoxGrasps"));
        checkBoxGrasps->setGeometry(QRect(20, 700, 141, 17));
        pushButtonPlan = new QPushButton(groupBox_1);
        pushButtonPlan->setObjectName(QString::fromUtf8("pushButtonPlan"));
        pushButtonPlan->setGeometry(QRect(60, 270, 141, 31));
        groupBox_2 = new QGroupBox(groupBox_1);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(40, 70, 181, 201));
        checkBoxFoceClosure = new QCheckBox(groupBox_2);
        checkBoxFoceClosure->setObjectName(QString::fromUtf8("checkBoxFoceClosure"));
        checkBoxFoceClosure->setGeometry(QRect(30, 170, 171, 17));
        spinBoxGraspNumber = new QSpinBox(groupBox_2);
        spinBoxGraspNumber->setObjectName(QString::fromUtf8("spinBoxGraspNumber"));
        spinBoxGraspNumber->setGeometry(QRect(30, 40, 111, 22));
        spinBoxGraspNumber->setMinimum(1);
        spinBoxGraspNumber->setMaximum(10000000);
        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 20, 151, 16));
        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(10, 70, 211, 16));
        spinBoxTimeOut = new QSpinBox(groupBox_2);
        spinBoxTimeOut->setObjectName(QString::fromUtf8("spinBoxTimeOut"));
        spinBoxTimeOut->setGeometry(QRect(30, 90, 111, 22));
        spinBoxTimeOut->setMinimum(0);
        spinBoxTimeOut->setMaximum(10000000);
        spinBoxTimeOut->setValue(30);
        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(10, 120, 171, 16));
        doubleSpinBoxQuality = new QDoubleSpinBox(groupBox_2);
        doubleSpinBoxQuality->setObjectName(QString::fromUtf8("doubleSpinBoxQuality"));
        doubleSpinBoxQuality->setGeometry(QRect(30, 140, 111, 22));
        doubleSpinBoxQuality->setDecimals(3);
        doubleSpinBoxQuality->setMaximum(1);
        doubleSpinBoxQuality->setSingleStep(0.001);
        pushButtonSave = new QPushButton(groupBox_1);
        pushButtonSave->setObjectName(QString::fromUtf8("pushButtonSave"));
        pushButtonSave->setGeometry(QRect(60, 350, 141, 31));
        pushButtonClose = new QPushButton(groupBox_1);
        pushButtonClose->setObjectName(QString::fromUtf8("pushButtonClose"));
        pushButtonClose->setGeometry(QRect(60, 310, 71, 31));
        pushButtonOpen = new QPushButton(groupBox_1);
        pushButtonOpen->setObjectName(QString::fromUtf8("pushButtonOpen"));
        pushButtonOpen->setGeometry(QRect(130, 310, 71, 31));
        labelInfo = new QLabel(groupBox_1);
        labelInfo->setObjectName(QString::fromUtf8("labelInfo"));
        labelInfo->setGeometry(QRect(20, 750, 221, 61));
        labelInfo->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        checkBoxHighlight = new QCheckBox(groupBox_1);
        checkBoxHighlight->setObjectName(QString::fromUtf8("checkBoxHighlight"));
        checkBoxHighlight->setGeometry(QRect(20, 720, 141, 17));
        pushButtonResetPose = new QPushButton(groupBox_1);
        pushButtonResetPose->setObjectName(QString::fromUtf8("pushButtonResetPose"));
        pushButtonResetPose->setGeometry(QRect(130, 510, 121, 31));
        pushButtonPerturbedGrasp = new QPushButton(groupBox_1);
        pushButtonPerturbedGrasp->setObjectName(QString::fromUtf8("pushButtonPerturbedGrasp"));
        pushButtonPerturbedGrasp->setGeometry(QRect(0, 510, 121, 31));
        pushButtonPerturbedGrasp->setCursor(QCursor(Qt::ArrowCursor));
        labelPertAngle = new QLabel(groupBox_1);
        labelPertAngle->setObjectName(QString::fromUtf8("labelPertAngle"));
        labelPertAngle->setGeometry(QRect(10, 550, 101, 17));
        label = new QLabel(groupBox_1);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(130, 550, 111, 17));
        pushButtonNormalGrasp = new QPushButton(groupBox_1);
        pushButtonNormalGrasp->setObjectName(QString::fromUtf8("pushButtonNormalGrasp"));
        pushButtonNormalGrasp->setGeometry(QRect(0, 460, 121, 31));
        labelGraspNum = new QLabel(groupBox_1);
        labelGraspNum->setObjectName(QString::fromUtf8("labelGraspNum"));
        labelGraspNum->setGeometry(QRect(200, 460, 41, 31));
        label_3 = new QLabel(groupBox_1);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 430, 101, 17));
        label_4 = new QLabel(groupBox_1);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(130, 430, 41, 17));
        label_5 = new QLabel(groupBox_1);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(200, 430, 51, 20));
        line = new QFrame(groupBox_1);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(7, 400, 241, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        spinBoxGraspNum = new QSpinBox(groupBox_1);
        spinBoxGraspNum->setObjectName(QString::fromUtf8("spinBoxGraspNum"));
        spinBoxGraspNum->setGeometry(QRect(130, 460, 60, 31));
        doubleSpinBoxPertAngle = new QDoubleSpinBox(groupBox_1);
        doubleSpinBoxPertAngle->setObjectName(QString::fromUtf8("doubleSpinBoxPertAngle"));
        doubleSpinBoxPertAngle->setGeometry(QRect(10, 570, 91, 27));
        doubleSpinBoxPertDistance = new QDoubleSpinBox(groupBox_1);
        doubleSpinBoxPertDistance->setObjectName(QString::fromUtf8("doubleSpinBoxPertDistance"));
        doubleSpinBoxPertDistance->setGeometry(QRect(130, 570, 91, 27));

        gridLayout->addWidget(groupBox_1, 0, 1, 1, 1);

        GraspPlannerEvaluator->setCentralWidget(centralwidget);
        menubar = new QMenuBar(GraspPlannerEvaluator);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1209, 25));
        GraspPlannerEvaluator->setMenuBar(menubar);
        statusbar = new QStatusBar(GraspPlannerEvaluator);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        GraspPlannerEvaluator->setStatusBar(statusbar);

        retranslateUi(GraspPlannerEvaluator);

        QMetaObject::connectSlotsByName(GraspPlannerEvaluator);
    } // setupUi

    void retranslateUi(QMainWindow *GraspPlannerEvaluator)
    {
        GraspPlannerEvaluator->setWindowTitle(QApplication::translate("GraspPlannerEvaluator", "GraspStudio - GraspPlanner", 0, QApplication::UnicodeUTF8));
        groupBox_1->setTitle(QString());
        pushButtonReset->setText(QApplication::translate("GraspPlannerEvaluator", "Reset", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("GraspPlannerEvaluator", "Visualization", 0, QApplication::UnicodeUTF8));
        checkBoxColModel->setText(QApplication::translate("GraspPlannerEvaluator", "Collision Model", 0, QApplication::UnicodeUTF8));
        checkBoxCones->setText(QApplication::translate("GraspPlannerEvaluator", "Friction Cones", 0, QApplication::UnicodeUTF8));
        checkBoxGrasps->setText(QApplication::translate("GraspPlannerEvaluator", "Show grasps", 0, QApplication::UnicodeUTF8));
        pushButtonPlan->setText(QApplication::translate("GraspPlannerEvaluator", "Plan grasp(s)", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("GraspPlannerEvaluator", "Grasp Planning Options", 0, QApplication::UnicodeUTF8));
        checkBoxFoceClosure->setText(QApplication::translate("GraspPlannerEvaluator", "Force closure", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("GraspPlannerEvaluator", "Number of Grasps", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("GraspPlannerEvaluator", "Timeout, seconds (0=endless)", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("GraspPlannerEvaluator", "Min quality", 0, QApplication::UnicodeUTF8));
        pushButtonSave->setText(QApplication::translate("GraspPlannerEvaluator", "Save", 0, QApplication::UnicodeUTF8));
        pushButtonClose->setText(QApplication::translate("GraspPlannerEvaluator", "Close", 0, QApplication::UnicodeUTF8));
        pushButtonOpen->setText(QApplication::translate("GraspPlannerEvaluator", "Open", 0, QApplication::UnicodeUTF8));
        labelInfo->setText(QApplication::translate("GraspPlannerEvaluator", "Grasps: 0", 0, QApplication::UnicodeUTF8));
        checkBoxHighlight->setText(QApplication::translate("GraspPlannerEvaluator", "Highlight", 0, QApplication::UnicodeUTF8));
        pushButtonResetPose->setText(QApplication::translate("GraspPlannerEvaluator", "Reset Poses", 0, QApplication::UnicodeUTF8));
        pushButtonPerturbedGrasp->setText(QApplication::translate("GraspPlannerEvaluator", "Perturbed Grasp", 0, QApplication::UnicodeUTF8));
        labelPertAngle->setText(QApplication::translate("GraspPlannerEvaluator", "Pert. Angle", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("GraspPlannerEvaluator", "Pert. Distance", 0, QApplication::UnicodeUTF8));
        pushButtonNormalGrasp->setText(QApplication::translate("GraspPlannerEvaluator", "Normal Grasp", 0, QApplication::UnicodeUTF8));
        labelGraspNum->setText(QApplication::translate("GraspPlannerEvaluator", "0", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("GraspPlannerEvaluator", "Execute Grasp", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("GraspPlannerEvaluator", "ID", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("GraspPlannerEvaluator", "Out of", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GraspPlannerEvaluator: public Ui_GraspPlannerEvaluator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRASPPLANNEREVALUATOR_H
