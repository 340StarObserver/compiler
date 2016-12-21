/*
Author 		: 	Lv Yang
Created 	: 	19 December 2016
Modified 	: 	21 December 2016
Version 	: 	1.0
*/

#ifndef _GRAMMAR_H
#define _GRAMMAR_H

#include <vector>
using std::vector;

#include <string>
using std::string;

namespace Seven
{
	/* 产生式 */
	class Production
	{
	public:
		// ε
		static string Null;

		/*
		例如，要表示 "S -> if S else S"，则 :
			exp  = { "S", "if", "S", "else", "S" }
			isVt = { 0, 1, 0, 1, 0 }
		其中 :
			isVt[i] == 0  表示那个位置是一个非终结符的文法符号
			isVt[i] == 1  表示那个位置是一个终结符的文法符号
		*/
		vector<string> exp;
		vector<bool> isVt;

		/*
		其中 :
			ppos  是"."的位置
			sstr  是搜索符
		例如，要表示一个项目集中的元素 [ "S -> ·if S else S", "$" ]，则 :
			exp 和 isVt 不变
			ppos = 0
			sstr = "$"
		*/
		int ppos;
		string sstr;

		/* operator < */
		bool operator < (const Production & p)const;

		/*
		可见，我把原文法产生式 & 构造LR(1)语法分析表时用到的项目集元素，合并了起来
		因为后者相对于前者，就多了两个属性嘛，而且不会对前两个属性产生影响
		当我需要用这个类来表示原文法产生式的时候，后两个属性不管它即可
		*/
	};


	/* 文法类 */
	class Grammar
	{
	public:
		/*
		文法是一组产生式的集合
		注意，产生式的下标就是它的编号（从零开始）
		注意，确保零号产生式是 "S' -> S"
		*/
		static vector<Production> Plist;

		/* 读取文法配置文件 */
		static void init(const char * path);
	};

}

#endif