/*
Author 		: 	Lv Yang
Created 	: 	08 November 2016
Modified 	: 	08 November 2016
Version 	: 	1.0
*/

#ifndef _REGEXOPERATOR_H
#define _REGEXOPERATOR_H

namespace Seven
{
	/* operator in regex */
	class RegexOperator
	{
	public:
		/* judge whether an op is supported */
		static bool support(char op);

		/* get an op's feature( has one operand | has two operands | ... ) */
		static int feature(char op);

		/* get an op's priority when this op is in a stack */
		static int innerPriority(char op);

		/* get an op's priority when this op isn't in a stack */
		static int outerPriority(char op);
	};
}

#endif
