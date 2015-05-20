
#include "GraspPlannerEvaluatorWindow.h"
#include "GraspPlanning/Visualization/CoinVisualization/CoinConvexHullVisualization.h"
#include "GraspPlanning/ContactConeGenerator.h"
#include "VirtualRobot/EndEffector/EndEffector.h"
#include "VirtualRobot/Workspace/Reachability.h"
#include "VirtualRobot/ManipulationObject.h"
#include "VirtualRobot/Grasping/Grasp.h"
#include "VirtualRobot/IK/GenericIKSolver.h"
#include "VirtualRobot/Grasping/GraspSet.h"
#include "VirtualRobot/CollisionDetection/CDManager.h"
#include "VirtualRobot/XML/ObjectIO.h"
#include "VirtualRobot/XML/RobotIO.h"
#include "VirtualRobot/Visualization/CoinVisualization/CoinVisualizationFactory.h"
#include "VirtualRobot/Visualization/TriMeshModel.h"
#include <QFileDialog>
#include <Eigen/Geometry>

#include <time.h>
#include <vector>
#include <iostream>
#include <cmath>



#include "Inventor/actions/SoLineHighlightRenderAction.h"
#include <Inventor/nodes/SoShapeHints.h>
#include <Inventor/nodes/SoLightModel.h>
#include <Inventor/sensors/SoTimerSensor.h>
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/nodes/SoMatrixTransform.h>
#include <Inventor/nodes/SoScale.h>

#include <sstream>
using namespace std;
using namespace VirtualRobot;
using namespace GraspStudio;

float TIMER_MS = 30.0f;

GraspPlannerEvaluatorWindow::GraspPlannerEvaluatorWindow(std::string& sceneFile, std::string& robotName, std::string& eefName, std::string& preshape, std::string& objectName, Qt::WFlags flags) 
{
	VR_INFO << " start " << endl;

	// init the random number generator
	srand(time(NULL));
	graspNumber = 0;

	this->sceneFile = sceneFile;
	this->robotName = robotName;
	this->eefName = eefName;
	this->preshape = preshape;
	this->objectName = objectName;
	eefVisu = NULL;

	sceneSep = new SoSeparator;
	sceneSep->ref();
	sceneVisuSep = new SoSeparator;
	sceneSep->addChild(sceneVisuSep);
	frictionConeSep = new SoSeparator;
	robotSep = new SoSeparator;
	objectSep = new SoSeparator;
	graspsSep = new SoSeparator;
	graspsSep->ref();

#if 0
	SoSeparator* s = CoinVisualizationFactory::CreateCoordSystemVisualization();
	sceneSep->addChild(s);
#endif
	sceneSep->addChild(robotSep);
	sceneSep->addChild(objectSep);
	sceneSep->addChild(frictionConeSep);
	sceneSep->addChild(graspsSep);

	setupUI();

	loadScene();

	buildVisu();
	viewer->viewAll();
}


GraspPlannerEvaluatorWindow::~GraspPlannerEvaluatorWindow()
{
	sceneSep->unref();
	graspsSep->unref();

	if (eefVisu)
	{
		eefVisu->unref();
	}
}

void GraspPlannerEvaluatorWindow::setupUI()
{
	UI.setupUi(this);
	viewer = new SoQtExaminerViewer(UI.frameViewer, "", TRUE, SoQtExaminerViewer::BUILD_POPUP);

	// setup
	viewer->setBackgroundColor(SbColor(1.0f, 1.0f, 1.0f));
	viewer->setAccumulationBuffer(true);
#ifdef WIN32
	viewer->setAntialiasing(true, 8);
#endif
	viewer->setGLRenderAction(new SoLineHighlightRenderAction);
	viewer->setTransparencyType(SoGLRenderAction::SORTED_OBJECT_BLEND);
	viewer->setFeedbackVisibility(true);
	viewer->setSceneGraph(sceneSep);
	viewer->viewAll();

	connect(UI.pushButtonReset, SIGNAL(clicked()), this, SLOT(resetSceneryAll()));
	connect(UI.pushButtonPlan, SIGNAL(clicked()), this, SLOT(plan()));
	connect(UI.pushButtonSave, SIGNAL(clicked()), this, SLOT(save()));
	connect(UI.pushButtonOpen, SIGNAL(clicked()), this, SLOT(openEEF()));
	connect(UI.pushButtonClose, SIGNAL(clicked()), this, SLOT(closeEEF()));
	connect(UI.pushButtonNormalGrasp, SIGNAL(clicked()), this, SLOT(normalGrasp()));
	connect(UI.pushButtonPerturbedGrasp, SIGNAL(clicked()), this, SLOT(perturbatedGrasp()));
	connect(UI.pushButtonResetPose, SIGNAL(clicked()), this, SLOT(resetPose()));

	connect(UI.checkBoxColModel, SIGNAL(clicked()), this, SLOT(colModel()));
	connect(UI.checkBoxCones, SIGNAL(clicked()), this, SLOT(frictionConeVisu()));
	connect(UI.checkBoxGrasps, SIGNAL(clicked()), this, SLOT(showGrasps()));
}


