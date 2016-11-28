/*
Author 		: 	Lv Yang
Created 	: 	14 November 2016
Modified 	: 	23 November 2016
Version 	: 	1.0
*/

/* This file used to test the class 'DFA' */

#include "../lexical/DFA.h"
#include "../lexical/Regex.h"
using Seven::DFA;
using Seven::NFA;
using Seven::Regex;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <iostream>
using std::cout;

/* print some variables of a DFA */
void print_DFA(DFA * dfa)
{
	// 1. get DFA's vts
	int num_vt = dfa->getVtNum();
	int * vts = dfa->getVts();

	// 2. get DFA's state-transfer-table
	vector<int *> * table = dfa->getTable();

	// 3. get DFA's state-end-mark[]
	int * types = dfa->getEndTypes();

	// 4. print DFA, for example :
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

	cout<<"\nend types[] :\n";
	for(int i = 0; i < table->size(); i++)
		cout<<types[i]<<'\t';
	cout<<'\n';
}


/* test DFA::create */
void test_1(const string & infix)
{
	// 1. calculate suffix regex
	string suffix = Regex::transfer(infix);
	cout<<"regex suffix : "<<suffix<<'\n';

	// 2. build a NFA
	int start_id = 1;
	NFA * nfa = NFA::create(suffix, 10, start_id);

	// 3. build a DFA
	DFA * dfa = DFA::create(nfa);

	// 4. print DFA
	print_DFA(dfa);

	// 8. delete
	delete nfa;
	delete dfa;
}


/* test DFA::create by several suffix regex */
void test_2()
{
	// prepare some suffix regexs
	vector<string> regexs;
	regexs.push_back(Regex::transfer("(a|b)*.c"));
	regexs.push_back(Regex::transfer("(b|c)*.a"));

	vector<int> types;
	types.push_back(20);
	types.push_back(23);

	// create a NFA
	int start_id = 1;
	NFA * nfa = NFA::create(regexs, types, start_id);

	// create a DFA
	DFA * dfa = DFA::create(nfa);

	// print DFA
	print_DFA(dfa);

	// delete 
	delete nfa;
	delete dfa;
}


/* test a large DFA */
void test_3()
{
	// 1. build a large NFA
	NFA * nfa = NFA::create("/home/seven/gitspace/compiler/conf/regex.conf");

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
	// test_1(string("a.(b.a.b*.a)*.(a|b).b*"));
	// test_1(string("(a|b)*.a.(a|b).(a|b).(a|b)"));
	// test_1(string("(a.b*.a)*.(a|b).b*"));
	// test_1(string("a.a*.((b.a.b*.a)*.(a|b).b*)*"));
	test_1(string("((b.a*)*.a)*.(a|b)"));

	// test_2();
	// test_3();
	return 0;
}
