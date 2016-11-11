/*
Author 		: 	Lv Yang
Created 	: 	09 November 2016
Modified 	: 	11 November 2016
Version 	: 	1.0
*/

#ifndef _NFA_H
#define _NFA_H

#include "FANode.h"

#include <vector>
using std::vector;

#include <string>
using std::string;

namespace Seven
{
	/* NFA */
	class NFA
	{
	private:
		FANode * _start; 	// the start node
		FANode * _end; 	// the end node

		/* used in deconstructor */
		bool contains(const vector<FANode *> & pool, FANode * node)const;
	public:
		/* constructor */
		/*
		build a NFA according to a Vt
		Example :
			vt = int('a'), start_id = 7
			then it will create a NFA like 7------>8, its edge is 'a'
		*/
		NFA(int vt, int start_id);

		/* deconstructor */
		~NFA();

		/* get the start node */
		FANode * getStart()const;

		/* get the end node */
		FANode * getEnd()const;

		/* set the start node */
		void setStart(FANode * node);

		/* set the end node */
		void setEnd(FANode * node);

		/* do closure-change( NFA to NFA* ) on a NFA */
		static void closure(NFA * nfa, int start_id);

		/* merge two NFAs by a '|' */
		static void merge(NFA * left, NFA * right, int start_id);

		/* join two NFAs by '.' */
		static void join(NFA * left, NFA * right);

		/* create a NFA by given a suffix regex */
		static NFA * create(const string & suffixRegex, int & start_id);

		/* create a big NFA by given all the suffix regex */
		static NFA * create(const vector<string> & suffixs);
	};
}

#endif
