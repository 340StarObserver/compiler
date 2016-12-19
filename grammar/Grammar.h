/*
Author 		: 	Lv Yang
Created 	: 	19 December 2016
Modified 	: 	19 December 2016
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
	struct Production
	{
		/*
		例如，要表示 "S -> if S else S"，则 :
			_exp  = { "S", "if", "S", "else", "S" }
			_isVt = { 0, 1, 0, 1, 0 }
		其中 :
			_isVt[i] == 0  表示那个位置是一个非终结符的文法符号
			_isVt[i] == 1  表示那个位置是一个终结符的文法符号
		*/
		vector<string> _exp;
		vector<bool> _isVt;

		/*
		其中 :
			_ppos  是"."的位置
			_sstr  是搜索符
		例如，要表示一个项目集中的元素 [ "S -> ·if S else S", "$" ]，则 :
			_exp 和 _isVt 不变
			_ppos = 0
			_sstr = "$"
		*/
		int _ppos;
		string _sstr;

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
