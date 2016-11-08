/*
Author 		: 	Lv Yang
Created 	: 	08 November 2016
Modified 	: 	08 November 2016
Version 	: 	1.0
*/

#ifndef _REGEX_H
#define _REGEX_H

#include <stack>
using std::stack;

#include <string>
using std::string;

namespace Seven
{
	/* regex when used in lexical analyzer */
	class Regex
	{
	private:
		/* encapsulate an action */
		static void action(stack<char> & opstack,stack<string> & expstack);
	public:
		/* transfer a infix-regex into a suffix-regex */
		static string transfer(const string & infix);
	};
}

#endif
