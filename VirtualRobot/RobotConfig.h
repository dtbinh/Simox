/**
* This file is part of Simox.
*
* Simox is free software; you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as
* published by the Free Software Foundation; either version 2 of
* the License, or (at your option) any later version.
*
* Simox is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
* @package    VirtualRobot
* @author     Nikolaus Vahrenkamp
* @copyright  2011 Nikolaus Vahrenkamp
*             GNU Lesser General Public License
*
*/
#ifndef _VirtualRobot_RobotConfig_h_
#define _VirtualRobot_RobotConfig_h_

#include "VirtualRobotImportExport.h"

#include "Robot.h"

#include <string>
#include <vector>
#include <map>


namespace VirtualRobot
{
class Robot;

class VIRTUAL_ROBOT_IMPORT_EXPORT RobotConfig
{
public:

	struct Configuration
	{
		std::string name;	//!< The name of the robot node
		float value;		//!< The corresponding value
	};

	RobotConfig(RobotPtr robot, const std::string &name);
	RobotConfig(RobotPtr robot, const std::string &name, const std::map< RobotNodePtr, float > &configs);
	RobotConfig(RobotPtr robot, const std::string &name, const std::vector< Configuration > &configs);
	RobotConfig(RobotPtr robot, const std::string &name, const std::vector< std::string > &robotNodes, const std::vector< float > &values);
	RobotConfig(RobotPtr robot, const std::string &name, const std::vector< RobotNodePtr > &robotNodes, const std::vector< float > &values);

	/*!
		Creates a copy of this object with the given robot
		\param newRobot If not given, the current robot is used. otherwise the newRobot is used.
	 */
	RobotConfigPtr clone(RobotPtr newRobot = RobotPtr());

	/*!
		Returns name of this RobotConfig.
	*/
	std::string getName() const;

	void print() const;

	RobotPtr getRobot();

	/*!
		Appends a configuration to this instance
	*/
	void setConfig (const Configuration &c);
	void setConfig (RobotNodePtr node, float value);
	void setConfig (const std::string &node, float value);

	/*!
		Apply the stored configurations to the corresponding robot.
		RobotNodes that are not stored in this RobotConfig are not affected.
	*/
	void setJointValues();

	/*!
		Check if a configuration for a RobotNode with name is stored.
	*/
	bool hasConfig(const std::string & name) const;
	/*!
		Return the corresponding stored value. If no RobotNode with name is stored, 0.0f is returned.
	*/
	float getConfig(const std::string & name) const;

	/*!
		Return vector of all nodes that are covered by this RobotConfig.
	*/
	std::vector< RobotNodePtr > getNodes() const;

	std::map < std::string, float > getRobotNodeJointvalueMap();

	/*!
		Usually setJointValues() is sufficient for applying the joint values. But in some cases one might want to
		apply the joint values to a cloned robot. Therefore this method can be used.
	*/
	bool applyToRobot(RobotPtr r);

	std::string getXMLString(int tabs=0);
protected:


	std::string name;

	std::map< RobotNodePtr, float > configs;
	RobotPtr robot;
};


} // namespace VirtualRobot

#endif // _VirtualRobot_RobotConfig_h_
