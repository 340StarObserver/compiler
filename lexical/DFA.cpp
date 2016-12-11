/*
Author 		: 	Lv Yang
Created 	: 	14 November 2016
Modified 	: 	01 December 2016
Version 	: 	1.0
*/

#include "DFA.h"
#include "RegexConf.h"

#include <cstring>
using std::memset;

#include <queue>
using std::queue;

#include <algorithm>
using std::set_intersection;
using std::inserter;

namespace Seven
{
	/* extract all nodes from a NFA */
	FANode ** DFA::extract_nodes(const NFA * nfa, int & num)
	{
		FANode * start = nfa->getStart();
		FANode * end = nfa->getEnd();

		// if NFA is empty
		if(start == NULL || end == NULL){
			num = 0;
			return NULL;
		}

		// the number of nodes = id of the end node
		num = end->getId();

		// prepare space for all nodes
		FANode ** nodes = new FANode*[num + 1];
		memset(nodes, 0, sizeof(FANode *)*(num + 1));

		// prepare some variables
		FANode * cur = NULL;
		vector<FANode *> * nexts = NULL;
		size_t n, i;
		int id;

		// do BFS
		queue<FANode *> Q;
		Q.push(start);
		while(Q.empty() == false){
			// pop a item
			cur = Q.front();
			Q.pop();

			// if haven't visit this node
			id = cur->getId();
			if(nodes[id] == NULL){
				// save to nodes[]
				nodes[id] = cur;

				// push next nodes into the queue
				nexts = cur->getNexts();
				n = nexts->size();
				for(i = 0; i < n; i++)
					Q.push(nexts->at(i));
			}
		}

		// return all nodes
		return nodes;
	}


	/* extract all vt(terminal symbols) */
	int * DFA::extract_vts(const NFA * nfa, int & num)
	{
		FANode * start = nfa->getStart();
		FANode * end = nfa->getEnd();

		// if NFA is empty
		if(start == NULL || end == NULL){
			num = 0;
			return NULL;
		}

		// create a set to save vts
		set<int> S;

		// prepare some variables
		FANode * cur = NULL;
		vector<FANode *> * nexts = NULL;
		vector<int> * edges = NULL;
		size_t n, i;
		int id;

		// prepare a vistied[] to mark
		bool * visited = new bool[end->getId()];
		memset(visited, 0, sizeof(bool)*end->getId());

		// do BFS
		queue<FANode *> Q;
		Q.push(start);
		while(Q.empty() == false){
			// pop a item
			cur = Q.front();
			Q.pop();

			// if haven't visit this node
			id = cur->getId();
			if(visited[id - 1] == false){
				// mark this node
				visited[id - 1] = true;

				// push next nodes into the queue
				nexts = cur->getNexts();
				edges = cur->getEdges();
				n = nexts->size();
				for(i = 0; i < n; i++){
					Q.push(nexts->at(i));
					if(edges->at(i) != FANode::NullEdge)
						S.insert(edges->at(i));
				}
			}
		}

		// prepare space for the vt array
		num = S.size();
		int * vts = new int[num];

		// fill the vt array
		int k = 0;
		for(set<int>::iterator it = S.begin(); it != S.end(); ++it)
			vts[k++] = *it;

		// return result
		S.clear();
		delete []visited;
		return vts;
	}


	/* get ε-closure of a set C */
	set<int> DFA::closure(FANode ** nodes, const set<int> & C)
	{
		// prepare an empty set
		set<int> S;

		// prepare a queue, and put all nodes which in C into the queue
		queue<FANode *> Q;
		for(set<int>::iterator it = C.begin(); it != C.end(); ++it)
			Q.push(nodes[*it]);

		// prepare some variables
		FANode * cur = NULL;
		vector<FANode *> * nexts = NULL;
		vector<int> * edges = NULL;
		size_t n, i;
		int id;

		// do BFS
		while(Q.empty() == false){
			// pop a item
			cur = Q.front();
			Q.pop();

			// if haven't visit this node
			id = cur->getId();
			if(S.find(id) == S.end()){
				// add this node into S
				S.insert(id);

				// push next nodes with ε-edge into queue
				nexts = cur->getNexts();
				edges = cur->getEdges();
				n = nexts->size();
				for(i = 0; i < n; i++){
					if(edges->at(i) == FANode::NullEdge)
						Q.push(nexts->at(i));
				}
			}
		}
		return S;
	}


	/* goto(C, X) */
	set<int> DFA::goTo(FANode ** nodes, const set<int> & C, int vt)
	{
		// prepare an empty set
		set<int> S;

		// prepare some variables
		FANode * cur = NULL;
		vector<FANode *> * nexts = NULL;
		vector<int> * edges = NULL;
		size_t n, i;

		// put a's next nodes with vt-edge ( a ∈ C )
		for(set<int>::iterator it = C.begin(); it != C.end(); ++it){
			cur = nodes[*it];
			nexts = cur->getNexts();
			edges = cur->getEdges();

			n = nexts->size();
			for(i = 0; i < n; i++){
				if(edges->at(i) == vt)
					S.insert(nexts->at(i)->getId());
			}
		}
		return S;
	}


