#include <VirtualRobot/VirtualRobot.h>
#include <VirtualRobot/RuntimeEnvironment.h>

#include <string>
#include <iostream>

using std::cout;
using std::endl;
using namespace VirtualRobot;

#include <Eigen/Core>
#include <Eigen/Geometry>

#include "GraspPlannerEvaluatorWindow.h"


int main(int argc, char* argv[])
{
    SoDB::init();
    SoQt::init(argc, argv, "showRobot");
    cout << " --- START --- " << endl;

    std::string filename("../../data/scenes/scene.xml");
    std::string robotName("SHADOWHAND");
    std::string eefName("SHADOWHAND");
    std::string objectName("ManipulationObject");
    std::string preshapeName("Grasp Preshape");

    VirtualRobot::RuntimeEnvironment::considerKey("scene");
    VirtualRobot::RuntimeEnvironment::considerKey("robot");
    VirtualRobot::RuntimeEnvironment::considerKey("object");
    VirtualRobot::RuntimeEnvironment::considerKey("endeffector");
    VirtualRobot::RuntimeEnvironment::considerKey("preshape");

    VirtualRobot::RuntimeEnvironment::processCommandLine(argc, argv);
    VirtualRobot::RuntimeEnvironment::print();

    filename = VirtualRobot::RuntimeEnvironment::checkValidFileParameter("scene", filename);

    std::string robName = VirtualRobot::RuntimeEnvironment::getValue("robot");

    if (!robName.empty() && VirtualRobot::RuntimeEnvironment::getDataFileAbsolute(robName))
    {
        robotName = robName;
    }

    std::string objName = VirtualRobot::RuntimeEnvironment::getValue("object");

    if (!objName.empty() && VirtualRobot::RuntimeEnvironment::getDataFileAbsolute(objName))
    {
        objectName = objName;
    }

    std::string eefname = VirtualRobot::RuntimeEnvironment::getValue("endeffector");

    if (!eefname.empty())
    {
        eefName = eefname;
    }

    std::string ps = VirtualRobot::RuntimeEnvironment::getValue("preshape");

    if (!ps.empty())
    {
        preshapeName = ps;
    }

    cout << "Robot name: " << robotName << endl;
    cout << "End effector name:" << eefName << ", preshape:" << preshapeName << endl;
    cout << "Object name: " << objectName << endl;
    cout << "Using scene from file:" << filename << endl;

    GraspPlannerEvaluatorWindow rw(filename, robotName, eefName, preshapeName, objectName);


    rw.main();

    return 0;
}
