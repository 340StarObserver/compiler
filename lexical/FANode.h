/*
Author 		: 	Lv Yang
Created 	: 	09 November 2016
Modified 	: 	11 December 2016
Version 	: 	1.0
*/

#ifndef _FANODE_H
#define _FANODE_H

#include <vector>
using std::vector;

#include <string>
using std::string;

namespace Seven
{
	/* node used in FA( NFA or DFA ) */
	class FANode
	{
	private:
		/* id of this node */
		int _id;

		/* regex type when this node is a end node */
		/* 0 represent it is not a end node */
		int _type;

		/* regex mean when this node is a end node */
		string _mean;

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

		/* get regex type when this node is a end node */
		int getType()const;

		/* set regex type when this node is a end node */
		void setType(int type);

		/* get regex mean when this node is a end node */
		string getMean()const;

		/* set regex mean when this node is a end node */
		void setMean(const string & mean);

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
