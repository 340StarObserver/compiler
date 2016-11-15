/*
Author 		: 	Lv Yang
Created 	: 	14 November 2016
Modified 	: 	15 November 2016
Version 	: 	1.0
*/

#include "DFA.h"

#include <cstring>
using std::memset;

#include <queue>
using std::queue;

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


	/* judge whether a state-set already exist */
	bool DFA::exist_state(const vector< set<int> > & Clist, const set<int> & C)
	{
		bool w;
		size_t n = Clist.size();
		for(size_t i = 0; i < n; i++){
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
				return true;
		}
		return false;
	}

}
