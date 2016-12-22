/*
Author 		: 	Lv Yang
Created 	: 	20 December 2016
Modified 	: 	21 December 2016
Version 	: 	1.0
*/

#ifndef _LRPPT_H
#define _LRPPT_H

#include "Grammar.h"

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


		/*
		求LR(1)项目集的闭包
		参数的解释 :
			pset 	: 	产生式集合
		返回值解释 :
			产生式集合
		*/
		static set<Production> closure(const set<Production> & pset);


		/*
		LR(1)项目集的goTo操作
		参数的解释 :
			pset 	: 	产生式集合
			X 	: 	文法符号（可以是终结符，也可以是非终结符）
		返回值解释 :
			产生式集合
		注意的地方 :
			该方法经常和closure配合使用，比如 I1 = closure( goTo(I0, "if") )
		*/
		static set<Production> goTo(const set<Production> & pset, const string & X);


		/*
		判断某项目集是否已经出现过
		参数的解释 :
			U 	: 	当前构建的所有项目集
			pset 	: 	目标项目集
		返回值解释 :
			若找到则返回在U中的下标，反之返回 -1
		*/
		static int existState(const vector< set<Production> > & U, const set<Production> & pset);


		/*
		构造LR(1)文法的项目集族
		参数的解释 :
			U 	: 	用以保存项目集族
		注意的地方 :
			执行之前，确保进行了Grammar::init
		*/
		static void stateRace(vector< set<Production> > & U);
	};
}

#endif