void GraspPlannerEvaluatorWindow::resetSceneryAll()
{
	grasps->removeAllGrasps();
	graspsSep->removeAllChildren();
}


void GraspPlannerEvaluatorWindow::closeEvent(QCloseEvent* event)
{
	quit();
	QMainWindow::closeEvent(event);
}


void GraspPlannerEvaluatorWindow::buildVisu()
{
	sceneVisuSep->removeAllChildren();
	SceneObject::VisualizationType visuType = (UI.checkBoxColModel->isChecked()) ? SceneObject::Collision : SceneObject::Full;

	visualization = scene->getVisualization<CoinVisualization>(visuType);
	SoNode* visualisationNode = visualization->getCoinVisualization();

	if (visualisationNode)
	{
		sceneVisuSep->addChild(visualisationNode);
	}

	robotSep->removeAllChildren();
	SceneObject::VisualizationType colModel = (UI.checkBoxColModel->isChecked()) ? SceneObject::Collision : SceneObject::Full;

	if (eefCloned)
	{
		visualizationRobot = eefCloned->getVisualization<CoinVisualization>(colModel);
		SoNode* visualisationNode = visualizationRobot->getCoinVisualization();

		if (visualisationNode)
		{
			robotSep->addChild(visualisationNode);
			visualizationRobot->highlight(UI.checkBoxHighlight->isChecked());
		}
	}
	objectSep->removeAllChildren();

	if (object)
	{
		SceneObject::VisualizationType colModel2 = (UI.checkBoxColModel->isChecked()) ? SceneObject::CollisionData : SceneObject::Full;
		SoNode* visualisationNode = CoinVisualizationFactory::getCoinVisualization(object, colModel2);

		if (visualisationNode)
		{
			objectSep->addChild(visualisationNode);
		}

	}

	frictionConeSep->removeAllChildren();
	bool fc = (UI.checkBoxCones->isChecked());

	if (fc && contacts.size() > 0 && qualityMeasure)
	{
		ContactConeGeneratorPtr cg = qualityMeasure->getConeGenerator();
		float radius = cg->getConeRadius();
		float height = cg->getConeHeight();
		float scaling = 30.0f;
		SoNode* visualisationNode = CoinVisualizationFactory::getCoinVisualization(contacts, height * scaling, radius * scaling, true);

		if (visualisationNode)
		{
			frictionConeSep->addChild(visualisationNode);
		}

		// add approach dir visu
		for (size_t i = 0; i < contacts.size(); i++)
		{
			SoSeparator* s = new SoSeparator;
			Eigen::Matrix4f ma;
			ma.setIdentity();
			ma.block(0, 3, 3, 1) = contacts[i].contactPointFingerGlobal;
			SoMatrixTransform* m = CoinVisualizationFactory::getMatrixTransformScaleMM2M(ma);
			s->addChild(m);
			s->addChild(CoinVisualizationFactory::CreateArrow(contacts[i].approachDirectionGlobal, 10.0f, 1.0f));
			frictionConeSep->addChild(s);
		}
	}

	if (UI.checkBoxGrasps->isChecked() && sceneSep->findChild(graspsSep) < 0)
	{
		sceneSep->addChild(graspsSep);
	}

	if (!UI.checkBoxGrasps->isChecked() && sceneSep->findChild(graspsSep) >= 0)
	{
		sceneSep->removeChild(graspsSep);
	}

	viewer->scheduleRedraw();
}

int GraspPlannerEvaluatorWindow::main()
{
	SoQt::show(this);
	SoQt::mainLoop();
	return 0;
}


