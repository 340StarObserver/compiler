/*
Author 		: 	Lv Yang
Created 	: 	14 November 2016
Modified 	: 	17 November 2016
Version 	: 	1.0
*/

/* This file used to test the class 'DFA' */

#include "../lexical/DFA.h"
#include "../lexical/Regex.h"
using Seven::DFA;
using Seven::NFA;
using Seven::FANode;
using Seven::Regex;

#include <string>
using std::string;

#include <set>
using std::set;

#include <vector>
using std::vector;

#include <iostream>
using std::cout;

/* print a FANode */
// void show(FANode & node)
// {
// 	cout<<"this node itself :\n";
// 	cout<<'\t'<<(void *)&node<<'\t'<<node.getId()<<'\t'<<node.isTerminate()<<'\n';
// 	cout<<"next nodes :\n";
// 	size_t n = node.getEdges()->size();
// 	for(size_t i = 0; i < n; i++){
// 		cout<<'\t'<<(void *)(node.getNexts()->at(i))<<'\t';
// 		cout<<node.getNexts()->at(i)->getId()<<'\t';
// 		cout<<node.getNexts()->at(i)->isTerminate()<<'\t';
// 		cout<<node.getEdges()->at(i)<<'\n';
// 	}
// 	cout<<'\n';
// }


/* test DFA::extract_nodes when it is public */
// void test_1()
// {
// 	// build a NFA
// 	string suffix("ab.c|*de|*.");
// 	int start_id = 1;
// 	NFA * nfa = NFA::create(suffix, start_id);

// 	// get all nodes
// 	int num = 0;
// 	FANode ** nodes = DFA::extract_nodes(nfa, num);

// 	// print all nodes
// 	for(int i = 1; i <= num; i++)
// 		show(*(nodes[i]));

// 	// delete
// 	delete nfa;
// 	delete []nodes;
// }


/* test DFA::extract_vts when it is public */
// void test_2()
// {
// 	// build a NFA
// 	string suffix("ab|c|d|**ae|.f.f.f.");
// 	int start_id = 1;
// 	NFA * nfa = NFA::create(suffix, start_id);

// 	// get all vts
// 	int num = 0;
// 	int * vts = DFA::extract_vts(nfa, num);

// 	// print all vts
// 	for(int i = 0; i < num; i++)
// 		cout<<vts[i]<<'\t';
// 	cout<<'\n';

// 	// delete
// 	delete nfa;
// 	delete []vts;
// }


/* test DFA::closure when it is public */
// void test_3()
// {
// 	// build a NFA
// 	string suffix = Regex::transfer("(a|b)*.a.(a|b).(a|b).(a|b)");
// 	int start_id = 1;
// 	NFA * nfa = NFA::create(suffix, start_id);

// 	// get all nodes
// 	int num = 0;
// 	FANode ** nodes = DFA::extract_nodes(nfa, num);

// 	// calculate some closures
// 	int a1[] = {7};
// 	set<int> s1(a1, a1 + 1);
// 	set<int> res1 = DFA::closure(nodes, s1);
// 	for(set<int>::iterator it = res1.begin(); it != res1.end(); ++it)
// 		cout<<*it<<'\t';
// 	cout<<"\n\n";

// 	int a2[] = {2,10,12,18};
// 	set<int> s2(a2, a2 + 4);
// 	set<int> res2 = DFA::closure(nodes, s2);
// 	for(set<int>::iterator it = res2.begin(); it != res2.end(); ++it)
// 		cout<<*it<<'\t';
// 	cout<<"\n\n";

// 	int a3[] = {4,14,26};
// 	set<int> s3(a3, a3 + 3);
// 	set<int> res3 = DFA::closure(nodes, s3);
// 	for(set<int>::iterator it = res3.begin(); it != res3.end(); ++it)
// 		cout<<*it<<'\t';
// 	cout<<"\n\n";

// 	// delete
// 	delete nfa;
// 	delete []nodes;
// }


/* test DFA::goTo when it is public */
// void test_4()
// {
// 	// build a NFA
// 	string suffix = Regex::transfer("(a|b)*.a.(a|b).(a|b).(a|b)");
// 	int start_id = 1;
// 	NFA * nfa = NFA::create(suffix, start_id);