	/* judge whether a state-set already exist, if exist return the index, else -1 */
	int DFA::find_state(const vector< set<int> > & Clist, const set<int> & C)
	{
		bool w;
		int n = Clist.size();
		for(int i = 0; i < n; i++){
			// compare Clist[i] and C
			w = true;
			if(Clist[i].size() != C.size())
				w = false;
			else{
				for(set<int>::iterator it = C.begin(); it != C.end(); ++it){
					if(Clist[i].find(*it) == Clist[i].end()){
						w = false;
						break;
					}
				}
			}
			if(w == true)
				return i;
		}
		return -1;
	}


	/* private constructor */
	DFA::DFA()
	{
		_vtNum = 0;
		_vts = NULL;
		_types = NULL;
		_means = NULL;
	}


	/* private set vts */
	void DFA::setVts(int * vts, int vtNum)
	{
		_vts = vts;
		_vtNum = vtNum;
	}


	/* private set types */
	void DFA::setEndTypes(int * types)
	{
		_types = types;
	}


	/* get state transfer table */
	vector<int *> * DFA::getTable()
	{
		return &_table;
	}


	/* get the number of vt */
	int DFA::getVtNum()const
	{
		return _vtNum;
	}


	/* get the vts */
	int * DFA::getVts()const
	{
		return _vts;
	}


	/* get type[] which represent each state's type */
	int * DFA::getEndTypes()const
	{
		return _types;
	}


	/* get mean[] which represent each state's end-mean */
	string * DFA::getEndMeans()const
	{
		return _means;
	}


	/* deconstructor */
	DFA::~DFA()
	{
		// delete _types
		if(_types != NULL)
			delete []_types;

		// delete _means
		if(_means != NULL)
			delete []_means;

		// delete _vts
		if(_vts != NULL)
			delete []_vts;

		// delete _table
		size_t n = _table.size();
		for(size_t i = 0; i < n; i++){
			if(_table[i] != NULL)
				delete []_table[i];
		}
		_table.clear();
	}


	/* create a DFA from a NFA */
	DFA * DFA::create(const NFA * nfa)
	{
		// 1. create a result DFA
		DFA * dfa = new DFA();

		// 2. get all nodes of NFA
		int num_node = 0;
		FANode ** nodes = extract_nodes(nfa, num_node);

		// 3. get all vts of NFA
		int num_vt = 0;
		int * vts = extract_vts(nfa, num_vt);
		dfa->setVts(vts, num_vt);

		// 4. prepare some objects
		vector< set<int> > Clist;
		queue< set<int> > Q;
		set<int> cur, tmp;
		int i = 1, p, k, j;

		// 5. calculate ε-closure(NFA's start node), and put it to Clist and Q
		cur.insert(nfa->getStart()->getId());
		tmp = closure(nodes, cur);
		dfa->getTable()->push_back(new int[num_vt]);
		Clist.push_back(tmp);
		Q.push(tmp);

		// 6. do BFS
		while(Q.empty() == false){
			// pop a item
			cur = Q.front();
			Q.pop();
			p = find_state(Clist, cur);

			// consider each vt
			for(k = 0; k < num_vt; k++){
				// calculate ε-closure(goto(cur,vt))
				tmp = closure(nodes, goTo(nodes, cur, vts[k]));

				if(tmp.size() == 0){
					// if tmp is ∅
					dfa->getTable()->at(p)[k] = -1;
				}else if((j = find_state(Clist, tmp)) != -1){
					// if tmp is in Clist
					dfa->getTable()->at(p)[k] = j;
				}else{
					// tmp is a new state-set
					dfa->getTable()->at(p)[k] = i;
					dfa->getTable()->push_back(new int[num_vt]);
					Clist.push_back(tmp);
					Q.push(tmp);
					i++;
				}
			}
		}

		// 7. then calculate types[]

		/* prepare space for types[] */
		int dfa_state_num = dfa->getTable()->size();
		int * types = new int[dfa_state_num];
		string * means = new string[dfa_state_num];

		/* prepare set A, A is all small NFA's end node's id */
		set<int> A;
		for(i = 1; i <= num_node; i++){
			if(nodes[i]->getType() != 0)
				A.insert(i);
		}

		/* for each Clist[i] */
		for(i = 0; i < dfa_state_num; i++){
			/* T = Clist[i] ∩ A */
			set<int> T;
			set_intersection(
				Clist[i].begin(), Clist[i].end(), A.begin(), A.end(), 
				inserter(T, T.begin())
			);

			if(T.size() == 0){
				/* if T is ∅, then types[i] = 0 */
				types[i] = 0;
			}else{
				/* types[i] = T中优先级最高的那种类型 */
				int best_priority = 0, best_type, tmp_priority, tmp_type;
				for(set<int>::iterator it = T.begin(); it != T.end(); ++it){
					tmp_type = nodes[*it]->getType();
					tmp_priority = RegexConf::Items[tmp_type - 1].priority;
					if(best_priority < tmp_priority){
						best_type = tmp_type;
						best_priority = tmp_priority;
					}
				}
				types[i] = best_type;
				means[i] = RegexConf::Items[best_type - 1].mean;
			}
		}
		dfa->setEndTypes(types);
		dfa->_means = means;

		// 8. delete
		delete []nodes;
		Clist.clear();

		// 9. return
		return dfa;
	}

}
