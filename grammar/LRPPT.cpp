/*
Author 		: 	Lv Yang
Created 	: 	20 December 2016
Modified 	: 	21 December 2016
Version 	: 	1.0
*/

#include "LRPPT.h"

#include <queue>
using std::queue;

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


	/* 求LR(1)项目集的闭包 */
	set<Production> LRPPT::closure(const set<Production> & pset)
	{
		// 定义结果集
		set<Production> res;

		// 准备工作队列，并且要把pset中的所有元素扔进该队列
		queue<Production> Q;
		for(set<Production>::iterator it = pset.begin(); it != pset.end(); ++it)
			Q.push(*it);

		// do BFS
		while(Q.empty() == false){
			// 队首出队
			Production p = Q.front();
			Q.pop();

			// if haven't visited p
			if(res.find(p) == res.end()){
				// add p to res
				res.insert(p);

				// 接下来将p的所有扩展结点入队 :
				// p 这个产生式，可以抽象成 [ A -> α·Bβ, a ]
				for(int i = 0; i < Grammar::Plist.size(); i++){
					// if G[i].左部是B，则可以抽象成 B -> γ
					if(Grammar::Plist[i].exp[0] == p.exp[p.ppos]){
						// T = First(βa)
						vector<string> tmp_S;
						vector<bool> tmp_M;
						for(int j = p.ppos + 1; j < p.exp.size(); j++){
							tmp_S.push_back(p.exp[j]);
							tmp_M.push_back(p.isVt[j]);
						}
						tmp_S.push_back(p.sstr);
						tmp_M.push_back(true);
						set<string> T = First(tmp_S, tmp_M, 0);

						// for T中的每个元素t, 将 [ B -> ·γ, t ] 入队
						Production next = Grammar::Plist[i];
						next.ppos = 1;
						for(set<string>::iterator it = T.begin(); it != T.end(); ++it){
							next.sstr = *it;
							Q.push(next);
						}
					}
				}
			}
		}

		return res;
	}


	/* LR(1)项目集的goTo操作 */
	set<Production> LRPPT::goTo(const set<Production> & pset, const string & X)
	{
		set<Production> res;

		for(set<Production>::iterator it = pset.begin(); it != pset.end(); ++it){
			Production p = *it;

			// p 可以抽象成 [ A -> α·Xβ, a ]
			// add [ A -> αX·β, a ] to res
			if(p.exp[p.ppos] == X){
				p.ppos = p.ppos + 1;
				res.insert(p);
			}
		}

		return res;
	}


	/* 判断某项目集是否已经出现过 */
	int LRPPT::existState(const vector< set<Production> > & U, const set<Production> & pset)
	{
		for(int i = 0; i < U.size(); i++){
			/* compare U[i] and pset */
			if(U[i].size() == pset.size()){
				bool w = true;
				for(set<Production>::iterator it = U[i].begin(); it != U[i].end(); ++it){
					if(pset.find(*it) == pset.end()){
						w = false;
						break;
					}
				}
				if(w == true)
					return i;
			}
		}

		/* not found */
		return -1;
	}


	/* 构造LR(1)文法的项目集族 */
	void LRPPT::stateRace(vector< set<Production> > & U)
	{
		// first clean U
		U.clear();

		// assume G[0] is like "A -> B", calculate i0 = closure({ ["A -> ·B", $] })
		Production p = Grammar::Plist[0];
		p.ppos = 1;
		p.sstr = "$";
		set<Production> i0;
		i0.insert(p);
		i0 = closure(i0);

		// prepare a work queue
		queue< set<Production> > Q;
		Q.push(i0);

		// do BFS
		while(Q.empty() == false){
			// get the top
			set<Production> cur = Q.front();
			Q.pop();

			// if this state hasn't been visited
			if(existState(U, cur) == -1){
				// add cur to U
				U.push_back(cur);

				// E = cur 的每个产生式里，位于·后面的文法符号的集合
				set<string> E;
				for(set<Production>::iterator p_it = cur.begin(); p_it != cur.end(); ++p_it){
					p = *p_it;
					if(p.ppos < p.exp.size() && p.exp[p.ppos] != Production::Null)
						E.insert(p.exp[p.ppos]);
				}

				// 接下来把 cur 的所有扩展结点入队
				for(set<string>::iterator e_it = E.begin(); e_it != E.end(); ++e_it)
					Q.push( closure( goTo(cur, *e_it) ) );
			}
		}
	}

}
