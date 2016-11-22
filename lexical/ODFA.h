/*
Author 		: 	Lv Yang
Created 	: 	18 November 2016
Modified 	: 	18 November 2016
Version 	: 	1.0
*/

#ifndef _ODFA_H
#define _ODFA_H

#include <vector>
using std::vector;

#include <set>
using std::set;

namespace Seven
{
	/* optimized DFA */
	class ODFA
	{
	public:
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
		// static bool split(const vector<int *> & table, int vt_num, vector< set<int> > & U, int index);

		/*
		查找状态state，属于当前划分的哪一个等价类中
		返回值解释 :
			返回那个等价类的下标，若没找到，则返回-1
		*/
		static int find(const vector< set<int> > & U, int state);
	};
}

#endif