void GraspPlannerEvaluatorWindow::quit()
{
	std::cout << "GraspPlannerEvaluatorWindow: Closing" << std::endl;
	this->close();
	SoQt::exitMainLoop();
}

void GraspPlannerEvaluatorWindow::loadScene()
{
	sceneVisuSep->removeAllChildren();
	cout << "Loading Scene from " << sceneFile << endl;

	scene.reset();

	try
	{
		scene = SceneIO::loadScene(sceneFile);

		robot = scene->getRobot(robotName);
		if (!robot) {
			VR_ERROR << " no robot named as: " << robotName << endl;
			return;
		}
		else {
			eefInitialPose = robot->getGlobalPose();
			scene->deRegisterRobot(robotName);
		}

		eef = robot->getEndEffector(eefName);

		if (!preshape.empty())
		{
			eef->setPreshape(preshape);
		}

		eefVisu = CoinVisualizationFactory::CreateEndEffectorVisualization(eef);
		eefVisu->ref();

		object = scene->getManipulationObject(objectName);
		if (!object)
		{
			object = Obstacle::createBox(50.0f, 50.0f, 10.0f);
		}
		else {
			scene->deRegisterManipulationObject(objectName);
		}

		qualityMeasure.reset(new GraspStudio::GraspQualityMeasureWrenchSpace(object));
		//qualityMeasure->setVerbose(true);
		qualityMeasure->calculateObjectProperties();
		approach.reset(new GraspStudio::ApproachMovementSurfaceNormal(object, eef));
		eefCloned = approach->getEEFRobotClone();
		eefCloned->setGlobalPose(eefInitialPose);

		if (robot && eef)
		{
			std::string name = "Grasp Planner - ";
			name += eef->getName();
			grasps.reset(new GraspSet(name, robot->getType(), eefName));
		}
		planner.reset(new GraspStudio::GenericGraspPlanner(grasps, qualityMeasure, approach));
		planner->setVerbose(true);

		obstacles = scene->getObstacles();
		obstacleSet = SceneObjectSetPtr(new VirtualRobot::SceneObjectSet());
		for (unsigned i=0; i<obstacles.size(); i++) {
			obstacleSet->addSceneObject(obstacles[i]);
		}
	}
	catch (VirtualRobotException& e)
	{
		cout << "Could not find valid scene in file " << sceneFile << endl;
	}

	if (!scene)
	{
		cout << " ERROR while creating scene" << endl;
		return;
	}
}

void GraspPlannerEvaluatorWindow::plan()
{
	openEEF();
	resetPose();

	float timeout = UI.spinBoxTimeOut->value() * 1000.0f;
	bool forceClosure = UI.checkBoxFoceClosure->isChecked();
	float quality = (float)UI.doubleSpinBoxQuality->value();
	int nrGrasps = UI.spinBoxGraspNumber->value();
	planner.reset(new GraspStudio::GenericGraspPlanner(grasps, qualityMeasure, approach, quality, forceClosure));
	VR_INFO << "EEF robot type:" << approach->getEEF()->getRobotType() << endl;
	/*if (!(approach->getEEF()->getRobot()->getCollisionModel()))
	  VR_INFO << "Null collision model" << endl;*/

	VR_ASSERT(obstacleSet);

	int nr = planner->plan(nrGrasps, timeout, obstacleSet);
	VR_INFO << " Grasp planned:" << nr << endl;
	std::stringstream ss;
	ss << grasps->getSize();
	UI.labelGraspNum->setText(QString(ss.str().c_str()));

	int start = (int)grasps->getSize() - nrGrasps - 1;

	if (start < 0)
	{
		start = 0;
	}

	grasps->setPreshape(preshape);

	for (int i = start; i < (int)grasps->getSize() - 1; i++)
	{
		std::cout << "Adding grasp..." << std::endl;
		Eigen::Matrix4f m = grasps->getGrasp(i)->getTcpPoseGlobal(object->getGlobalPose());
		SoSeparator* sep1 = new SoSeparator();
		SoMatrixTransform* mt = CoinVisualizationFactory::getMatrixTransformScaleMM2M(m);
		sep1->addChild(mt);
		sep1->addChild(eefVisu);
		graspsSep->addChild(sep1);
	}

	// set to last valid grasp
	graspNumber = grasps->getSize();
	if (graspNumber > 0 && eefCloned && eefCloned->getEndEffector(eefName))
	{
		std::cout << "Setting grasp..." << std::endl;
		Eigen::Matrix4f mGrasp = grasps->getGrasp(graspNumber - 1)->getTcpPoseGlobal(object->getGlobalPose());
		eefCloned->setGlobalPoseForRobotNode(eefCloned->getEndEffector(eefName)->getTcp(), mGrasp);
	}

	if (nrGrasps > 0 && graspNumber > 0)
	{
		std::cout << "Open/close fingers" << std::endl;
		openEEF();
		closeEEF();
	}
	else {
		resetPose();
	}
}

