/*
Author 		: 	Lv Yang
Created 	: 	14 November 2016
Modified 	: 	23 November 2016
Version 	: 	1.0
*/

#ifndef _DFA_H
#define _DFA_H

#include "NFA.h"

#include <set>
using std::set;

#include <vector>
using std::vector;

#include <string>
using std::string;

namespace Seven
{
	/* DFA */
	class DFA
	{
	private:
		/* extract all nodes from a NFA */
		/*
		1. Eg. a NFA has 7 nodes, their id is 1~7
			it will return a array with 8 elements, index 1~7 really used
			array[i] points to a node whose id is i
		2. parameter 'int & num' used to get the number of nodes
		*/
		static FANode ** extract_nodes(const NFA * nfa, int & num);


		/* extract all vt(terminal symbols) */
		/*
		1. Eg. a NFA has {a,b,c} vts
			it will return a int array = { int('a'), int('b'), int('c') }
		2. ε is not in the result array
		3. parameter 'int & num' used to get the number of vts
		*/
		static int * extract_vts(const NFA * nfa, int & num);


		/* get ε-closure of a set C */
		/*
		parameters :
			'nodes', you can get it by DFA::extract_nodes
			'C' is a set such as {1,3,5}
		*/
		static set<int> closure(FANode ** nodes, const set<int> & C);


		/* goto(C, X) */
		/*
		parameters :
			'nodes', you can get it by DFA::extract_nodes
			'C' is a set such as {1,3,5}
			'vt' is a terminal symbol
		tip :
			after use this function, usually use closure
				Eg. I1=ε-closure(goto(I0,a))
		*/
		static set<int> goTo(FANode ** nodes, const set<int> & C, int vt);


		/* judge whether a state-set already exist, if exist return the index, else -1 */
		/*
		Eg. Clist=[{1,2,4},{3,5,6}]
		      C={1,2,4} already exist in Clist
		      C={1,3,5} not exist in Clist
		*/
		static int find_state(const vector< set<int> > & Clist, const set<int> & C);

	private:
		/* private constructor */
		DFA();

		/* private set vts */
		void setVts(int * vts, int vtNum);

		/* private set types */
		void setEndTypes(int * types);

	private:
		/* the number of vt */
		int _vtNum;

		/* the vts */
		int * _vts;

		/* the state transfer table */
		vector<int *> _table;

		/* mark each state's end-type */
		int * _types;

		/* mark each state's end-mean */
		string * _means;

	public:
		/* deconstructor */
		~DFA();

		/* get the number of vt */
		int getVtNum()const;

		/* get the vts */
		int * getVts()const;

		/* get state transfer table */
		vector<int *> * getTable();

		/* get type[] which represent each state's end-type */
		int * getEndTypes()const;

		/* get mean[] which represent each state's end-mean */
		string * getEndMeans()const;

		/* create a DFA from a NFA */
		static DFA * create(const NFA * nfa);
	};
}

#endif
