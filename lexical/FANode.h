/*
Author 		: 	Lv Yang
Created 	: 	09 November 2016
Modified 	: 	11 November 2016
Version 	: 	1.0
*/

#ifndef _FANODE_H
#define _FANODE_H

#include <vector>
using std::vector;

namespace Seven
{
	/* node used in FA( NFA or DFA ) */
	class FANode
	{
	private:
		/* id of this node */
		int _id;

		/* whether this node is terminate state */
		/* this item only used in DFA */
		bool _terminate;

		/* Vt of each edge */
		/* -1 represent a null edge */
		vector<int> _edges;

		/* next nodes */
		vector<FANode *> _nexts;
	public:
		/* the null edge */
		const static int NullEdge = -1;

		/* constructor */
		FANode(int id);

		/* deconstructor */
		~FANode();

		/* get the id */
		int getId()const;

		/* get whether this node is terminate state */
		bool isTerminate()const;

		/* set whether this node is terminate state */
		void setTerminate(bool terminate);

		/* get Vt of each edge */
		vector<int> * getEdges();

		/* get next nodes */
		vector<FANode *> * getNexts();

		/* add a next node */
		/*
		parameters :
			vt 	: 	the Vt of this edge
			node 	: 	this edge connect to which child node
		*/
		void addNext(int vt, FANode * node);
	};
}

#endif
