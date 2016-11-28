/*
Author 		: 	Lv Yang
Created 	: 	18 November 2016
Modified 	: 	28 November 2016
Version 	: 	1.0
*/

/* This file used to test the class 'ODFA' */

#include "../lexical/Regex.h"
#include "../lexical/ODFA.h"
using Seven::NFA;
using Seven::Regex;
using Seven::DFA;
using Seven::ODFA;

#include <iostream>
using std::cout;


/* print a ODFA */
void print(const ODFA & odfa)
{
	int m = odfa.getStateNum();
	int n = odfa.getVtNum();
	int * vts = odfa.getVts();
	int * tables = odfa.getTables();
	int * types = odfa.getEndTypes();

	cout<<"入口状态 : "<<odfa.getEntranceState();

	cout<<"\nODFA的状态转换表\n\t";
	for(int i = 0; i < n; i++)
		cout<<char(vts[i])<<'\t';
	for(int i = 0; i < m; i++)
	{
		cout<<"\nI"<<i<<"   : ";
		for(int j = 0; j < n; j++)
			cout<<tables[i * n + j]<<'\t';
	}
	
	cout<<"\n终结结点-对应识别正则代号 对照表\n";
	for(int i = 0; i < m; i++)
		cout<<types[i]<<'\t';
	cout<<'\n';
}


/* test transfer a DFA(only one regex) to a ODFA */
void test_1(const string & infix)
{
	// 1. calculate suffix regex
	string suffix = Regex::transfer(infix);

	// 2. build a NFA
	int start_id = 1;
	NFA * nfa = NFA::create(suffix, 10, start_id);

	// 3. build a DFA
	DFA * dfa = DFA::create(nfa);

	// 4. build a ODFA
	ODFA * odfa = ODFA::create(dfa);

	// 5. test print this ODFA
	print(*odfa);

	// delete
	delete nfa;
	delete dfa;
	delete odfa;
}


/* test transfer a DFA(more than one regex) to a ODFA */
void test_2()
{
	// 1. prepare some suffix regexs
	vector<string> regexs;
	regexs.push_back(Regex::transfer("(a|b)*.c"));
	regexs.push_back(Regex::transfer("a.b**.c"));
	vector<int> types;
	types.push_back(20);
	types.push_back(23);

	// 2. create a NFA
	int start_id = 1;
	NFA * nfa = NFA::create(regexs, types, start_id);

	// 3. create a DFA
	DFA * dfa = DFA::create(nfa);

	// 4. build a ODFA
	ODFA * odfa = ODFA::create(dfa);

	// 5. test print this ODFA
	print(*odfa);

	// delete
	delete nfa;
	delete dfa;
	delete odfa;
}


/* test save a ODFA and load */
void test_3()
{
	// 1. calculate suffix regex
	string suffix = Regex::transfer(string("((b.a*)*.a)*.(a|b)"));

	// 2. build a NFA
	int start_id = 1;
	NFA * nfa = NFA::create(suffix, 10, start_id);

	// 3. build a DFA
	DFA * dfa = DFA::create(nfa);

	// 4. build a ODFA
	ODFA * odfa = ODFA::create(dfa);
	cout<<"before :\n";
	print(*odfa);

	// 5. save odfa to file
	odfa->save("odfa.dat");

	// 6. load from file
	ODFA * odfa_2 = ODFA::load("odfa.dat");
	cout<<"\nafter :\n";
	print(*odfa_2);

	// delete
	delete nfa;
	delete dfa;
	delete odfa;
	delete odfa_2;
}


int main()
{
	// test_1(string("((b.a*)*.a)*.(a|b)"));
	// test_1(string("(a.b*.a)*.(a|b).b*"));
	// test_1(string("a.(b.a.b*.a)*.(a|b).b*"));
	// test_1(string("a.a*.((b.a.b*.a)*.(a|b).b*)*"));
	// test_2();
	test_3();
	return 0;
}
