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
#ifndef _VirtualRobot_MathTools_h_
#define _VirtualRobot_MathTools_h_

#include "VirtualRobotImportExport.h"

#include <algorithm>
#include <string>
#include <list>
#include <sstream>
#include <iostream>
#include <vector>
#include <Eigen/Core>
#include <Eigen/Geometry>

namespace VirtualRobot
{

namespace MathTools
{

	/************************************************************************/
	/* QUATERNIONS                                                          */
	/************************************************************************/

	struct Quaternion
	{
		Quaternion(){x=y=z=0.0f;w=1.0f;}
		float x,y,z,w;
	};

	
	/*!
		Return rotation that converts vector from to vector to.
	*/
	Quaternion VIRTUAL_ROBOT_IMPORT_EXPORT getRotation(const Eigen::Vector3f &from, const Eigen::Vector3f &to);
	
	//! get the corresponding angle of rotation that is defined by the quaternion (radian)
	float VIRTUAL_ROBOT_IMPORT_EXPORT getAngle (const Quaternion &q);

	//! Return the quaternion that defines the difference between the two given rotations
	Quaternion VIRTUAL_ROBOT_IMPORT_EXPORT getDelta(const Quaternion &q1, const Quaternion &q2);

	//! Return the inverse quaternion
	Quaternion VIRTUAL_ROBOT_IMPORT_EXPORT getInverse(const Quaternion &q);

	//! Return the conjugated quaternion
	Quaternion VIRTUAL_ROBOT_IMPORT_EXPORT getConjugated( const Quaternion &q );

	//! Returns q1*q2
	Quaternion VIRTUAL_ROBOT_IMPORT_EXPORT multiplyQuaternions( const Quaternion &q1, const Quaternion &q2 );

	//! returns q1 dot q2
	float VIRTUAL_ROBOT_IMPORT_EXPORT getDot(const Quaternion &q1, const Quaternion &q2 );
	
	//! Computes mean orientation of quaternions
	MathTools::Quaternion VIRTUAL_ROBOT_IMPORT_EXPORT getMean(std::vector<MathTools::Quaternion> quaternions );

	/************************************************************************/
	/* CONVERTIONS                                                          */
	/************************************************************************/

	/*!
		Convert rpy values to a 3x3 rotation matrix and store it to the rotational component of the given homogeneous matrix.
		The translation is set to zero.
	*/
	void VIRTUAL_ROBOT_IMPORT_EXPORT rpy2eigen4f (float r, float p, float y, Eigen::Matrix4f &m);
	void VIRTUAL_ROBOT_IMPORT_EXPORT posrpy2eigen4f (float x[6], Eigen::Matrix4f &m);
	void VIRTUAL_ROBOT_IMPORT_EXPORT posrpy2eigen4f (const Eigen::Vector3f &pos, const Eigen::Vector3f &rpy, Eigen::Matrix4f &m);

	/*!
		Convert homogeneous matrix to translation and rpy rotation.
		\param m The matrix to be converted
		\param x The result is stored in this float array (x,y,z,roll,pitch,yaw)
	*/
	void VIRTUAL_ROBOT_IMPORT_EXPORT eigen4f2rpy(const Eigen::Matrix4f &m, float x[6]);
	void VIRTUAL_ROBOT_IMPORT_EXPORT eigen4f2rpy(const Eigen::Matrix4f &m, Eigen::Vector3f &storeRPY);

	/*!
		Convert quaternion values to a 3x3 rotation matrix and store it to the rotational component of the result.
		The translational part of m is zero
		\return Homogeneous matrix representing the rotation of q.
	*/
	Eigen::Matrix4f VIRTUAL_ROBOT_IMPORT_EXPORT quat2eigen4f (float x, float y, float z, float w);
	Eigen::Matrix4f VIRTUAL_ROBOT_IMPORT_EXPORT quat2eigen4f (const Quaternion q);

	Quaternion VIRTUAL_ROBOT_IMPORT_EXPORT eigen4f2quat (const Eigen::Matrix4f &m);

