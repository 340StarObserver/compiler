/*
Author 		: 	Lv Yang
Created 	: 	22 November 2016
Modified 	: 	01 December 2016
Version 	: 	1.0
*/

#ifndef _REGEXCONF_H
#define _REGEXCONF_H

#include <vector>
using std::vector;

#include <string>
using std::string;

namespace Seven
{
	/* one regex conf item */
	struct RegexConfItem
	{
		int id; 			// 该正则的编号( 从1开始 )
		int priority; 		// 该正则的优先级( 越大优先级越高 )
		string mean; 		// 该正则的含义
		string infix; 		// 该正则的中缀表达式
	};


	/* regex conf */
	class RegexConf
	{
	public:
		/* all the regexs' conf items */
		static vector<RegexConfItem> Items;

		/* init from a conf file */
		static void init(const char * path);
	};
}

#endif
