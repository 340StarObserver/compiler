/*
Author 		: 	Lv Yang
Created 	: 	18 November 2016
Modified 	: 	01 December 2016
Version 	: 	1.0
*/

#ifndef _ODFA_H
#define _ODFA_H

#include "DFA.h"

#include <iostream>
using std::ostream;

namespace Seven
{
	/* optimized DFA */
	class ODFA
	{
	private:
		/*
		把状态总集T, 拆分为 非终结态集A 和 终结态集B
		参数的解释 :
			T 		T[i]==0  <==> state i is not a end node; T[i] != 0  <==> state i is a end node
			n 		the length of array T
			A 		to save 非终结态集A
			B 		to save 终结态集B
		*/
		static void init_split(const int * T, int n, set<int> & A, set<int> & B);


		/*
		把终结态集B按照终结状态对应的正规表达式来分成很多个小集合
		拆分准则 :
			1. 同一个小集合里的多个终结状态，它们对应的正规表达式是同一个
			2. 不同小集合里的多个终结状态，它们对应的正规表达式不是同一个
		为何如此 ?
			两个终结状态S1,S2，尽管它们是弱等价的，但是对应不同的正规表达式，应该分离
			否则会导致终结冲突
		参数的解释 :
			T 		T[i]==0  <==> state i is not a end node; T[i] != 0  <==> state i is a end node
			B 		终结态集
			bs 		to save 很多个小集合
		*/
		static void deal_ends(const int * T, const set<int> & B, vector< set<int> > & bs);


		/*
		查找状态state，属于当前划分的哪一个等价类中
		返回值解释 :
			返回那个等价类的下标，若没找到，则返回-1
		*/
		static int find(const vector< set<int> > & U, int state);


		/*
		用来拆分状态集的函数
		参数的解释 :
			table 		是DFA的状态转化表
			vt_num 	是终结符的总个数，即table中的每一行的列数
			U 		是当前的等价划分
			index 		是我想对 U[index] 进行拆分
		返回值解释 :
			当需要对 U[index] 进行进一步拆分 :
				从U中移除U[index]
				把拆分后的两个新的状态集A1,A2添加到U的尾部
				return true
			当不需要对 U[index] 进行进一步拆分 :
				return false
		*/
		static bool split(const vector<int *> & table, int vt_num, vector< set<int> > & U, int index);
		

		/*
		把一个DFA的所有状态划分成若干个等价类
		参数的解释 :
			dfa 		the input DFA
			U 		to save the result of 等价类划分
		*/
		static void calc_divisions(DFA * dfa, vector< set<int> > & U);


		/*
		根据划分好的等价类，构建新的状态转换表
		参数的解释 :
			dfa 		the input DFA
			U 		the result of 等价类划分, you can get it by ODFA::calc_divisions
		返回值解释 :
			m行n列的矩阵的一维数组形式 table[m*n]
			m 是ODFA的状态数
			n  是终结符的总数
			table[i * n + j]表示ODFA中状态i，在j号终结符的作用下，到达的后继状态的编号
		*/
		static int * calc_table(DFA * dfa, const vector< set<int> > & U);


		/*
		标记每个新的终结状态对应了哪种词素
		参数的解释 :
			dfa 		the input DFA
			U 		the result of 等价类划分, you can get it by ODFA::calc_divisions
		返回值解释 :
			m列的一维数组 types[]
			types[i] == 0    <==>    新的状态i不是一个终结结点
			types[i] != 0    <==>    新的状态i是一个终结结点，且它表示了对应的正则的代号
		*/
		static int * calc_types(DFA * dfa, const vector< set<int> > & U);

	private:
		/* private constructor */
		ODFA();

	private:
		int _vtNum; 		// the number of vt
		int * _vts; 		// the vts[]

		int _sNum; 		// the number of states
		int * _tables; 		// the state-transfer-table

		int * _types; 		// states' end-situation

		int _entrance; 		// the new entrance state

	public:
		/* deconstructor */
		~ODFA();


		/* get the number of vt */
		int getVtNum()const;

		/* get the number of state */
		int getStateNum()const;

		/* get the entrance state */
		int getEntranceState()const;

		/* get the list of vts */
		int * getVts()const;

		/* get the state-transfer-table */
		int * getTables()const;

		/* get states' end-situation */
		int * getEndTypes()const;


		/* create a ODFA by given a DFA */
		static ODFA * create(DFA * dfa);

		/* save this ODFA to a file */
		void save(const char * path)const;

		/* load a ODFA from a file */
		static ODFA * load(const char * path);


		/*
		扫描一段文本做词法分析
		参数的解释 :
			text 		待分析的文本
			resOut 		分析结果的输出流( 建议输出到文件 )
			errorOut 	报错的输出流( 建议输出到文件 )
		结果输出流 :
			每一行是 {"id" : 内码, "word" : 词语, "type" : 类型}
		报错输出流 :
			每一行是 {"line" : 行号, "offset" : 行内序号, "word" : 错误词语}
		*/
		void scan(const string & text, ostream & resOut, ostream & errorOut)const;
	};
}

#endif