	Eigen::Vector3f VIRTUAL_ROBOT_IMPORT_EXPORT getTranslation (const Eigen::Matrix4f &m);

	void VIRTUAL_ROBOT_IMPORT_EXPORT eigen4f2axisangle(const Eigen::Matrix4f &m, Eigen::Vector3f &storeAxis, float& storeAngle);
	Eigen::Matrix4f VIRTUAL_ROBOT_IMPORT_EXPORT axisangle2eigen4f(const Eigen::Vector3f &axis, float angle);
	Eigen::Matrix3f VIRTUAL_ROBOT_IMPORT_EXPORT axisangle2eigen3f(const Eigen::Vector3f &axis, float angle);
	Quaternion VIRTUAL_ROBOT_IMPORT_EXPORT axisangle2quat(const Eigen::Vector3f &axis, float angle);



	/************************************************************************/
	/* GEOMETRY                                                             */
	/************************************************************************/
	struct Plane
	{
		Plane(const Eigen::Vector3f &point, const Eigen::Vector3f &normal)
		{
			p = point;
			n = normal;
			n.normalize();
		}

		Plane(const Plane& plane){this->p = plane.p;this->n = plane.n;}

		Eigen::Vector3f	p;	// point
		Eigen::Vector3f n;	// normal (unit length)
	};

	//! Create a floor plane
	Plane VIRTUAL_ROBOT_IMPORT_EXPORT getFloorPlane();

	struct Line
	{
		Line(const Eigen::Vector3f &point, const Eigen::Vector3f &dir)
		{
			p = point;
			d = dir;
			if (d.norm()>1e-9)
				d.normalize();
		}

		Line(const Line& line){this->p = line.p;this->d = line.d;}

		bool isValid() const {return d.norm()>1e-9;}

		Eigen::Vector3f	p;	// point
		Eigen::Vector3f d;	// direction (unit length)
	};
	
	/*! 
		Convenient structs for handling 3D/6D vertices, faces and convex hulls.
	*/
	struct ContactPoint
	{
		Eigen::Vector3f	p;	// point
		Eigen::Vector3f n;	// normal
	};

	struct TriangleFace
	{
		/**
		 * Flips the orientation of the contained vertex and the normal.
		 */
		void flipOrientation(){
			std::swap(id3, id1);
			normal *= -1.0f;
		}
		// id == position in vertex array
		unsigned int id1;
		unsigned int id2;
		unsigned int id3;
		Eigen::Vector3f normal;
	};
	struct TriangleFace6D
	{
		int id[6];// position in vertice vector (x,y,z,nx,ny,nz)
		ContactPoint normal;

		// these values are set by the ConvexHull algorithm (@see GraspStudio)
		float distNormZero;		// distance of facet to origin
		float distNormCenter;	// distance of facet to center of convex hull 
		float distPlaneZero;	// distance of plane defined by facet to origin
		float distPlaneCenter;	// distance of plane defined by facet to center of convex hull 
		float offset;			// offset value of facet, determined by qhull
	};


	//! Get the projected point in 3D
	Eigen::Vector3f VIRTUAL_ROBOT_IMPORT_EXPORT projectPointToPlane(const Eigen::Vector3f &point, const Plane &plane);

	//! Get the intersection line of two planes. If planes are parallel, the resulting line is invalid, i.e. has a zero direction vector!
	Line VIRTUAL_ROBOT_IMPORT_EXPORT intersectPlanes(const Plane &p1, const Plane &p2);

	//! Returns nearest point to p on line l
	Eigen::Vector3f VIRTUAL_ROBOT_IMPORT_EXPORT nearestPointOnLine(const Line &l, const Eigen::Vector3f &p);
	float VIRTUAL_ROBOT_IMPORT_EXPORT distPointLine(const Line &l, const Eigen::Vector3f &p);

