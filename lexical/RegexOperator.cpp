/*
Author 		: 	Lv Yang
Created 	: 	08 November 2016
Modified 	: 	08 November 2016
Version 	: 	1.0
*/

#include "RegexOperator.h"

namespace Seven
{
	/* judge whether an op is supported */
	bool RegexOperator::support(char op)
	{
		if(op == '(')
			return true;
		if(op == ')')
			return true;
		if(op == '*')
			return true;
		if(op == '|')
			return true;
		if(op == '.')
			return true;
		return false;
	}

	/* get an op's feature( has one operand | has two operands | ... ) */
	int RegexOperator::feature(char op)
	{
		if(op == '*')
			return 1;
		if(op == '|')
			return 2;
		if(op == '.')
			return 2;
		// '(' or ')' or unsupported-operators, return 0
		return 0;
	}

	/* get an op's priority when this op is in a stack */
	int RegexOperator::innerPriority(char op)
	{
		if(op == '(')
			return 1;
		if(op == ')')
			return 7;
		if(op == '*')
			return 6;
		if(op == '|')
			return 3;
		if(op == '.')
			return 3;
		// unsupported-operators, return 0
		return 0;
	}

	/* get an op's priority when this op isn't in a stack */
	int RegexOperator::outerPriority(char op)
	{
		if(op == '(')
			return 7;
		if(op == ')')
			return 1;
		if(op == '*')
			return 6;
		if(op == '|')
			return 2;
		if(op == '.')
			return 4;
		// unsupported-operators, return 0
		return 0;
	}

}
