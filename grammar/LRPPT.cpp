/*
Author 		: 	Lv Yang
Created 	: 	20 December 2016
Modified 	: 	20 December 2016
Version 	: 	1.0
*/

#include "LRPPT.h"
#include "Grammar.h"

namespace Seven
{
	/* 计算文法符号串S的First */
	set<string> LRPPT::First(const vector<string> & S, const vector<bool> & M, int index)
	{
		set<string> res;

		// 如果当前要分析的文法符号是终结符
		if(M[index] == true){
			res.insert(S[index]);
			return res;
		}

		// 当前要分析的文法符号是非终结符，则必定会出现在文法G的某个产生式的左部
		int n = Grammar::Plist.size();
		for(int i = 0; i < n; i++){
			Production p = Grammar::Plist[i];

			// p.左部 == 当前要分析的文法符号
			// p.右部的第一个符号 != 左部 (为了避免陷入死循环)
			// 则需要把p.右部的First也并进来
			if(p.exp[0] == S[index] && p.exp[1] != S[index]){
				set<string> tmp = First(p.exp, p.isVt, 1);
				for(set<string>::iterator it = tmp.begin(); it != tmp.end(); ++it)
					res.insert(*it);
			}
		}

		// ε ∈ res, 则需要把下一个文法符号的First也并进来
		if(res.find(Production::Null) != res.end() && index < S.size() - 1){
			set<string> tmp = First(S, M, index + 1);
			for(set<string>::iterator it = tmp.begin(); it != tmp.end(); ++it)
				res.insert(*it);
		}

		return res;
	}

}