	//! Check if three points are collinear
	bool VIRTUAL_ROBOT_IMPORT_EXPORT collinear(const Eigen::Vector3f &p1, const Eigen::Vector3f &p2, const Eigen::Vector3f &p3 );

	/*!
		assuming all points to be in a plane. Returns normal of this plane.
	*/
	Eigen::Vector3f VIRTUAL_ROBOT_IMPORT_EXPORT findNormal( const std::vector<Eigen::Vector3f> &points);

	//! Get the projected point in 2D (local coordinate system of the plane)
	Eigen::Vector2f VIRTUAL_ROBOT_IMPORT_EXPORT projectPointToPlane2D(const Eigen::Vector3f &point, const Plane &plane);

	//! Get the corresponding point in 3D
	Eigen::Vector3f VIRTUAL_ROBOT_IMPORT_EXPORT planePoint3D(const Eigen::Vector2f &pointLocal, const Plane &plane);

	float VIRTUAL_ROBOT_IMPORT_EXPORT getDistancePointPlane( const Eigen::Vector3f &point, const Plane &plane );

	/*!
		This method can be used to multiply a 3d position with a matrix
		result = m * pos
	*/
	Eigen::Vector3f VIRTUAL_ROBOT_IMPORT_EXPORT transformPosition(const Eigen::Vector3f &pos, const Eigen::Matrix4f &m);

	//! Get a random point inside the triangle that is spanned by v1, v2 and v3
	Eigen::Vector3f VIRTUAL_ROBOT_IMPORT_EXPORT randomPointInTriangle(const Eigen::Vector3f &v1, const Eigen::Vector3f &v2, const Eigen::Vector3f &v3);

	/*!
		Returns true, if point is on the side of plane in which the normal vector is pointing.
	*/
	bool VIRTUAL_ROBOT_IMPORT_EXPORT onNormalPointingSide(const Eigen::Vector3f &point, const Plane &p);


	/************************************************************************/
	/* CONVEX HULLS                                                         */
	/* More convex hull methods can be found in the GarspStudio lib         */
	/************************************************************************/

	struct Segment2D
	{
		int id1;
		int id2;
	};

	struct ConvexHull2D
	{
		std::vector<Eigen::Vector2f> vertices;
		std::vector<Segment2D> segments;
	};	
	typedef boost::shared_ptr<ConvexHull2D> ConvexHull2DPtr;

	struct ConvexHull3D
	{
		std::vector<Eigen::Vector3f> vertices;
		std::vector<TriangleFace> faces;
		float volume;
	};
	typedef boost::shared_ptr<ConvexHull3D> ConvexHull3DPtr;

	struct ConvexHull6D
	{
		std::vector<ContactPoint>	vertices;
		std::vector<TriangleFace6D>	faces;
		float volume;
		ContactPoint center;
	};
	typedef boost::shared_ptr<ConvexHull6D> ConvexHull6DPtr;
	

	// Copyright 2001, softSurfer (www.softsurfer.com)
	// This code may be freely used and modified for any purpose
	// providing that this copyright notice is included with it.
	// SoftSurfer makes no warranty for this code, and cannot be held
	// liable for any real or imagined damage resulting from its use.
	// Users of this code must verify correctness for their application.
	// isLeft(): tests if a point is Left|On|Right of an infinite line.
	//    Input:  three points P0, P1, and P2
	//    Return: >0 for P2 left of the line through P0 and P1
	//            =0 for P2 on the line
	//            <0 for P2 right of the line
	//    See: the January 2001 Algorithm on Area of Triangles
	inline float isLeft( Eigen::Vector2f P0, Eigen::Vector2f P1, Eigen::Vector2f P2 )
	{
		return (P1(0) - P0(0))*(P2(1) - P0(1)) - (P2(0) - P0(0))*(P1(1) - P0(1));
	}

	//! Consider first coordinate. If two points share the first coord, the second one is used to decide which is "smaller"
	Eigen::Vector2f getAndRemoveSmallestPoint(std::vector< Eigen::Vector2f > &points);

