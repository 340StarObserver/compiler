/*
Author 		: 	Lv Yang
Created 	: 	09 November 2016
Modified 	: 	22 November 2016
Version 	: 	1.0
*/

/* This file used to test the class 'NFA' */

#include "../lexical/NFA.h"
using Seven::NFA;
using Seven::FANode;

#include "../lexical/Regex.h"
using Seven::Regex;

#include "../lexical/RegexType.h"
using Seven::RegexType;

#include <queue>
using std::queue;

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <iostream>
using std::cout;

/* print a FANode */
void show(FANode & node)
{
	cout<<"this node itself :\n";
	cout<<'\t'<<(void *)&node<<'\t'<<node.getId()<<'\t'<<node.getType()<<'\n';
	cout<<"next nodes :\n";
	size_t n = node.getEdges()->size();
	for(size_t i = 0; i < n; i++){
		cout<<'\t'<<(void *)(node.getNexts()->at(i))<<'\t';
		cout<<"id : "<<node.getNexts()->at(i)->getId()<<"\t\t";
		cout<<"type : "<<node.getNexts()->at(i)->getType()<<'\t';
		cout<<"edge : "<<node.getEdges()->at(i)<<'\n';
	}
	cout<<'\n';
}


/* traverse a NFA */
bool contains(const vector<FANode *> & pool, FANode * node){
	size_t n = pool.size();
	for(size_t i = 0; i < n; i++){
		if(pool[i] == node)
			return true;
	}
	return false;
}
void traverse(const NFA & nfa){
	cout<<"print start node :\n";
	if(nfa.getStart() != NULL)
		show(*(nfa.getStart()));
	else
		cout<<"null\n";

	cout<<"print end node :\n";
	if(nfa.getEnd() != NULL)
		show(*(nfa.getEnd()));
	else
		cout<<"null\n";

	cout<<"print all nodes :\n";
	queue<FANode *> Q;
	if(nfa.getStart() != NULL)
		Q.push(nfa.getStart());
	vector<FANode *> pool;
	FANode * cur = NULL;
	vector<FANode *> * nexts = NULL;
	size_t n, i;
	while(Q.empty() == false){
		cur = Q.front();
		Q.pop();
		if(contains(pool, cur) == false){
			pool.push_back(cur);
			show(*cur);
			nexts = cur->getNexts();
			n = nexts->size();
			for(i = 0; i < n; i++)
				Q.push(nexts->at(i));
		}
	}
	cout<<'\n';
}


/* test build a NFA by given a suffix regex */
void test_1()
{
	// build a NFA
	string suffix("ab.c|*de|*.");
	int start_id = 1;
	NFA * nfa = NFA::create(suffix, 10, start_id);

	// print NFA
	traverse(*nfa);
	cout<<"\nnow the start_id : "<<start_id<<'\n';

	// delete
	delete nfa;
}


/* test build a big NFA by given several suffix regexs */
void test_2()
{
	// prepare some suffix regexs
	vector<string> regexs;
	regexs.push_back(Regex::transfer("(a|b)*.c"));
	regexs.push_back(Regex::transfer("a.b**.c"));
	regexs.push_back(Regex::transfer("d|e|f"));

	vector<int> types;
	types.push_back(10);
	types.push_back(20);
	types.push_back(30);

	// create a big NFA
	int start_id = 1;
	NFA * nfa = NFA::create(regexs, types, start_id);

	// print NFA
	cout<<"start_id : "<<start_id<<'\n';
	traverse(*nfa);

	// delete
	delete nfa;
}


/* test build a big NFA by default regexs */
void test_3()
{
	NFA * nfa = NFA::create("/home/seven/gitspace/compiler/conf/regex.conf");
	traverse(*nfa);
	delete nfa;

	for(int i = 1; i <= 58; i++){
		cout<<"id       : "<<i<<'\n';
		cout<<"priority : "<<RegexType::priority(i)<<'\n';
		cout<<"mean     : "<<RegexType::Means[i]<<'\n';
		cout<<"infix    : "<<RegexType::Infixs[i]<<'\n';
		cout<<'\n';
	}
}


int main()
{
	test_1();
	// test_2();
	// test_3();
	return 0;
}
