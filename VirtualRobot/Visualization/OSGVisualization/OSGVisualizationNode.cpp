/**
* @package    VirtualRobot
* @author     Nikolaus Vahrenkamp
* @copyright  2011 Nikolaus Vahrenkamp
*/

#include "OSGVisualizationNode.h"
#include "OSGVisualizationFactory.h"
#include "../TriMeshModel.h"
#include "../../VirtualRobotException.h"

#include <osg/TriangleFunctor>
#include <osg/Geode>
#include <osg/Node>
#include <osg/Group>

namespace VirtualRobot {

/**
 * Store a reference to \p visualizationNode in the member
 * OSGVisualizationNode::visualization.
 */
OSGVisualizationNode::OSGVisualizationNode(osg::Node* visualizationNode) 
{
	visualization = visualizationNode;
	visualization->ref();

	visualizationAtGlobalPose = new osg::Group;
	visualizationAtGlobalPose->ref();
	
	globalPoseTransform = new osg::MatrixTransform;
	visualizationAtGlobalPose->addChild(globalPoseTransform);
	
	attachedVisualizationsSeparator = new osg::Group;
	attachedVisualizationsSeparator->ref();
	globalPoseTransform->addChild(attachedVisualizationsSeparator);

	if (!visualization)
		visualization = new osg::Node; // create dummy node

	globalPoseTransform->addChild(visualization);
}


/**
 */
OSGVisualizationNode::~OSGVisualizationNode()
{
	if (visualization)
		visualization->unref();
	if (visualizationAtGlobalPose)
		visualizationAtGlobalPose->unref();
	if (attachedVisualizationsSeparator)
		attachedVisualizationsSeparator->unref();
}

/**
 * This method returns OSGVisualizationNode::triMeshModel.
 * If the model doesn't exist construct it by calling
 * OSGVisualizationNode::createTriMeshModel().
 */
TriMeshModelPtr OSGVisualizationNode::getTriMeshModel()
{
	if (!triMeshModel)
		createTriMeshModel();
	return triMeshModel;
}


/**
 * This method constructs an instance of TriMeshModel and stores it in
 * OSGVisualizationNode::triMeshModel.
 * If OSGVisualizationMode::visualization is invalid VirtualRobotException
 * is thrown.
 * Otherwise OSGVisualizationNode::InentorTriangleCB() is called on the
 * OSG graph stored in OSGVisualizationNode::visualization.
 */
void OSGVisualizationNode::createTriMeshModel()
{
	THROW_VR_EXCEPTION_IF(!visualization, "OSGVisualizationNode::createTriMeshModel(): no OSG model present!");

	if (triMeshModel)
		triMeshModel->clear();
	else
		triMeshModel.reset(new TriMeshModel());

	// check if node is a geode
	osg::Geode* visuGeode = visualization->asGeode();
	if (visuGeode)
	{
		osg::TriangleFunctor<osgTriangleConverter> tf;
		tf.triMeshModel = triMeshModel;
		addGeodeTriData(visuGeode,triMeshModel);
	} else
	{
		// check if node is a group
		osg::Group* visuGroup = visualization->asGroup();
		if (visuGroup)
		{
			addGroupTriData(visuGroup,triMeshModel);
		}
	}
}
void OSGVisualizationNode::addGeodeTriData(osg::Geode* geode, TriMeshModelPtr mesh)
{
	if (!geode || !mesh)
		return;
	for ( unsigned int i = 0; i < geode->getNumDrawables(); ++i ) 
	{
		osg::TriangleFunctor<osgTriangleConverter> tf;
		tf.triMeshModel = mesh;
		geode->getDrawable( i )->accept( tf );
	}
}

void OSGVisualizationNode::addGroupTriData(osg::Group* visuGroup, TriMeshModelPtr mesh)
{
	for ( unsigned int i = 0; i < visuGroup->getNumChildren(); ++i ) 
	{
		osg::Geode* geode = visuGroup->getChild(i)->asGeode();
		if (geode)
			addGeodeTriData(geode,triMeshModel);
		else
		{
			osg::Group* group = visuGroup->getChild(i)->asGroup();
			if (group)
				addGroupTriData(group,triMeshModel);
		}
	}
}


/**
 * This mehtod returns the internal OSGVisualizationNode::visualization.
 */
osg::Node* OSGVisualizationNode::getOSGVisualization()
{
	return visualizationAtGlobalPose;
}

void OSGVisualizationNode::setGlobalPose( const Eigen::Matrix4f &m )
{
	globalPose = m;
	if (globalPoseTransform && updateVisualization)
	{
		osg::Matrix mat(globalPose.data());
			/*m(0,0),m(0,1),m(0,2),0,
			m(1,0),m(1,1),m(1,2),0,
			m(2,0),m(2,1),m(2,2),0,
			m(0,3),m(1,3),m(2,3),1
			);*/
		globalPoseTransform->setMatrix(mat);
		//m(reinterpret_cast<SbMat*>(globalPose.data()));
		//globalPoseTransform->matrix.setValue(m);
	}
}

void OSGVisualizationNode::print()
{
	cout << "  OSGVisualization: ";
	if (!triMeshModel)
		createTriMeshModel();
	if (triMeshModel)
	{
		Eigen::Vector3f mi;
		Eigen::Vector3f ma;
		triMeshModel->getSize(mi,ma);
		cout << triMeshModel->faces.size() << " triangles" << endl;// Extend: " << ma[0]-mi[0] << ", " << ma[1] - mi[1] << ", " << ma[2] - mi[2] << endl;
		cout << "    Min point: (" << mi[0] << "," << mi[1] << "," << mi[2] << ")" << endl;
		cout << "    Max point: (" << ma[0] << "," << ma[1] << "," << ma[2] << ")" << endl;

	} else
		cout << "No model" << endl;
}

void OSGVisualizationNode::attachVisualization(const std::string &name, VisualizationNodePtr v)
{
	VisualizationNode::attachVisualization(name,v);

	boost::shared_ptr<OSGVisualizationNode> osgNode = boost::dynamic_pointer_cast<OSGVisualizationNode>(v);
	if (osgNode && osgNode->getOSGVisualization())
	{
		attachedOSGVisualizations[name] = osgNode->getOSGVisualization();
		attachedVisualizationsSeparator->addChild(osgNode->getOSGVisualization());
	}
}

void OSGVisualizationNode::detachVisualization(const std::string &name)
{
	VisualizationNode::detachVisualization(name);
	std::map< std::string, osg::Node* >::const_iterator i = attachedOSGVisualizations.begin();
	while (i!=attachedOSGVisualizations.end())
	{
		if (i->first == name)
		{
			attachedVisualizationsSeparator->removeChild(i->second);
			attachedOSGVisualizations.erase(name);
			return;
		}
		i++;
	}
}


VirtualRobot::VisualizationNodePtr OSGVisualizationNode::clone(bool deepCopy)
{
	osg::Node* newModel = NULL;
	if (visualization)
	{
		if (deepCopy)
		{
			newModel =  static_cast<osg::Node*>(visualization->clone(osg::CopyOp::DEEP_COPY_ALL));
		} else
			newModel = visualization;
	}
	VisualizationNodePtr p(new OSGVisualizationNode(newModel));

	p->setUpdateVisualization(updateVisualization);
	p->setGlobalPose(getGlobalPose());
	p->setFilename(filename,boundingBox);

	// clone attached visualizations
	std::map< std::string, VisualizationNodePtr >::const_iterator i = attachedVisualizations.begin();
	while (i!=attachedVisualizations.end())
	{
		VisualizationNodePtr attachedClone = i->second->clone();
		p->attachVisualization(i->first, attachedClone);
		i++;
	}

	return p;
}

void OSGVisualizationNode::setupVisualization( bool showVisualization, bool showAttachedVisualizations )
{
	VisualizationNode::setupVisualization(showVisualization,showAttachedVisualizations);
	if (!visualizationAtGlobalPose || !attachedVisualizationsSeparator || !visualization)
		return;
	
	if (showAttachedVisualizations && !visualizationAtGlobalPose->containsNode(attachedVisualizationsSeparator))
		visualizationAtGlobalPose->addChild(attachedVisualizationsSeparator);
	if (!showAttachedVisualizations && visualizationAtGlobalPose->containsNode(attachedVisualizationsSeparator))
		visualizationAtGlobalPose->removeChild(attachedVisualizationsSeparator);


	if (showVisualization && !visualizationAtGlobalPose->containsNode(visualization))
		visualizationAtGlobalPose->addChild(visualization);
	if (!showVisualization && visualizationAtGlobalPose->containsNode(visualization))
		visualizationAtGlobalPose->removeChild(visualization);
}


} // namespace VirtualRobot
