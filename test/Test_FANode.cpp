/*
Author 		: 	Lv Yang
Created 	: 	09 November 2016
Modified 	: 	11 December 2016
Version 	: 	1.0
*/

/* This file used to test the class 'FANode' */

#include "../lexical/FANode.h"
using Seven::FANode;

#include <iostream>
using std::cout;

/* test print a FANode */
void show(FANode & node)
{
	cout<<"this node itself :\n";
	cout<<'\t'<<(void *)&node<<'\t';
	cout<<node.getId()<<'\t';
	cout<<node.getType()<<'\t';
	cout<<node.getMean()<<"\n\n";
	cout<<"next nodes :\n";
	size_t n = node.getEdges()->size();
	for(size_t i = 0; i < n; i++){
		cout<<'\t'<<"edge : "<<node.getEdges()->at(i)<<'\t';
		cout<<(void *)(node.getNexts()->at(i))<<'\t';
		cout<<node.getNexts()->at(i)->getId()<<'\t';
		cout<<node.getNexts()->at(i)->getType()<<'\t';
		cout<<node.getNexts()->at(i)->getMean()<<'\n';
	}
}

int main()
{
	/* create some nodes */
	FANode * p1 = new FANode(1);

	FANode p2(2);
	p2.setType(1);
	p2.setMean("id");

	FANode p3(3);
	p3.setType(2);
	p3.setMean("num");

	FANode p4(4);
	p4.setType(3);
	p4.setMean("str");

	/* link those nodes */
	p1->addNext(int('a'), &p2);
	p1->addNext(int('b'), &p3);
	p1->addNext(FANode::NullEdge, &p4);

	/* test print */
	show(*p1);

	/* delete */
	delete p1;

	return 0;
}
