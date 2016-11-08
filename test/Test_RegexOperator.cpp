/*
Author 		: 	Lv Yang
Created 	: 	08 November 2016
Modified 	: 	08 November 2016
Version 	: 	1.0
*/

/* This file used to test the class 'RegexOperator' */

#include "../lexical/RegexOperator.h"
using Seven::RegexOperator;

#include <iostream>
using std::cout;

int main()
{
	// test : bool RegexOperator::support(char op);
	cout<<RegexOperator::support('(')<<'\n';
	cout<<RegexOperator::support(')')<<'\n';
	cout<<RegexOperator::support('*')<<'\n';
	cout<<RegexOperator::support('|')<<'\n';
	cout<<RegexOperator::support('.')<<'\n';
	cout<<RegexOperator::support('&')<<'\n';
	cout<<'\n';

	// test : int RegexOperator::feature(char op);
	cout<<RegexOperator::feature('(')<<'\n';
	cout<<RegexOperator::feature(')')<<'\n';
	cout<<RegexOperator::feature('*')<<'\n';
	cout<<RegexOperator::feature('|')<<'\n';
	cout<<RegexOperator::feature('.')<<'\n';
	cout<<RegexOperator::feature('&')<<'\n';
	cout<<'\n';

	// test : int RegexOperator::innerPriority(char op);
	cout<<RegexOperator::innerPriority('(')<<'\n';
	cout<<RegexOperator::innerPriority(')')<<'\n';
	cout<<RegexOperator::innerPriority('*')<<'\n';
	cout<<RegexOperator::innerPriority('|')<<'\n';
	cout<<RegexOperator::innerPriority('.')<<'\n';
	cout<<RegexOperator::innerPriority('&')<<'\n';
	cout<<'\n';

	// test : int RegexOperator::outerPriority(char op);
	cout<<RegexOperator::outerPriority('(')<<'\n';
	cout<<RegexOperator::outerPriority(')')<<'\n';
	cout<<RegexOperator::outerPriority('*')<<'\n';
	cout<<RegexOperator::outerPriority('|')<<'\n';
	cout<<RegexOperator::outerPriority('.')<<'\n';
	cout<<RegexOperator::outerPriority('&')<<'\n';

	return 0;
}
