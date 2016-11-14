/*
Author 		: 	Lv Yang
Created 	: 	14 November 2016
Modified 	: 	14 November 2016
Version 	: 	1.0
*/

#ifndef _DFA_H
#define _DFA_H

#include "NFA.h"

namespace Seven
{
	/* DFA */
	class DFA
	{
	public:
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
	};
}

#endif