void GraspPlannerEvaluatorWindow::normalGrasp() {
	resetPose();
	openEEF();

	graspNumber = UI.spinBoxGraspNum->value();
	if (graspNumber <= 0 || grasps->getSize() < graspNumber) {
		graspNumber = grasps->getSize();
			UI.spinBoxGraspNum->setValue(graspNumber);
		std::cout << "Invalid grasp number selection! Settting to last planned grasp." << std::endl;
	}

	if (graspNumber > 0 && eefCloned && eefCloned->getEndEffector(eefName))
	{
		Eigen::Matrix4f mGrasp = grasps->getGrasp(graspNumber - 1)->getTcpPoseGlobal(object->getGlobalPose());
		eefCloned->setGlobalPoseForRobotNode(eefCloned->getEndEffector(eefName)->getTcp(), mGrasp);

		closeEEF();
	}
}

void GraspPlannerEvaluatorWindow::closeEEF()
{
	contacts.clear();

	if (eefCloned && eefCloned->getEndEffector(eefName))
	{
		contacts = eefCloned->getEndEffector(eefName)->closeActors(object);
		qualityMeasure->setContactPoints(contacts);
		float qual = qualityMeasure->getGraspQuality();
		bool isFC = qualityMeasure->isGraspForceClosure();
		std::stringstream ss;
		ss << std::setprecision(3);
		ss << "Grasp Nr " << graspNumber << "\nQuality (wrench space): " << qual << "\nForce closure: ";

		if (isFC)
		{
			ss << "yes";
		}
		else
		{
			ss << "no";
		}

		UI.labelInfo->setText(QString(ss.str().c_str()));
	}

	buildVisu();
}

void GraspPlannerEvaluatorWindow::openEEF()
{
	contacts.clear();

	if (eefCloned && eefCloned->getEndEffector(eefName))
	{
		if (!preshape.empty())
			eefCloned->getEndEffector(eefName)->setPreshape(preshape);
		else
			eefCloned->getEndEffector(eefName)->openActors();
	}

	buildVisu();
}
Eigen::Matrix3f GraspPlannerEvaluatorWindow::rodriguesFormula(Eigen::Vector3f vector, float theta) {
	//Rotation vector must be of unit length
	//Angle theta must be in rad
	Eigen::Matrix3f mat;
	mat.setIdentity();

	Eigen::Matrix3f skewSym = getSkewSymmetricMatrix(vector);

	mat = mat + skewSym*sin(theta) + skewSym*skewSym*(1 - cos(theta));

	return mat;
}

