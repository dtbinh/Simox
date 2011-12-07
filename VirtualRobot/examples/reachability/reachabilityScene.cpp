#include <VirtualRobot/Robot.h>
#include <VirtualRobot/VirtualRobotException.h>
#include <VirtualRobot/Nodes/RobotNode.h>
#include <VirtualRobot/XML/RobotIO.h>
#include <VirtualRobot/Visualization/VisualizationFactory.h>
#include <VirtualRobot/Visualization/CoinVisualization/CoinVisualization.h>
#include <VirtualRobot/RuntimeEnvironment.h>

#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/Qt/SoQt.h>
#include <boost/shared_ptr.hpp>
#include <string>
#include <iostream>
#include <Eigen/Core>
#include <Eigen/Geometry>

#include "reachabilityWindow.h"

//#define AXIS_X

using std::cout;
using std::endl;
using namespace VirtualRobot;
int main(int argc, char *argv[])
{
	SoDB::init();
	SoQt::init(argc,argv,"showRobot");
	cout << " --- START --- " << endl;
	std::string filenameRob(VR_BASE_DIR "/data/robots/ArmarIII/ArmarIII.xml");
#ifdef AXIS_X
	Eigen::Vector3f axisTCP(1.0f,0,0);
#else
	Eigen::Vector3f axisTCP(0,0,1.0f);
#endif
	std::string filenameReach;

	VirtualRobot::RuntimeEnvironment::considerKey("robot");
	VirtualRobot::RuntimeEnvironment::considerKey("reachability");
	VirtualRobot::RuntimeEnvironment::considerKey("visualizationTCPAxis");
	VirtualRobot::RuntimeEnvironment::processCommandLine(argc,argv);
	VirtualRobot::RuntimeEnvironment::print();

	cout << " --- START --- " << endl;

	if (VirtualRobot::RuntimeEnvironment::hasValue("robot"))
	{
		std::string robFile = VirtualRobot::RuntimeEnvironment::getValue("robot");
		if (VirtualRobot::RuntimeEnvironment::getDataFileAbsolute(robFile))
		{
			filenameRob = robFile;
		}
	}
	if (VirtualRobot::RuntimeEnvironment::hasValue("reachability"))
	{
		std::string reachFile = VirtualRobot::RuntimeEnvironment::getValue("reachability");
		if (VirtualRobot::RuntimeEnvironment::getDataFileAbsolute(reachFile))
		{
			filenameReach = reachFile;
		}
	}
	if (VirtualRobot::RuntimeEnvironment::hasValue("visualizationTCPAxis"))
	{
		std::string axisStr = VirtualRobot::RuntimeEnvironment::getValue("visualizationTCPAxis");
		if (!VirtualRobot::RuntimeEnvironment::toVector3f(axisStr,axisTCP))
		{
			cout << "Wrong axis definition:" << axisStr << endl;
		}
	}
	
	cout << "Using robot at " << filenameRob << endl;
	cout << "Using reachability file from " << filenameReach << endl;


	reachabilityWindow rw(filenameRob,filenameReach,axisTCP);

	rw.main();

	return 0;

}
