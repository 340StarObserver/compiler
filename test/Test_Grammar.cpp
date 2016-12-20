/*
Author 		: 	Lv Yang
Created 	: 	19 December 2016
Modified 	: 	20 December 2016
Version 	: 	1.0
*/

/* This file used to test the class 'Production' and 'Grammar' */

#include "../grammar/Grammar.h"
using Seven::Grammar;
using Seven::Production;

#include <iostream>
using std::cout;

int main()
{
	// 1. define conf path
	const char * path = "/home/seven/gitspace/compiler/conf/production.conf";

	// 2. read conf
	Grammar::init(path);

	// 3. print result
	int n = Grammar::Plist.size();
	cout << "the number of productions : " << n << '\n';

	for(int i = 0; i < n; i++){
		Production p = Grammar::Plist[i];

		for(int j = 0; j < p.exp.size(); j++)
			cout << p.exp[j] << '\t';
		cout << '\n';

		for(int j = 0; j < p.isVt.size(); j++)
			cout << p.isVt[j] << '\t';
		cout << '\n';

		cout << "ppos : " << p.ppos << '\n';
		cout << "sstr : " << p.sstr << '\n';
		cout << '\n';
	}

	return 0;
}
