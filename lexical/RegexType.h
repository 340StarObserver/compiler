/*
Author 		: 	Lv Yang
Created 	: 	22 November 2016
Modified 	: 	29 November 2016
Version 	: 	1.0
*/

#ifndef _REGEXTYPE_H
#define _REGEXTYPE_H

#include <vector>
using std::vector;

#include <string>
using std::string;

namespace Seven
{
	/* Regex Type */
	class RegexType
	{
	public:
		/* table of id-regex */
		static vector<string> Infixs;

		/* table of id-mean */
		static vector<string> Means;

		/* table of id-priority */
		static vector<int> Prioritys;

	public:
		/* init from a conf file */
		static void init(const char * path);

		/* give a priority of a type of regex */
		static int priority(int type);
	};
}

#endif