	ConvexHull2DPtr VIRTUAL_ROBOT_IMPORT_EXPORT createConvexHull2D(std::vector< Eigen::Vector2f > points);
	bool VIRTUAL_ROBOT_IMPORT_EXPORT isInside(const Eigen::Vector2f &p, ConvexHull2DPtr hull);
	
	/*!
 		Sort points according to their first coordinate. If two points share the first coord, the second one is used to decide which is "smaller".
	*/
	std::vector< Eigen::Vector2f > sortPoints(const std::vector< Eigen::Vector2f > &points);



	/************************************************************************/
	/* BASIS HELPERS                                                        */
	/************************************************************************/
	bool VIRTUAL_ROBOT_IMPORT_EXPORT ensureOrthonormalBasis(Eigen::Vector3f &x, Eigen::Vector3f &y, Eigen::Vector3f &z);


	//! perform the Gram-Schmidt method for building an orthonormal basis
	bool VIRTUAL_ROBOT_IMPORT_EXPORT GramSchmidt(std::vector< Eigen::VectorXf > & basis);

	//! Searches a vector that is linearly independent ot the given basis.
	bool VIRTUAL_ROBOT_IMPORT_EXPORT randomLinearlyIndependentVector(const std::vector< Eigen::VectorXf > basis, Eigen::VectorXf &storeResult);

	//! Checks if m contains a col vector equal to v (distance up to 1e-8 are considered as equal)
	bool VIRTUAL_ROBOT_IMPORT_EXPORT containsVector(const Eigen::MatrixXf& m, const Eigen::VectorXf &v);
	

	/*!
		Computes the matrix describing the basis transformation from basis formed by vectors in basisSrc to basisDst.
		So v_{Src} can be transformed to v_{Dst}, given as linear combination of basisDst vectors, by 
		v_{Dst} = T v_{Src} with T is the BasisTransformationMatrix given by this method.
		\param basisSrc The initial basis vectors.
		\param basisDst The final basis vectors.
		\return The transformation matrix T.
	*/
	Eigen::MatrixXf VIRTUAL_ROBOT_IMPORT_EXPORT getBasisTransformation(const std::vector< Eigen::VectorXf > &basisSrc, const std::vector< Eigen::VectorXf > &basisDst);

	/*!
		Computes the matrix describing the basis transformation from basis formed by vectors in basisSrc to basisDst.
		So v_{Src} can be transformed to v_{Dst}, given as linear combination of basisDst vectors, by 
		v_{Dst} = T v_{Src} with T is the BasisTransformationMatrix given by this method.
		\param basisSrc The column vectors are the initial basis vectors 
		\param basisDst The column vectors are the final basis vectors.
		\return The transformation matrix T.
	*/
	Eigen::MatrixXf VIRTUAL_ROBOT_IMPORT_EXPORT getBasisTransformation(const Eigen::MatrixXf &basisSrc, const Eigen::MatrixXf &basisDst);


	/************************************************************************/
	/* HELPERS and IO                                                       */
	/************************************************************************/

	/*!
		Check if all entries of v are valid numbers (i.e. all entries of v are not NaN and not INF)
	*/
	bool VIRTUAL_ROBOT_IMPORT_EXPORT isValid (const Eigen::MatrixXf &v);
	void VIRTUAL_ROBOT_IMPORT_EXPORT print (const ContactPoint &p);
	void VIRTUAL_ROBOT_IMPORT_EXPORT print (const std::vector<ContactPoint> &points);
	void VIRTUAL_ROBOT_IMPORT_EXPORT print( const Eigen::Vector3f &v, bool endline = true );
	std::string VIRTUAL_ROBOT_IMPORT_EXPORT getTransformXMLString(const Eigen::Matrix4f &m, const std::string &tabs);
	void VIRTUAL_ROBOT_IMPORT_EXPORT convertMM2M( const std::vector<ContactPoint> points, std::vector<ContactPoint> &storeResult );


};
} // namespace VirtualRobot

#endif //_VirtualRobot_MathTools_h_