// 	// get all nodes
// 	int num = 0;
// 	FANode ** nodes = DFA::extract_nodes(nfa, num);

// 	// calculate some goTo
// 	int a1[] = {1,2,3,5,6,8,9,10,11,12,13,15,16,17,18,19,21,22,23,25,27};
// 	set<int> s1(a1, a1 + 21);
// 	set<int> res1 = DFA::goTo(nodes, s1, int('a'));
// 	set<int> res2 = DFA::goTo(nodes, s1, int('b'));

// 	int a2[] = {1,3,4,5,6,8,9,20,22,23,25,27};
// 	set<int> s2(a2, a2 + 12);
// 	set<int> res3 = DFA::goTo(nodes, s2, int('a'));
// 	set<int> res4 = DFA::goTo(nodes, s2, int('b'));

// 	// print these goTo result
// 	for(set<int>::iterator it = res1.begin(); it != res1.end(); ++it)
// 		cout<<*it<<'\t';
// 	cout<<"\n\n";
// 	for(set<int>::iterator it = res2.begin(); it != res2.end(); ++it)
// 		cout<<*it<<'\t';
// 	cout<<"\n\n";
// 	for(set<int>::iterator it = res3.begin(); it != res3.end(); ++it)
// 		cout<<*it<<'\t';
// 	cout<<"\n\n";
// 	for(set<int>::iterator it = res4.begin(); it != res4.end(); ++it)
// 		cout<<*it<<'\t';
// 	cout<<"\n\n";

// 	// delete
// 	delete nfa;
// 	delete []nodes;
// }


/* test Sj=ε-closure(goto(Si,vt)) */
// void test_5()
// {
// 	// build a NFA
// 	string suffix = Regex::transfer("(a|b)*.a.(a|b).(a|b).(a|b)");
// 	int start_id = 1;
// 	NFA * nfa = NFA::create(suffix, start_id);

// 	// get all nodes
// 	int num = 0;
// 	FANode ** nodes = DFA::extract_nodes(nfa, num);

// 	// calculate some ε-closure(goto(Si,vt))
// 	int a1[] = {1,2,3,5,6,8,9,10,11,12,13,15,16,17,18,19,21,22,23,25,27};
// 	set<int> s1(a1, a1 + 21);
// 	set<int> res1 = DFA::closure(nodes, DFA::goTo(nodes, s1, int('a')));
// 	set<int> res2 = DFA::closure(nodes, DFA::goTo(nodes, s1, int('b')));

// 	int a2[] = {1,3,4,5,6,8,9,20,22,23,25,27};
// 	set<int> s2(a2, a2 + 12);
// 	set<int> res3 = DFA::closure(nodes, DFA::goTo(nodes, s2, int('a')));
// 	set<int> res4 = DFA::closure(nodes, DFA::goTo(nodes, s2, int('b')));

// 	// print results
// 	for(set<int>::iterator it = res1.begin(); it != res1.end(); ++it)
// 		cout<<*it<<'\t';
// 	cout<<"\n\n";
// 	for(set<int>::iterator it = res2.begin(); it != res2.end(); ++it)
// 		cout<<*it<<'\t';
// 	cout<<"\n\n";
// 	for(set<int>::iterator it = res3.begin(); it != res3.end(); ++it)
// 		cout<<*it<<'\t';
// 	cout<<"\n\n";
// 	for(set<int>::iterator it = res4.begin(); it != res4.end(); ++it)
// 		cout<<*it<<'\t';
// 	cout<<"\n\n";

// 	// delete
// 	delete nfa;
// 	delete []nodes;
// }


/* test DFA::find_state when it is public */
// void test_6()
// {
// 	// prepare some arrays
// 	int a1[] = {1,2,3,4,5};
// 	int a2[] = {2,6,8};
// 	int a3[] = {4,7,9,0,13};
// 	int a4[] = {1,2,9,0,10,11,32};
// 	int a5[] = {0,9,13,7,4};
// 	int a6[] = {4,8,9,0,13};
// 	int a7[] = {2,8};

