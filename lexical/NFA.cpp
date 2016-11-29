/*
Author 		: 	Lv Yang
Created 	: 	09 November 2016
Modified 	: 	22 November 2016
Version 	: 	1.0
*/

#include "NFA.h"
#include "Regex.h"
#include "RegexType.h"

#include <queue>
using std::queue;

#include <stack>
using std::stack;

namespace Seven
{
	/* constructor */
	/*
	build a NFA according to a Vt
	Example :
		vt = int('a'), start_id = 7
		then it will create a NFA like 7------>8, its edge is 'a'
	*/
	NFA::NFA(int vt, int start_id)
	{
		_start = new FANode(start_id);
		_end = new FANode(start_id + 1);
		_start->addNext(vt, _end);
	}


	/* used in deconstructor */
	bool NFA::contains(const vector<FANode *> & pool, FANode * node)
	{
		size_t n = pool.size();
		for(size_t i = 0; i < n; i++){
			if(pool[i] == node)
				return true;
		}
		return false;
	}


	/* deconstructor */
	/*
	it use BFS to traverse each node :
		put the current node into a pool
		// because this diagram may have loops,
		// so it must use a pool to inspect whether a node has already been visited
	*/
	NFA::~NFA()
	{
		// create a work queue
		queue<FANode *> Q;
		if(_start != NULL)
			Q.push(_start);

		// create a node pool
		vector<FANode *> pool;

		// do BFS
		FANode * cur = NULL;
		vector<FANode *> * nexts = NULL;
		size_t n, i;
		while(Q.empty() == false){
			cur = Q.front();
			Q.pop();
			// if haven't deal with this node
			if(contains(pool, cur) == false){
				// put this node into the pool
				pool.push_back(cur);
				// push next nodes into the queue
				nexts = cur->getNexts();
				n = nexts->size();
				for(i = 0; i < n; i++)
					Q.push(nexts->at(i));
			}
		}

		// delete all the nodes which in the pool
		n = pool.size();
		for(i = 0; i < n; i++)
			delete pool[i];
		pool.clear();
	}


	/* get the start node */
	FANode * NFA::getStart()const
	{
		return _start;
	}


	/* get the end node */
	FANode * NFA::getEnd()const
	{
		return _end;
	}


	/* set the start node */
	void NFA::setStart(FANode * node)
	{
		_start = node;
	}


	/* set the end node */
	void NFA::setEnd(FANode * node)
	{
		_end = node;
	}


	/* do closure-change( NFA to NFA* ) on a NFA */
	void NFA::closure(NFA * nfa, int start_id)
	{
		// get the original start node & original end node
		FANode * origin_s = nfa->getStart();
		FANode * origin_e = nfa->getEnd();

		// create a new start node & a new end node
		FANode * s = new FANode(start_id);
		FANode * e = new FANode(start_id + 1);

		// connect
		s->addNext(FANode::NullEdge, origin_s);
		s->addNext(FANode::NullEdge, e);
		origin_e->addNext(FANode::NullEdge, origin_s);
		origin_e->addNext(FANode::NullEdge, e);

		// update the start & end
		nfa->setStart(s);
		nfa->setEnd(e);
	}


	/* union two NFAs by a '|' */
	/*
	Tips :
		it will make the second NFA become empty, that is to say :
		a. its' start node's pointer will become NULL
		b. its' end node's pointer will become NULL
	*/
	void NFA::merge(NFA * left, NFA * right, int start_id)
	{
		// get original start nodes & original end nodes
		FANode * ls = left->getStart();
		FANode * le = left->getEnd();
		FANode * rs = right->getStart();
		FANode * re = right->getEnd();

		// create a new start node & a new end node
		FANode * s = new FANode(start_id);
		FANode * e = new FANode(start_id + 1);

		// connect
		s->addNext(FANode::NullEdge, ls);
		s->addNext(FANode::NullEdge, rs);
		le->addNext(FANode::NullEdge, e);
		re->addNext(FANode::NullEdge, e);

		// update the start & end
		left->setStart(s);
		left->setEnd(e);

		// make the second NFA become empty
		right->setStart(NULL);
		right->setEnd(NULL);
	}


	/* join two NFAs by '.' */
	/*
	Tips :
		it will make the second NFA become empty, that is to say :
		a. its' start node's pointer will become NULL
		b. its' end node's pointer will become NULL
	*/
	void NFA::join(NFA * left, NFA * right)
	{
		// get left's end, right's start, right's end
		FANode * le = left->getEnd();
		FANode * rs = right->getStart();
		FANode * re = right->getEnd();

		// connect
		le->addNext(FANode::NullEdge, rs);

		// update the end
		left->setEnd(re);

		// make the second NFA become empty
		right->setStart(NULL);
		right->setEnd(NULL);
	}


