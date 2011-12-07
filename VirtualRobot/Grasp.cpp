
#include "Grasp.h"
#include "Robot.h"
#include "VirtualRobotException.h"
#include <iomanip>

namespace VirtualRobot 
{


Grasp::Grasp(const std::string &name, const std::string &robotType, const std::string &eef, const Eigen::Matrix4f &poseInTCPCoordSystem, const std::string &creation, float quality)
:name(name),robotType(robotType),eef(eef),poseTcp(poseInTCPCoordSystem),creation(creation),quality(quality)
{
}

Grasp::~Grasp()
{
}

void Grasp::print( bool printDecoration /*= true*/ )
{
	if (printDecoration)
	{
		cout << "**** Grasp ****" << endl;
		cout << " * Robot type: " << robotType << endl;
		cout << " * End Effector: " << eef << endl;
	}
	cout << " * Name: " << name << endl;
	cout << " * Creation Method: " << creation << endl;
	cout << " * Quality: " << quality << endl;
	{ // scope
		std::ostringstream sos;
		sos << std::setiosflags(std::ios::fixed);
		sos << " * Pose in EEF-TCP coordinate system:" << endl << poseTcp << endl;
		cout << sos.str() << endl;
	} // scope
	if (printDecoration)
		cout << endl;
}

std::string Grasp::getRobotType()
{
	return robotType;
}

std::string Grasp::getEefName()
{
	return eef;
}

Eigen::Matrix4f Grasp::getTargetPoseGlobal( RobotPtr robot )
{
	THROW_VR_EXCEPTION_IF(!robot,"Null data");
	THROW_VR_EXCEPTION_IF(robot->getType() != robotType,"Robot types are not compatible: " << robot->getType() << " != " << robotType);
	EndEffectorPtr eefPtr = robot->getEndEffector(eef);
	if (!eefPtr)
	{
		VR_ERROR << "No EndEffector with name " << eef << " stored in robot " << robot->getName() << endl;
		return Eigen::Matrix4f::Identity();
	}
	RobotNodePtr tcpNode = eefPtr->getTcp();
	if (!tcpNode)
	{
		VR_ERROR << "No tcp with name " << eefPtr->getTcpName() << " in EndEffector " << eef << " in robot " << robot->getName() << endl;
		return Eigen::Matrix4f::Identity();
	}
	return tcpNode->toGlobalCoordinateSystem(poseTcp);
}

std::string Grasp::getName()
{
	return name;
}

Eigen::Matrix4f Grasp::getTransformation()
{
	return poseTcp;
}

void Grasp::setName( const std::string &name )
{
	this->name = name;
}

std::string Grasp::getXMLString()
{
	std::stringstream ss;
	std::string t = "\t";
	std::string tt = "\t\t";
	std::string ttt = "\t\t\t";
	std::string tttt = "\t\t\t\t";

	ss << tt << "<Grasp name='" << name << "' quality='" << quality << "' Creation='" << creation << "'>\n";
	ss << ttt<< "<Transform>\n";
	ss << MathTools::getTransformXMLString(poseTcp, tttt);
	ss << ttt << "</Transform>\n";

	ss << tt << "</Grasp>\n";

	return ss.str();
}

void Grasp::setTransformation( const Eigen::Matrix4f &tcp2Object )
{
	poseTcp = tcp2Object;
}

Eigen::Matrix4f Grasp::getTcpPoseGlobal( const Eigen::Matrix4f &objectPose )
{
	Eigen::Matrix4f result = objectPose * poseTcp.inverse();
	return result;
}

Eigen::Matrix4f Grasp::getObjectTargetPoseGlobal( const Eigen::Matrix4f &graspingPose )
{
	Eigen::Matrix4f result = graspingPose * poseTcp;
	return result;
}

VirtualRobot::GraspPtr Grasp::clone()
{
	GraspPtr result(new Grasp(name,robotType,eef,poseTcp,creation,quality));
	return result;
}


} //  namespace


