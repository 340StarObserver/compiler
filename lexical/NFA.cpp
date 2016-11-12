/*
Author 		: 	Lv Yang
Created 	: 	09 November 2016
Modified 	: 	12 November 2016
Version 	: 	1.0
*/

#include "NFA.h"
#include "Regex.h"

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
	bool NFA::contains(const vector<FANode *> & pool, FANode * node)const
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
	NFA * NFA::create(const string & suffixRegex, int & start_id)
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
		return S.top();
	}

	/* create a big NFA by given all the suffix regex */
	NFA * NFA::create(const vector<string> & suffixs, int & start_id)
	{
		// if there is no suffix regex
		size_t n = suffixs.size();
		if(n == 0)
			return NULL;

		// create the first NFA
		NFA * nfa = create(suffixs[0], start_id);

		// merge the 'nfa' with other NFAs
		NFA * tmp = NULL;
		for(size_t i = 1; i < n; i++){
			tmp = create(suffixs[i], start_id);
			NFA::merge(nfa, tmp, start_id);
			delete tmp;
			start_id += 2;
		}

		// return the final NFA
		return nfa;
	}

	/* create a big NFA by some default regex */
	NFA * NFA::create()
	{
		// prepare some infix regexs
		const static string infix[] = {
			"(_|A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z|a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z).(0|1|2|3|4|5|6|7|8|9|_|A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z|a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z)*",
			"(\t| |\n).(\t| |\n)*",
			"0|(1|2|3|4|5|6|7|8|9).(0|1|2|3|4|5|6|7|8|9)*",
			"#. .i.n.c.l.u.d.e", "#. .i.f.n.d.e.f", "#. .d.e.f.i.n.e", "#. .e.n.d.i.f",
			"m.a.i.n", "n.a.m.e.s.p.a.c.e", "u.s.i.n.g",
			"c.l.a.s.s", "s.t.r.u.c.t", "u.n.i.o.n", "e.n.u.m",
			"p.r.i.v.a.t.e", "p.u.b.l.i.c", "s.t.a.t.i.c", "c.o.n.s.t",
			"v.o.i.d", "b.o.o.l", "c.h.a.r", "i.n.t", "l.o.n.g", "f.l.o.a.t", "d.o.u.b.l.e",
			":.:", "~",
			"r.e.t.u.r.n", "i.f", "e.l.s.e", "d.o", "w.h.i.l.e", "f.o.r"
		};

		// prepare some suffix regexs
		const static string suffix[] = {
			"{", "}", "(", ")", ";",
			"+", "-", "/", "+=.", "-=.", "/=.",
			"&", "^", "&&.", "!",
			"=", ">", "<", "==.", ">=.", "<=."
		};

		// 1. create a NFA with *  *=  |  ||
		/*
			because in a normal suffix regex, it includes '*', '.', '|'
			that is to say, it will cause collusion
			so, I have to create it manually
		*/
		NFA * nfa = NULL, * tmp1 = NULL, * tmp2 = NULL;
		nfa = new NFA(int('*'), 1);
		tmp1 = new NFA(int('*'), 3);
		tmp2 = new NFA(int('='), 5);
		join(tmp1, tmp2);
		delete tmp2;
		merge(nfa, tmp1, 7);
		delete tmp1;
		tmp1 = new NFA('|', 9);
		merge(nfa, tmp1, 11);
		delete tmp1;
		tmp1 = new NFA('|', 13);
		tmp2 = new NFA('|', 15);
		join(tmp1, tmp2);
		delete tmp2;
		merge(nfa, tmp1, 17);
		delete tmp1;
		
		// 2. create a NFA with the rest regexs
		/*
			those rest regexs can be created automically
		*/
		vector<string> all_suffix;
		for(int i = 0; i < 33; i++)
			all_suffix.push_back(Regex::transfer(infix[i]));
		for(int i = 0; i < 21; i++)
			all_suffix.push_back(suffix[i]);
		int id = 19;
		tmp1 = create(all_suffix, id);
		all_suffix.clear();

		// 3. merge the manually-NFA and the automically-NFA
		merge(nfa, tmp1, id);
		delete tmp1;

		// 4. return the final large NFA
		return nfa;
	}

}