	/* create a NFA by given a suffix regex */
	NFA * NFA::create(const string & suffixRegex, int type, int & start_id)
	{
		// create a work stack
		stack<NFA *> S;

		// prepare two temp pointer
		NFA * nfa_1 = NULL;
		NFA * nfa_2 = NULL;

		// scan the suffix regex
		char ch;
		size_t n = suffixRegex.length();
		for(size_t i = 0; i < n; i++){
			ch = suffixRegex[i];
			if(ch == '*'){
				nfa_1 = S.top();
				S.pop();
				NFA::closure(nfa_1, start_id);
				S.push(nfa_1);
				start_id += 2;
			}
			else if(ch == '|'){
				nfa_1 = S.top();
				S.pop();
				nfa_2 = S.top();
				S.pop();
				NFA::merge(nfa_2, nfa_1, start_id);
				S.push(nfa_2);
				start_id += 2;
				delete nfa_1;
			}
			else if(ch == '.'){
				nfa_1 = S.top();
				S.pop();
				nfa_2 = S.top();
				S.pop();
				NFA::join(nfa_2, nfa_1);
				S.push(nfa_2);
				delete nfa_1;
			}
			else{
				nfa_1 = new NFA(int(ch), start_id);
				S.push(nfa_1);
				start_id += 2;
			}
		}

		// the top item in stack is the final NFA
		// set the end node's type
		NFA * res = S.top();
		res->getEnd()->setType(type);
		return res;
	}


	/* create a big NFA by given all the suffix regex */
	NFA * NFA::create(const vector<string> & suffixs, const vector<int> & types, int & start_id)
	{
		// if there is no suffix regex
		size_t n = suffixs.size();
		if(n == 0)
			return NULL;

		// create the first NFA
		NFA * nfa = create(suffixs[0], types[0], start_id);

		// merge the 'nfa' with other NFAs
		NFA * tmp = NULL;
		for(size_t i = 1; i < n; i++){
			tmp = create(suffixs[i], types[i], start_id);
			NFA::merge(nfa, tmp, start_id);
			delete tmp;
			start_id += 2;
		}

		// return the final NFA
		return nfa;
	}


	/* create a big NFA from conf file */
	NFA * NFA::create(const char * path)
	{
		// 1. read most regexs(which can be be builded automically) from a conf file
		RegexType::init(path);

		// 2. create a NFA with *  *=  |  ||
		/*
			because in a normal suffix regex, it includes '*', '.', '|'
			that is to say, it will cause collusion
			so, I have to create it manually
		*/
		NFA * nfa = NULL, * tmp1 = NULL, * tmp2 = NULL;

		nfa = new NFA(int('*'), 1);
		nfa->getEnd()->setType(11);

		tmp1 = new NFA(int('*'), 3);
		tmp2 = new NFA(int('='), 5);
		join(tmp1, tmp2);
		tmp1->getEnd()->setType(15);
		delete tmp2;
		merge(nfa, tmp1, 7);
		delete tmp1;

		tmp1 = new NFA('|', 9);
		tmp1->getEnd()->setType(18);
		merge(nfa, tmp1, 11);
		delete tmp1;

		tmp1 = new NFA('|', 13);
		tmp2 = new NFA('|', 15);
		join(tmp1, tmp2);
		tmp1->getEnd()->setType(21);
		delete tmp2;
		merge(nfa, tmp1, 17);
		delete tmp1;
		
		// 3. create a NFA with the rest regexs
		/*
			those rest regexs can be created automically
		*/
		vector<string> regexs;
		vector<int> types;

		int n = RegexType::Infixs.size();
		for(int i = 1; i < n; i++){
			if(RegexType::priority(i) != 0){
				regexs.push_back(Regex::transfer(RegexType::Infixs[i]));
				types.push_back(i);
			}
		}

		regexs.push_back("(");
		regexs.push_back(")");
		types.push_back(6);
		types.push_back(7);

		RegexType::Infixs[6] = string("(");
		RegexType::Infixs[7] = string(")");
		RegexType::Infixs[11] = string("*");
		RegexType::Infixs[15] = string("*.=");
		RegexType::Infixs[18] = string("|");
		RegexType::Infixs[21] = string("|.|");

		RegexType::Means[6] = string("LBrace");
		RegexType::Means[7] = string("RBrace");
		RegexType::Means[11] = string("multi");
		RegexType::Means[15] = string("MULTI");
		RegexType::Means[18] = string("BinOr");
		RegexType::Means[21] = string("LogicOr");

		RegexType::Prioritys[6] = 1;
		RegexType::Prioritys[7] = 1;
		RegexType::Prioritys[11] = 1;
		RegexType::Prioritys[15] = 5;
		RegexType::Prioritys[18] = 1;
		RegexType::Prioritys[21] = 5;

		int id = 19;
		tmp1 = create(regexs, types, id);
		regexs.clear();
		types.clear();

		// 4. merge the manually-NFA and the automically-NFA
		merge(nfa, tmp1, id);
		delete tmp1;

		// 5. return the final large NFA
		return nfa;
	}

}
