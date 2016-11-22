/*
Author 		: 	Lv Yang
Created 	: 	18 November 2016
Modified 	: 	18 November 2016
Version 	: 	1.0
*/

#include "ODFA.h"

namespace Seven
{
	/*
	查找状态state，属于当前划分的哪一个等价类中
	返回值解释 :
		返回那个等价类的下标，若没找到，则返回-1
	*/
	int ODFA::find(const vector< set<int> > & U, int state)
	{
		int n = U.size();
		for(int i = 0; i < n; i++){
			if(U[i].find(state) != U[i].end())
				return i;
		}
		return -1;
	}

}
