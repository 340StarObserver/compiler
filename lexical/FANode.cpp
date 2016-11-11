/*
Author 		: 	Lv Yang
Created 	: 	09 November 2016
Modified 	: 	11 November 2016
Version 	: 	1.0
*/

#include "FANode.h"

namespace Seven
{
	/* constructor */
	FANode::FANode(int id)
	{
		_id = id;
		_terminate = false;
	}

	/* deconstructor */
	FANode::~FANode()
	{
		_edges.clear();
		_nexts.clear();
	}

	/* get the id */
	int FANode::getId()const
	{
		return _id;
	}

	/* get whether this node is terminate state */
	bool FANode::isTerminate()const
	{
		return _terminate;
	}

	/* set whether this node is terminate state */
	void FANode::setTerminate(bool terminate)
	{
		_terminate = terminate;
	}

	/* get Vt of each edge */
	vector<int> * FANode::getEdges()
	{
		return &_edges;
	}

	/* get next nodes */
	vector<FANode *> * FANode::getNexts()
	{
		return &_nexts;
	}

	/* add a next node */
	/*
	parameters :
		vt 	: 	the Vt of this edge
		node 	: 	this edge connect to which child node
	*/
	void FANode::addNext(int vt, FANode * node)
	{
		_edges.push_back(vt);
		_nexts.push_back(node);
	}

}
