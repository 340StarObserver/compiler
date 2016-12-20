/*
Author 		: 	Lv Yang
Created 	: 	20 December 2016
Modified 	: 	20 December 2016
Version 	: 	1.0
*/

#ifndef _LRPPT_H
#define _LRPPT_H

#include <string>
using std::string;

#include <set>
using std::set;

#include <vector>
using std::vector;

namespace Seven
{
	/* LR(1)语法的预测分析表 */
	class LRPPT
	{
	public:
		/*
		计算文法符号串S的First
		参数的解释 :
			S 	: 	文法符号串，例如"AaB"应该表示成["A","a","B"]
			M 	: 	文法串中各符号是否是终结符
			index 	: 	当前分析S中的哪个符号(>=0)
		返回值解释 :
			终结符集合
		注意的地方 :
			执行之前，确保进行了Grammar::init
		*/
		static set<string> First(const vector<string> & S, const vector<bool> & M, int index);
	};
}

#endif
