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
* @author     Peter Kaiser
* @copyright  2015 Peter Kaiser
*             GNU Lesser General Public License
*
*/
#ifndef _VirtualRobot_TSRConstraint_h_
#define _VirtualRobot_TSRConstraint_h_

#include <VirtualRobot/VirtualRobotImportExport.h>
#include <VirtualRobot/IK/Constraint.h>
#include <VirtualRobot/IK/DifferentialIK.h>

#include <boost/shared_ptr.hpp>

namespace VirtualRobot
{
    class VIRTUAL_ROBOT_IMPORT_EXPORT TSRConstraint : public Constraint, public boost::enable_shared_from_this<TSRConstraint>
    {
        public:
            TSRConstraint(const RobotPtr &robot, const RobotNodeSetPtr &nodeSet, const RobotNodePtr &eef,
                          const Eigen::Matrix4f transformation, const Eigen::Matrix4f &eefOffset, const Eigen::Matrix<float, 6, 2> &bounds);

            Eigen::MatrixXf getJacobianMatrix();
            Eigen::MatrixXf getJacobianMatrix(SceneObjectPtr tcp);
            Eigen::VectorXf getError(float stepSize);
            bool checkTolerances();

            std::string getConstraintType();

            void visualize(SoSeparator *sep);

        protected:
            RobotPtr robot;
            RobotNodeSetPtr nodeSet;
            RobotNodePtr eef;

            Eigen::Matrix4f transformation;
            Eigen::Matrix4f eefOffset;
            Eigen::Matrix<float, 6, 2> bounds;

            DifferentialIKPtr ik;

            float toleranceTranslation;
            float toleranceRotation;
    };

    typedef boost::shared_ptr<TSRConstraint> TSRConstraintPtr;
}

#endif
