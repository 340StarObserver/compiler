/*
Author 		: 	Lv Yang
Created 	: 	14 November 2016
Modified 	: 	14 November 2016
Version 	: 	1.0
*/

/* This file used to test the class 'DFA' */

#include "../lexical/DFA.h"
using Seven::DFA;
using Seven::NFA;
using Seven::FANode;

#include <string>
using std::string;

#include <iostream>
using std::cout;

/* print a FANode */
void show(FANode & node)
{
	cout<<"this node itself :\n";
	cout<<'\t'<<(void *)&node<<'\t'<<node.getId()<<'\t'<<node.isTerminate()<<'\n';
	cout<<"next nodes :\n";
	size_t n = node.getEdges()->size();
	for(size_t i = 0; i < n; i++){
		cout<<'\t'<<(void *)(node.getNexts()->at(i))<<'\t';
		cout<<node.getNexts()->at(i)->getId()<<'\t';
		cout<<node.getNexts()->at(i)->isTerminate()<<'\t';
		cout<<node.getEdges()->at(i)<<'\n';
	}
	cout<<'\n';
}


/* test DFA::extract_nodes when it is public */
void test_1()
{
	// build a NFA
	string suffix("ab.c|*de|*.");
	int start_id = 1;
	NFA * nfa = NFA::create(suffix, start_id);

	// get all nodes
	int num = 0;
	FANode ** nodes = DFA::extract_nodes(nfa, num);

	// print all nodes
	for(int i = 1; i <= num; i++)
		show(*(nodes[i]));

	// delete
	delete nfa;
	delete []nodes;
}


/* test DFA::extract_vts when it is public */
void test_2()
{
	// build a NFA
	string suffix("ab|c|d|**ae|.f.f.f.");
	int start_id = 1;
	NFA * nfa = NFA::create(suffix, start_id);

	// get all vts
	int num = 0;
	int * vts = DFA::extract_vts(nfa, num);

	// print all vts
	for(int i = 0; i < num; i++)
		cout<<vts[i]<<'\t';
	cout<<'\n';

	// delete
	delete nfa;
	delete []vts;
}


int main()
{
	// test_1();
	test_2();
	return 0;
}