// 	// prepare some sets
// 	set<int> s1(a1, a1 + 5);
// 	set<int> s2(a2, a2 + 3);
// 	set<int> s3(a3, a3 + 5);
// 	set<int> s4(a4, a4 + 7);
// 	set<int> s5(a5, a5 + 5);
// 	set<int> s6(a6, a6 + 6);
// 	set<int> s7(a7, a7 + 2);

// 	// create a set-list
// 	vector< set<int> > V;
// 	V.push_back(s1);
// 	V.push_back(s2);
// 	V.push_back(s3);
// 	V.push_back(s4);

// 	// test DFA::exist_state
// 	cout<<DFA::find_state(V, s5)<<'\n';
// 	cout<<DFA::find_state(V, s6)<<'\n';
// 	cout<<DFA::find_state(V, s7)<<'\n';
// }


/* test DFA::isEnd when it is public */
// void test_7()
// {
// 	// create a state-set
// 	int a[] = {1,2,10,7,11,34,28};
// 	set<int> s(a, a + 7);

// 	// do some test
// 	cout<<DFA::isEnd(s, 7);
// 	cout<<DFA::isEnd(s, 34);
// 	cout<<DFA::isEnd(s, 25);
// }


/* test DFA::create */
void test_8(const string & infix)
{
	// 1. calculate suffix regex
	string suffix = Regex::transfer(infix);
	cout<<"regex suffix : "<<suffix<<'\n';

	// 2. build a NFA
	int start_id = 1;
	NFA * nfa = NFA::create(suffix, start_id);

	// 3. build a DFA
	DFA * dfa = DFA::create(nfa);

	// 4. get DFA's vts
	int num_vt = dfa->getVtNum();
	int * vts = dfa->getVts();

	// 5. get DFA's state-transfer-table
	vector<int *> * table = dfa->getTable();

	// 6. get DFA's state-end-mark[]
	bool * mark = dfa->getEndMark();

	// 7. print DFA, for example :
	/*
		the number of vt : 2

		state transfer table :
			a 	b
		S0 	S1 	S2
		S1 	S1 	S2
		S2 	∅ 	S2

		end mark[] :
		0 	1 	1
	*/
	cout<<"the number of vt : "<<num_vt<<'\n';

	cout<<"\nstate transfer table :\n\t";
	for(int i = 0; i < num_vt; i++)
		cout<<char(vts[i])<<'\t';
	cout<<'\n';

	for(int i = 0; i < table->size(); i++){
		cout<<"I"<<i<<'\t';
		for(int j = 0; j < num_vt; j++)
			cout<<table->at(i)[j]<<'\t';
		cout<<'\n';
	}

	cout<<"\nend mark[] :\n";
	for(int i = 0; i < table->size(); i++)
		cout<<mark[i]<<'\t';
	cout<<'\n';

	// 8. delete
	delete nfa;
	delete dfa;
}


/* test a large DFA */
void test_9()
{
	// 1. build a large NFA
	NFA * nfa = NFA::create();

	// 2. build a large DFA
	DFA * dfa = DFA::create(nfa);

	// 3. get DFA's vts
	int num_vt = dfa->getVtNum();
	int * vts = dfa->getVts();

	// 4. get DFA's state-transfer-table
	vector<int *> * table = dfa->getTable();

	// 5. print some value
	cout<<"the number of vts    : "<<num_vt<<'\n';
	cout<<"the number of state : "<<table->size()<<'\n';

	// 6. delete
	delete nfa;
	delete dfa;
}


int main()
{
	// test_1();
	// test_2();
	// test_3();
	// test_4();
	// test_5();
	// test_6();
	// test_7();

	// test_8(string("a.(b.a.b*.a)*.(a|b).b*"));
	// test_8(string("(a|b)*.a.(a|b).(a|b).(a|b)"));
	test_8(string("(a.b*.a)*.(a|b).b*"));
	// test_8(string("a.a*.((b.a.b*.a)*.(a|b).b*)*"));

	// test_9();

	return 0;
}
