/*
Author 		: 	Lv Yang
Created 	: 	18 November 2016
Modified 	: 	01 December 2016
Version 	: 	1.0
*/

#include "ODFA.h"
#include "RegexConf.h"

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios;

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


	/*
	把状态总集T, 拆分为 非终结态集A 和 终结态集B
	参数的解释 :
		T 		T[i]==0  <==> state i is not a end node; T[i] != 0  <==> state i is a end node
		n 		the length of array T
		A 		to save 非终结态集A
		B 		to save 终结态集B
	*/
	void ODFA::init_split(const int * T, int n, set<int> & A, set<int> & B)
	{
		A.clear();
		B.clear();
		for(int i = 0; i < n; i++){
			if(T[i] == 0)
				A.insert(i);
			else
				B.insert(i);
		}
	}


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
	bool ODFA::split(const vector<int *> & table, int vt_num, vector< set<int> > & U, int index)
	{
		// 准备邻接状态表
		vector<int> next;

		// prepare some temp variables
		set<int>::iterator it;
		int e_next, n_next, j, first;
		bool w;

		// 对第i个终结符做分析，看U[index]在该终结符的作用下，是否需要进一步拆分
		for(int i = 0; i < vt_num; i++){
			for(it = U[index].begin(); it != U[index].end(); ++it){
				e_next = table[*it][i];
				e_next = find(U, e_next);
				next.push_back(e_next);
			}

			// 判断next中的元素是否都一样
			n_next = next.size();
			w = true;
			for(j = 1; j < n_next; j++){
				if(next[j] != next[0]){
					w = false;
					break;
				}
			}

			if(w == true){
				// 清空邻接状态表，以进行下一个终结符的分析
				next.clear();
			}else{
				// 以first为参照，把 U[index] 分成对应的后继是first的，不是first的两个集合A1,A2
				first = next[0];
				set<int> A1, A2;
				for(it = U[index].begin(); it != U[index].end(); ++it){
					e_next = table[*it][i];
					e_next = find(U, e_next);
					if(e_next == first)
						A1.insert(*it);
					else
						A2.insert(*it);
				}

				// 从U中移除U[index], 把A1,A2添加到U的尾部
				U.erase(U.begin() + index);
				U.push_back(A1);
				U.push_back(A2);
				return true;
			}
		}

		// 对于所有的终结符，U[index]都不需要进行拆分
		return false;
	}


	/*
	把一个DFA的所有状态划分成若干个等价类
	参数的解释 :
		dfa 		is the input DFA
		U 		is the result of 等价类划分
	*/
	void ODFA::calc_divisions(DFA * dfa, vector< set<int> > & U)
	{
		// 1. calculate 非终结态集A 和 终结态集B
		set<int> A, B;
		vector<int *> * table = dfa->getTable();
		init_split(dfa->getEndTypes(), table->size(), A, B);

		// 2. 创建初始划分，一开始仅仅包含 非终结态集合A & 终结态集合B
		U.clear();
		U.push_back(A);
		U.push_back(B);

		// 3. ori_size 是每一轮迭代前的划分中的等价类的数目
		//     cur_size 是每一轮迭代后的划分中的等价类的数目
		int ori_size;
		int cur_size = U.size();
		int i;

		// 4. do split
		//     当某次迭代完成后，发现划分中的等价类的数目没有发生变化
		//     则说明所有的等价类都满足弱等价了，即可以结束了
		do{
			ori_size = cur_size;
			i = 0;
			while(i < U.size()){
				if(split(*table, dfa->getVtNum(), U, i) == false)
					i++;
				// 发生拆分的时候，下标指针是不变的
				// 因为删去了当前这个等价类U[i]，并在U末尾添加了两个新的从U[i]分出来的等价类
			}
			// 这一轮迭代后的，新的U的规模
			cur_size = U.size();
		}while(cur_size != ori_size);
	}


	/*
	根据划分好的等价类，构建新的状态转换表
	参数的解释 :
		dfa 		the input DFA
		U 		the result of 等价类划分, you can get it by ODFA::calc_divisions
	返回值解释 :
		m行n列的矩阵的一维数组形式table[m*n]
		m 是ODFA的状态数
		n  是终结符的总数
		table[i*n+j]表示ODFA中状态i，在j号终结符的作用下，到达的后继状态的编号
	*/
	int * ODFA::calc_table(DFA * dfa, const vector< set<int> > & U)
	{
		// 1. m 是优化过后的新的DFA的状态数
		//     n 是终结符的总数
		int m = U.size();
		int n = dfa->getVtNum();

		// 2. 新的DFA的状态转化表 new_table[m][n]
		int * new_table = new int[m * n];

		// 3. prepare some temp variables
		int i, j, represent, next;

		// 4. fill new_table[m][n]
		vector<int *> * table = dfa->getTable();
		for(i = 0; i < m; i++){
			for(j = 0; j < n; j++){
				// 选取每个等价类里的第零个元素作为代表吧
				represent = *(U[i].begin());

				// 状态represent在j号终结符下的后继状态
				// 是属于哪一个等价类，则那个等价类的下标，就是优化DFA情况下的后继
				next = table->at(represent)[j];
				next = find(U, next);
				new_table[i * n + j] = next;
			}
		}

		// 5. return
		return new_table;
	}


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
	int * ODFA::calc_types(DFA * dfa, const vector< set<int> > & U)
	{
		// 1. num 是优化后的DFA的状态数
		int num = U.size();

		// 2. 旧的DFA的每个结点的终结情况
		int * old_types = dfa->getEndTypes();

		// 3. 新的DFA的每个结点的终结情况
		int * new_types = new int[num];

		// 4. prepare some temp variables
		int tmp_state, tmp_type, tmp_priority, best_priority;
		set<int>::iterator it;

		// 5. fill new_types[]
		for(int i = 0; i < num; i++){
			new_types[i] = 0;
			best_priority = 0;

			for(it = U[i].begin(); it != U[i].end(); ++it){
				tmp_state = *it;
				tmp_type = old_types[tmp_state];
				tmp_priority = RegexConf::Items[tmp_type - 1].priority;

				if(best_priority < tmp_priority){
					new_types[i] = tmp_type;
					best_priority = tmp_priority;
				}
			}
		}

		// 6. return
		return new_types;
	}


	/* private constructor */
	ODFA::ODFA()
	{
		_vtNum = 0;
		_sNum = 0;
		_entrance = 0;
		_vts = NULL;
		_tables = NULL;
		_types = NULL;
	}


	/* deconstructor */
	ODFA::~ODFA()
	{
		if(_vts != NULL)
			delete []_vts;
		if(_tables != NULL)
			delete []_tables;
		if(_types != NULL)
			delete []_types;
	}


	/* get the number of vt */
	int ODFA::getVtNum()const
	{
		return _vtNum;
	}


	/* get the number of state */
	int ODFA::getStateNum()const
	{
		return _sNum;
	}


	/* get the entrance state */
	int ODFA::getEntranceState()const
	{
		return _entrance;
	}


	/* get the list of vts */
	int * ODFA::getVts()const
	{
		return _vts;
	}


	/* get the state-transfer-table */
	int * ODFA::getTables()const
	{
		return _tables;
	}


	/* get states' end-situation */
	int * ODFA::getEndTypes()const
	{
		return _types;
	}


	/* create a ODFA by given a DFA */
	ODFA * ODFA::create(DFA * dfa)
	{
		// invalid input
		if(dfa == NULL)
			return NULL;

		// 1. get a copy of the vts[]
		int it_vtNum = dfa->getVtNum();
		int * dfa_vts = dfa->getVts();
		int * it_vts = new int[it_vtNum];
		for(int i = 0; i < it_vtNum; i++)
			it_vts[i] = dfa_vts[i];

		// 2. calculate the state-transfer-table
		vector< set<int> > U;
		calc_divisions(dfa, U);
		int it_sNum = U.size();
		int * it_tables = calc_table(dfa, U);

		// 3. calculate the states' end-situation
		int * it_types = calc_types(dfa, U);

		// 4. calculate the new entrance state
		int entrance;
		for(int i = 0; i < it_sNum; i++){
			if(U[i].find(0) != U[i].end()){
				entrance = i;
				break;
			}
		}

		// 5. create a ODFA
		ODFA * res = new ODFA();
		res->_vtNum = it_vtNum;
		res->_sNum = it_sNum;
		res->_entrance = entrance;
		res->_vts = it_vts;
		res->_tables = it_tables;
		res->_types = it_types;

		// 6. return
		return res;
	}


	/* save this ODFA to a file */
	void ODFA::save(const char * path)const
	{
		// open file
		ofstream out(path);

		// write vtNum, sNum, entrance
		out << _vtNum << '\t' << _sNum << '\t' << _entrance << '\n';

		// write vts[]
		for(int i = 0; i < _vtNum; i++)
			out << _vts[i] << '\t';
		out << '\n';

		// write tables[]
		for(int i = 0; i < _sNum; i++){
			for(int j = 0; j < _vtNum; j++)
				out << _tables[i * _vtNum + j] << '\t';
			out << '\n';
		}

		// write types[]
		for(int i = 0; i < _sNum; i++)
			out << _types[i] << '\t';
		out << '\n';

		// close file
		out.close();
	}


	/* load a ODFA from a file */
	ODFA * ODFA::load(const char * path)
	{
		// prepare some variables
		int vtNum, sNum, entrance, tmp;

		// open file
		ifstream in;
		in.open(path, ios::in);
		if(in.is_open() == false)
			return NULL;

		// read vtNum, sNum, entrance
		in >> vtNum >> sNum >> entrance;

		// read vts[]
		int * vts = new int[vtNum];
		for(int i = 0; i < vtNum; i++){
			in >> tmp;
			vts[i] = tmp;
		}

		// read tables[]
		int * tables = new int[sNum * vtNum];
		for(int i = 0; i < sNum; i++){
			for(int j = 0; j < vtNum; j++){
				in >> tmp;
				tables[i * vtNum + j] = tmp;
			}
		}

		// read types[]
		int * types = new int[sNum];
		for(int i = 0; i < sNum; i++){
			in >> tmp;
			types[i] = tmp;
		}

		// close file
		in.close();

		// create a ODFA
		ODFA * res = new ODFA();
		res->_vtNum = vtNum;
		res->_sNum = sNum;
		res->_entrance = entrance;
		res->_vts = vts;
		res->_tables = tables;
		res->_types = types;

		// return
		return res;
	}

}
