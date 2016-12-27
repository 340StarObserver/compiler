/*
Author 		: 	Lv Yang
Created 	: 	20 December 2016
Modified 	: 	27 December 2016
Version 	: 	1.0
*/

#ifndef _LRPPT_H
#define _LRPPT_H

#include "Grammar.h"

#include <iostream>
using std::cout;
using std::ostream;
using std::pair;

namespace Seven
{
	/* LR(1)语法的预测分析表 */
	class LRPPT
	{
	private:
		/*
		计算文法符号串S的First
		参数的解释 :
			S 	: 	文法符号串，例如"AaB"应该表示成["A","a","B"]
			M 	: 	文法串中各符号是否是终结符
			index 	: 	当前分析S中的哪个符号(>=0)
		返回值解释 :
			终结符集合
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
		static int findState(const vector< set<Production> > & U, const set<Production> & pset);


		/*
		构造LR(1)文法的项目集族
		参数的解释 :
			U 	: 	用以保存项目集族
		*/
		static void stateRace(vector< set<Production> > & U);


		/*
		构造预测分析表
		参数的解释 :
			U 	: 	项目集族
			A 	: 	终结符列表
			B 	: 	非终结符列表
			TA 	: 	用以记录Action表
			TG 	: 	用以记录Goto表
		注意的地方 :
			1.
				U.size = m
				A.size = n1
				B.size = n2
				TA 是一维数组，长度是 m * n1
				TG 是一维数组，长度是 m * n2
			2.
				TA[i] = k  ( k>=1 ) 	// 移动状态k进栈
				TA[i] = -k ( k>=1 ) 	// 按k号产生式归约
				TA[i] = m 		// Accept
				TA[i] = 0 		// error
			3.
				TG[i] = k ( k>=1 ) 	// goto状态k
				TG[i] = 0 		// error
		*/
		static void buildPredictTable(const vector< set<Production> > & U, const vector<string> & A, const vector<string> & B, int * TA, int * TG);

		/*
		处理移动-归约冲突
		参数的解释 :
			TA 	: 	预测分析表Action
			cols 	: 	每行列数
			i 	: 	冲突行号
			j 	: 	冲突列号
			sx 	: 	移动状态x入栈( x>=1 )
			ry 	: 	按y号产生式归约( y>=1 )
			vt 	: 	当前读头下的文法符号
		*/
		static void dealCollision(int * TA, int cols, int i, int j, int sx, int ry, const string & vt);

	private:
		/*
		以json格式记录一条结果
		参数的解释 :
			out 	: 	输出流
			left 	: 	产生式左部
			right 	: 	[ 右部单词1, 右部单词2, ... ]
		*/
		static void log_res(ostream & out, const string & left, const vector<string> & right);

		/*
		以json格式记录一条报错
		参数的解释 :
			out 	: 	输出流
			word 	: 	出错单词
		*/
		static void log_error(ostream & out, const string & word);

	private:
		/* 终结符列表( 包含 $ ) */
		vector<string> _symbol_A;

		/* 非终结符列表( 不包含 S' ) */
		vector<string> _symbol_B;

		/* Action-Table */
		int * _table_action;

		/* Goto-Table */
		int * _table_goto;

		/* rows of Action-Table and Goto-Table */
		int _rows;

	private:
		/* private constructor */
		LRPPT();

	public:
		/* create */
		static LRPPT * create();

		/* desconstructor */
		~LRPPT();

		/* print the LRPPT */
		void print()const;


		/*
		对一段token序列做语法检查
		参数的解释 :
			tokens  	: 	token序列，里面每个pair形如 <文法符号, 对应代码中的单词>
			out_res 	: 	结果输出流
			out_error 	: 	报错输出流
		结果输出流 :
			每一行是 一个归约式, 形如 { "left" : 产生式左部, "right" : [ 右部单词1, 右部单词2, ... ] }
		报错输出流 :
			每一行是 一个出错点, 形如 { "word" : 出错单词 }
		*/
		void scan(const vector< pair<string, string> > & tokens, ostream & out_res, ostream & out_error)const;


		/*
		对一个token序列的文件做语法检查
		参数的解释 :
			path_input 	输入的token序列文件的路径
			path_res 	输出的结果文件的路径
			path_error 	输出的报错文件的路径
		注意的地方 :
			输入文件是词法分析的结果文件
		*/
		void scan(const char * path_input, const char * path_res, const char * path_error)const;


		// 定义两个scan的考虑 :
		// 1. 第一个scan方法更灵活
		// 	待分析token序列可以来自任何地方
		// 	结果和报错也可以重定向到多种地方( 屏幕 or 文件 or 网络 )
		// 2. 第二个scan方法更方便
		// 	大多数使用场景，数据源和结果都是文件，故调用方便
	};
}

#endif
