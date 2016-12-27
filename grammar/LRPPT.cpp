/*
Author 		: 	Lv Yang
Created 	: 	20 December 2016
Modified 	: 	27 December 2016
Version 	: 	1.0
*/

#include "LRPPT.h"

#include <queue>
using std::queue;

#include <cstring>
using std::memset;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios;

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
using rapidjson::Document;
using rapidjson::Writer;
using rapidjson::StringBuffer;
using rapidjson::StringRef;

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
		if(res.find(Production::NullSymbol) != res.end() && index < S.size() - 1){
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
					if(p.ppos < p.exp.size() && Grammar::Plist[i].exp[0] == p.exp[p.ppos]){
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
			if(p.ppos < p.exp.size() && p.exp[p.ppos] == X){
				p.ppos = p.ppos + 1;
				res.insert(p);
			}
		}

		return res;
	}


	/* 判断某项目集是否已经出现过 */
	int LRPPT::findState(const vector< set<Production> > & U, const set<Production> & pset)
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
		p.sstr = Production::EndSymbol;
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
			if(findState(U, cur) == -1){
				// add cur to U
				U.push_back(cur);

				// E = cur 的每个产生式里，位于·后面的文法符号的集合
				set<string> E;
				for(set<Production>::iterator p_it = cur.begin(); p_it != cur.end(); ++p_it){
					p = *p_it;
					if(p.ppos < p.exp.size() && p.exp[p.ppos] != Production::NullSymbol)
						E.insert(p.exp[p.ppos]);
				}

				// 接下来把 cur 的所有扩展结点入队
				for(set<string>::iterator e_it = E.begin(); e_it != E.end(); ++e_it)
					Q.push( closure( goTo(cur, *e_it) ) );
			}
		}
	}


	/* 构造预测分析表 */
	void LRPPT::buildPredictTable(const vector< set<Production> > & U, const vector<string> & A, const vector<string> & B, int * TA, int * TG)
	{
		// TA[m*n1], TG[m*n2]
		int m = U.size();
		int n1 = A.size();
		int n2 = B.size();

		// set all item 0 ( 0 represent error )
		memset(TA, 0, sizeof(int) * m * n1);
		memset(TG, 0, sizeof(int) * m * n2);

		// "accept" = [ S' -> S·, $ ]
		Production accept = Grammar::Plist[0];
		accept.ppos = 2;
		accept.sstr = Production::EndSymbol;

		for(int i = 0; i < m; i++)
		{
			/*
			U[i] 中的项目 :
				可能形如 [ A -> α·aβ, b ] ，其中a是终结符
				可能形如 [ A -> α·,     a ] ，其中A ≠ S'
				可能形如 [ A -> α·Bβ, b ] ，其中B是非终结符
			*/
			for(set<Production>::iterator p_it = U[i].begin(); p_it != U[i].end(); ++p_it){
				Production p = *p_it;

				if(p.ppos == p.exp.size()){
					if(p.exp[0] != Grammar::Plist[0].exp[0]){
						// 形如 [ A -> α·,     a ] ，其中A ≠ S'
						Production tmp = p;
						tmp.ppos = 0;
						tmp.sstr = "";
						// 则置 Goto表(状态i, a) = A -> α 的编号
						int k = Grammar::findProduction(tmp);
						int j = Grammar::findSymbol(A, p.sstr);
						if(k != -1 && j != -1){
							if(TA[i * n1 + j] == 0)
								TA[i * n1 + j] = -k;
							else if(TA[i * n1 + j] != -k){
								// 原先该位置有值 且 原值不等于冲突值，才需要处理冲突
								dealCollision(TA, n1, i, j, TA[i * n1 + j], k, p.sstr);
							}
						}
					}
				}
				else if(p.isVt[p.ppos] == false){
					// 形如 [ A -> α·Bβ, b ] ，其中B是非终结符
					// goto(状态i, B) 的编号 = k
					// 则置 Action表(状态i, B) = k
					int k = findState(U, closure(goTo(U[i], p.exp[p.ppos])));
					int j = Grammar::findSymbol(B, p.exp[p.ppos]);
					if(k != -1 && j != -1)
						TG[i * n2 + j] = k;
				}
				else if(p.exp[p.ppos] != Production::NullSymbol){
					// 形如 [ A -> α·aβ, b ] ，其中a是终结符
					// goto(状态i, a) 的编号 = k
					// 则置 Action表(状态i, a) = 移动状态k进栈
					int k = findState(U, closure(goTo(U[i], p.exp[p.ppos])));
					int j = Grammar::findSymbol(A, p.exp[p.ppos]);
					if(k != -1 && j != -1){
						if(TA[i * n1 + j] == 0)
							TA[i * n1 + j] = k;
						else if(TA[i * n1 + j] != k){
							// 原先该位置有值 且 原值不等于冲突值，才需要处理冲突
							dealCollision(TA, n1, i, j, k, -TA[i * n1 + j], p.exp[p.ppos]);
						}
					}
				}
			}

			// 若 [ S' -> S·, $ ] 属于 U[i]
			// 则置 Action表(状态i, $) = "accept"
			if(U[i].find(accept) != U[i].end()){
				int j = Grammar::findSymbol(A, Production::EndSymbol);
				TA[i * n1 + j] = m;
			}
		}
	}


	/* 处理移动-归约冲突 */
	void LRPPT::dealCollision(int * TA, int cols, int i, int j, int sx, int ry, const string & vt)
	{
		// 当前栈内优先级 pin = y号产生式中最后一个终结符的优先级
		int pin = 0;
		int n = Grammar::Plist[ry].exp.size() - 1;
		while(n >= 0){
			if(Grammar::Plist[ry].isVt[n] == true){
				GSrule rule(Grammar::Plist[ry].exp[n], 0, 0);
				set<GSrule>::iterator it = Grammar::VtRules.find(rule);
				if(it != Grammar::VtRules.end()){
					pin = (*it).getPriority();
					break;
				}
			}
			n--;
		}

		// pout = vt的优先级
		// w     = vt的结合规则
		int pout = 0;
		bool w = false;
		for(set<GSrule>::iterator it = Grammar::VtRules.begin(); it != Grammar::VtRules.end(); ++it){
			if((*it).getSymbol() == vt){
				pout = (*it).getPriority();
				w = (*it).getCombine();
				break;
			}
		}

		if((pin < pout) || (pin == pout && w == false)){
			// may be 1. 栈内距离栈顶最近的终结符的优先级 < 栈外读头下的文法符号的优先级
			// may be 2. 优先级相同，但读头下的文法符号是右结合的
			// 	移动状态x入栈
			TA[i * cols + j] = sx;
		}
		else if((pin > pout) || (pin == pout && w == true)){
			// may be 1. 栈内距离栈顶最近的终结符的优先级 > 栈外读头下的文法符号的优先级
			// may be 2. 优先级相同，但读头下的文法符号是左结合的
			// 	按y号产生式归约
			TA[i * cols + j] = -ry;
		}
	}


	/* private constructor */
	LRPPT::LRPPT()
	{
		_table_action = NULL;
		_table_goto = NULL;
		_rows = 0;
	}


	/* desconstructor */
	LRPPT::~LRPPT()
	{
		if(_table_action != NULL)
			delete []_table_action;
		if(_table_goto != NULL)
			delete []_table_goto;
	}


	/* print the LRPPT */
	void LRPPT::print()const
	{
		int m = _rows;
		int n1 = _symbol_A.size();
		int n2 = _symbol_B.size();

		cout << '\t';
		for(int i = 0; i < n1; i++)
			cout << '\t' << _symbol_A[i];
		cout << "\t|";
		for(int i = 0; i < n2; i++)
			cout << '\t' << _symbol_B[i];
		cout << '\n';

		for(int i = 0; i < m; i++)
		{
			cout << "I[" << i << "] ";
			if(i < 10)
				cout << ' ';
			cout << ": \t";
			for(int j = 0; j < n1; j++){
				int t = _table_action[i * n1 + j];
				if(t == m)
					cout << "Acc";
				else if(t > 0)
					cout << 'S' << t;
				else if(t < 0)
					cout << 'r' << -t;
				else
					cout << t;
				cout << '\t';
			}
			cout << "|\t";
			for(int j = 0; j < n2; j++){
				cout << _table_goto[i * n2 + j] << '\t';
			}
			cout << '\n';
		}
	}


	/* create */
	LRPPT * LRPPT::create()
	{
		// 1. define result
		LRPPT * ppt = new LRPPT();

		// 2. calculate terminal-symbols, non-terminal-symbols
		Grammar::classify(ppt->_symbol_A, ppt->_symbol_B);

		// 3. calculate State0, State1, State2, ...
		vector< set<Production> > U;
		stateRace(U);

		// 4. fill Table-Action, Table-Goto
		int m = U.size();
		int n1 = ppt->_symbol_A.size();
		int n2 = ppt->_symbol_B.size();
		int * TA = new int[m * n1];
		int * TG = new int[m * n2];
		buildPredictTable(U, ppt->_symbol_A, ppt->_symbol_B, TA, TG);

		// 5. set ppt
		ppt->_table_action = TA;
		ppt->_table_goto = TG;
		ppt->_rows = m;

		// 6. return
		return ppt;
	}


	/* 以json格式记录一条结果 */
	void LRPPT::log_res(ostream & out, const string & left, const vector<string> & right)
	{
		// 1. init
		static const char * json = "{\"left\":\"\",\"right\":[]}";
		Document d;
		d.Parse(json);

		// 2. set left
		d["left"].SetString(StringRef(left.c_str()));

		// 3. set right
		Document::AllocatorType & allocator = d.GetAllocator();
		for(size_t i = 0; i < right.size(); i++)
			d["right"].PushBack(StringRef(right[i].c_str()), allocator);

		// 4. output
		StringBuffer buffer;
		Writer<StringBuffer> writer(buffer);
		d.Accept(writer);
		out << buffer.GetString() << '\n';
	}


	/* 以json格式记录一条报错 */
	void LRPPT::log_error(ostream & out, const string & word)
	{
		// 1. init
		static const char * json = "{\"word\":\"\"}";
		Document d;
		d.Parse(json);

		// 2. set word
		d["word"].SetString(StringRef(word.c_str()));

		// 3. output
		StringBuffer buffer;
		Writer<StringBuffer> writer(buffer);
		d.Accept(writer);
		out << buffer.GetString() << '\n';
	}


	/* 对一个token序列的文件做语法检查 */
	void LRPPT::scan(const char * path_input, const char * path_res, const char * path_error)const
	{
		// 1. read tokens from input file
		vector< pair<string, string> > tokens;
		pair<string, string> item;
		string line;

		ifstream in;
		in.open(path_input, ios::in);
		if(in.is_open() == true){
			while(getline(in, line)){
				Document d;
				d.Parse(line.c_str());
				item.first = d["type"].GetString();
				item.second = d["word"].GetString();
				tokens.push_back(item);
			}
			in.close();
		}

		// 2. prepare two output streams
		ofstream out_res(path_res);
		ofstream out_error(path_error);

		// 3. do scan
		scan(tokens, out_res, out_error);

		// 4. close output streams
		out_res.close();
		out_error.close();
	}


	/* 对一段token序列做语法检查 */
	void LRPPT::scan(const vector< pair<string, string> > & tokens, ostream & out_res, ostream & out_error)const
	{
		// wait code...
	}

}
