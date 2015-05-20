
#ifndef __GraspPlannerEvaluator_WINDOW_H_
#define __GraspPlannerEvaluator_WINDOW_H_

#include <VirtualRobot/VirtualRobot.h>
#include <VirtualRobot/Robot.h>
#include <VirtualRobot/VirtualRobotException.h>
#include <VirtualRobot/Nodes/RobotNode.h>
#include <VirtualRobot/XML/SceneIO.h>
#include <VirtualRobot/Visualization/VisualizationFactory.h>
#include <VirtualRobot/Visualization/CoinVisualization/CoinVisualization.h>
#include <VirtualRobot/Obstacle.h>
#include <VirtualRobot/ManipulationObject.h>
#include <VirtualRobot/Obstacle.h>

#include "GraspPlanning/GraspStudio.h"
#include "GraspPlanning/GraspQuality/GraspQualityMeasureWrenchSpace.h"
#include "GraspPlanning/GraspPlanner/GenericGraspPlanner.h"
#include "GraspPlanning/ApproachMovementSurfaceNormal.h"

#include <string.h>
#include <QtCore/QtGlobal>
#include <QtGui/QtGui>
#include <QtCore/QtCore>

#include <Inventor/sensors/SoTimerSensor.h>
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/Qt/SoQt.h>
#include <Inventor/nodes/SoSeparator.h>


#include <vector>

#include "ui_GraspPlannerEvaluator.h"

class GraspPlannerEvaluatorWindow : public QMainWindow
{
	Q_OBJECT
	public:
		GraspPlannerEvaluatorWindow(std::string& sceneFile, std::string& robotName, std::string& eefName, std::string& preshape, std::string& objectName, Qt::WFlags flags = 0);
		~GraspPlannerEvaluatorWindow();

		/*!< Executes the SoQt mainLoop. You need to call this in order to execute the application. */
		int main();

		public slots:
			/*! Closes the window and exits SoQt runloop. */
			void quit();

		/*!< Overriding the close event, so we know when the window was closed by the user. */
		void closeEvent(QCloseEvent* event);

		void resetSceneryAll();


		void closeEEF();
		void openEEF();
		void colModel();
		void frictionConeVisu();
		void showGrasps();

		void buildVisu();

		void plan();
		void save();

		static Eigen::Matrix3f rodriguesFormula(Eigen::Vector3f vector, float theta);
		static Eigen::Matrix3f getSkewSymmetricMatrix(Eigen::Vector3f vector);

		void perturbatedGrasp();
		void perturbateObject();
		void resetPose();
		void normalGrasp();
		void moveEEFAway(const Eigen::Vector3f& approachDir, float step, int maxLoops = 1000);
		bool updateEEFPose(const Eigen::Vector3f& deltaPosition);
		bool updateEEFPose(const Eigen::Matrix4f& deltaPose);
		bool setEEFPose(const Eigen::Matrix4f& pose);

	protected:

		void loadRobot();
		void loadObject();
		void loadScene();

		void setupUI();

		static void timerCB(void* data, SoSensor* sensor);
		Ui::GraspPlannerEvaluator UI;
		SoQtExaminerViewer* viewer; /*!< Viewer to display the 3D model of the robot and the environment. */

		SoSeparator* sceneSep;
		SoSeparator* sceneVisuSep;
		SoSeparator* robotSep;
		SoSeparator* objectSep;
		SoSeparator* frictionConeSep;
		SoSeparator* graspsSep;

		Eigen::Matrix4f eefInitialPose;
		VirtualRobot::RobotPtr robot;
		VirtualRobot::RobotPtr eefCloned;
		VirtualRobot::ObstaclePtr object;
		std::vector< VirtualRobot::ObstaclePtr > obstacles;
		VirtualRobot::SceneObjectSetPtr obstacleSet;
		VirtualRobot::EndEffectorPtr eef;

		VirtualRobot::ScenePtr scene;
		std::string sceneFile;

		VirtualRobot::GraspSetPtr grasps;
		int graspNumber;


		VirtualRobot::EndEffector::ContactInfoVector contacts;


		std::string robotName;
		std::string objectName;
		std::string eefName;
		std::string preshape;

		SoSeparator* eefVisu;

		GraspStudio::GraspQualityMeasureWrenchSpacePtr qualityMeasure;
		GraspStudio::ApproachMovementSurfaceNormalPtr approach;
		GraspStudio::GenericGraspPlannerPtr planner;

		boost::shared_ptr<VirtualRobot::CoinVisualization> visualization;
		boost::shared_ptr<VirtualRobot::CoinVisualization> visualizationRobot;
		boost::shared_ptr<VirtualRobot::CoinVisualization> visualizationObject;
};

#endif // __GraspPlannerEvaluator_WINDOW_H_