Eigen::Matrix3f GraspPlannerEvaluatorWindow::getSkewSymmetricMatrix(Eigen::Vector3f vector) {
	Eigen::Matrix3f mat;
	mat(0,0) = 0;
	mat(1,1) = 0;
	mat(2,2) = 0;

	mat(0,1) = -vector(2);
	mat(1,0) = vector(2);

	mat(0,2) = vector(1);
	mat(2,0) = -vector(1);

	mat(1,2) = -vector(0);
	mat(2,1) = vector(0);

	return mat;
}
void GraspPlannerEvaluatorWindow::perturbateObject()
{
	Eigen::Vector3f rotPertub;
	rotPertub.setRandom(3).normalize();
	Eigen::Vector3f translPertub;
	translPertub.setRandom(3).normalize();

	Eigen::Matrix4f deltaPose;
	deltaPose.setIdentity();
	deltaPose.block(0,0,3,3) = rodriguesFormula(rotPertub, UI.doubleSpinBoxPertAngle->value());
	deltaPose.block(0,3,3,1) = translPertub*UI.doubleSpinBoxPertDistance->value();

	std::cout << "DeltaPose:\n" << deltaPose << std::endl;
	std::cout << "Pose:\n" << object->getGlobalPose() << std::endl;
	std::cout << "FinalPose:\n" << (deltaPose*object->getGlobalPose()) << std::endl;
	object->setGlobalPose(deltaPose*object->getGlobalPose());

}
void GraspPlannerEvaluatorWindow::perturbatedGrasp()
{
	openEEF();
	resetPose();

	graspNumber = UI.spinBoxGraspNum->value();
	if (graspNumber <= 0 || grasps->getSize() < graspNumber) {
		graspNumber = grasps->getSize();
		UI.spinBoxGraspNum->setValue(graspNumber);
		std::cout << "Invalid grasp number selection! Settting to last planned grasp." << std::endl;
	}

	// set to last valid grasp
	if (graspNumber > 0 && eefCloned && eefCloned->getEndEffector(eefName))
	{
		Eigen::Matrix4f mGrasp = grasps->getGrasp(graspNumber - 1)->getTcpPoseGlobal(object->getGlobalPose());
		eefCloned->setGlobalPoseForRobotNode(eefCloned->getEndEffector(eefName)->getTcp(), mGrasp);
		perturbateObject();

		//Grasp Center Point Robot Node
		VirtualRobot::RobotNodePtr graspNode = eefCloned->getEndEffector(eefName)->getGCP();
		//Grasp Pose
		Eigen::Matrix4f pose = graspNode->getGlobalPose();
		//Approach Direction (-z vector)
		Eigen::Vector3f approachDir = -pose.block(0,0,3,1);

		//Move eff away	
		moveEEFAway(approachDir, 3.0f);

		closeEEF();
	}
}

void GraspPlannerEvaluatorWindow::resetPose()
{
	Eigen::Matrix4f pose;
	pose.setIdentity();
	object->setGlobalPose(pose);

	eefCloned->setGlobalPose(eefInitialPose);
}

void GraspPlannerEvaluatorWindow::moveEEFAway(const Eigen::Vector3f& approachDir, float step, int maxLoops)
{
	VirtualRobot::SceneObjectSetPtr sos = eefCloned->getEndEffector(eefName)->createSceneObjectSet();

	if (!sos)
	{
		return;
	}

	int loop = 0;
	Eigen::Vector3f delta = approachDir * step;

	while (loop < maxLoops && eefCloned->getEndEffector(eefName)->getCollisionChecker()->checkCollision(object->getCollisionModel(), sos))
	{
		updateEEFPose(delta);
		loop++;
	}
}
bool GraspPlannerEvaluatorWindow::updateEEFPose(const Eigen::Vector3f& deltaPosition)
{
	Eigen::Matrix4f deltaPose;
	deltaPose.setIdentity();
	deltaPose.block(0, 3, 3, 1) = deltaPosition;
	return updateEEFPose(deltaPose);
}

bool GraspPlannerEvaluatorWindow::updateEEFPose(const Eigen::Matrix4f& deltaPose)
{
	Eigen::Matrix4f pose = eefCloned->getEndEffector(eefName)->getGCP()->getGlobalPose();
	pose = deltaPose * pose;
	return setEEFPose(pose);
}

bool GraspPlannerEvaluatorWindow::setEEFPose(const Eigen::Matrix4f& pose)
{
	eefCloned->setGlobalPoseForRobotNode(eefCloned->getEndEffector(eefName)->getGCP(), pose);
	return true;
}


void GraspPlannerEvaluatorWindow::frictionConeVisu()
{
	buildVisu();
}

void GraspPlannerEvaluatorWindow::colModel()
{
	buildVisu();
}

void GraspPlannerEvaluatorWindow::showGrasps()
{
	buildVisu();
}

void GraspPlannerEvaluatorWindow::save()
{
	if (!object)
	{
		return;
	}

	ManipulationObjectPtr objectM(new ManipulationObject(object->getName(), object->getVisualization()->clone(), object->getCollisionModel()->clone()));
	objectM->addGraspSet(grasps);
	QString fi = QFileDialog::getSaveFileName(this, tr("Save ManipulationObject"), QString(), tr("XML Files (*.xml)"));
	objectName = std::string(fi.toAscii());
	bool ok = false;

	try
	{
		ok = ObjectIO::saveManipulationObject(objectM, objectName);
	}
	catch (VirtualRobotException& e)
	{
		cout << " ERROR while saving object" << endl;
		cout << e.what();
		return;
	}

	if (!ok)
	{
		cout << " ERROR while saving object" << endl;
		return;
	}
}
