/*
Author 		: 	Lv Yang
Created 	: 	09 November 2016
Modified 	: 	11 November 2016
Version 	: 	1.0
*/

/* This file used to test the class 'NFA' */

#include "../lexical/NFA.h"
using Seven::NFA;
using Seven::FANode;

#include "../lexical/Regex.h"
using Seven::Regex;

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


/* test whether the nodes in a NFA( ab.c|*de|*. ) are right */
void test_1()
{
	// manually build a NFA
	NFA * nfa = new NFA(int('a'), 1);
	FANode * origin_start = nfa->getStart();
	FANode * origin_end = nfa->getEnd();

	FANode * p3 = new FANode(3);
	FANode * p4 = new FANode(4);
	FANode * p5 = new FANode(5);
	FANode * p6 = new FANode(6);
	FANode * p7 = new FANode(7);
	FANode * p8 = new FANode(8);
	FANode * p9 = new FANode(9);
	FANode * p10 = new FANode(10);
	FANode * p11 = new FANode(11);
	FANode * p12 = new FANode(12);
	FANode * p13 = new FANode(13);
	FANode * p14 = new FANode(14);
	FANode * p15 = new FANode(15);
	FANode * p16 = new FANode(16);
	FANode * p17 = new FANode(17);
	FANode * p18 = new FANode(18);

	p7->addNext(FANode::NullEdge, origin_start);
	origin_end->addNext(FANode::NullEdge, p3);
	p3->addNext(int('b'), p4);
	p4->addNext(FANode::NullEdge, p8);

	p7->addNext(FANode::NullEdge, p5);
	p5->addNext(int('c'), p6);
	p6->addNext(FANode::NullEdge, p8);

	p9->addNext(FANode::NullEdge, p7);
	p9->addNext(FANode::NullEdge, p10);
	p8->addNext(FANode::NullEdge, p7);
	p8->addNext(FANode::NullEdge, p10);

	p10->addNext(FANode::NullEdge, p17);
	p17->addNext(FANode::NullEdge, p15);
	p17->addNext(FANode::NullEdge, p18);
	p15->addNext(FANode::NullEdge, p11);
	p15->addNext(FANode::NullEdge, p13);
	p11->addNext(int('d'), p12);
	p13->addNext(int('e'), p14);
	p12->addNext(FANode::NullEdge, p16);
	p14->addNext(FANode::NullEdge, p16);
	p16->addNext(FANode::NullEdge, p15);
	p16->addNext(FANode::NullEdge, p18);

	nfa->setStart(p9);
	nfa->setEnd(p18);
	p18->setTerminate(true);

	// test print
	traverse(*nfa);

	// delete
	delete nfa;
}


/* test do closure on a NFA */
void test_2()
{
	// create a NFA
	NFA * nfa = new NFA(int('a'), 1);
	// do two closure
	NFA::closure(nfa, 3);
	NFA::closure(nfa, 5);
	// test print
	traverse(*nfa);
	// delete
	delete nfa;
}


/* test union NFAs by '|' */
void test_3()
{
	// create NFA1
	NFA * nfa_1 = new NFA(int('a'), 1);
	NFA::closure(nfa_1, 3);

	// create NFA2
	NFA * nfa_2 = new NFA(int('b'), 5);
	NFA::closure(nfa_2, 7);

	// union NFA1 & NFA2
	NFA::merge(nfa_1, nfa_2, 9);

	// create NFA3
	NFA * nfa_3 = new NFA(int('c'), 11);

	// union (NFA1|NFA2) & NFA3
	NFA::merge(nfa_1, nfa_3, 13);

	// test print NFA1
	cout<<"---- NFA1 ----\n";
	traverse(*nfa_1);

	// test print NFA2
	cout<<"---- NFA2 ----\n";
	traverse(*nfa_2);

	// test print NFA3
	cout<<"---- NFA3 ----\n";
	traverse(*nfa_3);

	// delete
	delete nfa_1;
	delete nfa_2;
	delete nfa_3;
}


/* test join NFAs by '.' */
void test_4()
{
	// create NFA1, NFA2
	NFA * nfa_1 = new NFA(int('a'), 1);
	NFA * nfa_2 = new NFA(int('b'), 3);
	// do NFA1|NFA2
	NFA::merge(nfa_1, nfa_2, 5);
	// do (NFA1|NFA2)*
	NFA::closure(nfa_1, 7);

	// create NFA3
	NFA * nfa_3 = new NFA(int('c'), 9);
	// do NFA3*
	NFA::closure(nfa_3, 11);

	// create NFA4
	NFA * nfa_4 = new NFA(int('d'), 13);

	// do (NFA1|NFA2)*.NFA3*.NFA4
	NFA::join(nfa_1, nfa_3);
	NFA::join(nfa_1, nfa_4);

	// test print
	cout<<"---- NFA1 ----\n";
	traverse(*nfa_1);
	cout<<"---- NFA2 ----\n";
	traverse(*nfa_2);
	cout<<"---- NFA3 ----\n";
	traverse(*nfa_3);
	cout<<"---- NFA4 ----\n";
	traverse(*nfa_4);

	// delete
	delete nfa_1;
	delete nfa_2;
	delete nfa_3;
	delete nfa_4;
}


/* test build a NFA by given a suffix regex */
void test_5()
{
	// build a NFA
	string suffix("ab.c|*de|*.");
	int start_id = 1;
	NFA * nfa = NFA::create(suffix, start_id);

	// print NFA
	traverse(*nfa);
	cout<<"\nnow the start_id : "<<start_id<<'\n';

	// delete
	delete nfa;
}


/* test build a big NFA by given several suffix regexs */
void test_6()
{
	// prepare some suffix regexs
	vector<string> regexs;
	regexs.push_back(Regex::transfer("(a|b)*.c"));
	regexs.push_back(Regex::transfer("a*"));
	regexs.push_back(Regex::transfer("d|e"));

	// create a big NFA
	NFA * nfa = NFA::create(regexs);

	// print NFA
	traverse(*nfa);

	// delete
	delete nfa;
}


int main()
{
	// test_1();
	// test_2();
	// test_3();
	// test_4();
	// test_5();
	test_6();
	return 0;
}
