/*
Author 		: 	Lv Yang
Created 	: 	19 December 2016
Modified 	: 	21 December 2016
Version 	: 	1.0
*/

/* This file used to test the class 'Production' and 'Grammar' */

#include "../grammar/Grammar.h"
using Seven::Grammar;
using Seven::Production;

#include <iostream>
using std::cout;

#include <set>
using std::set;

int main()
{
	// 1. define conf path
	const char * path = "/home/seven/gitspace/compiler/conf/production.conf";

	// 2. read conf
	Grammar::init(path);

	// test Grammar::init
	{
		cout << "< test Grammar::init >\n";

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
	}

	// test Production::operator < in a set
	{
		cout << "\n< test Production::operator < in a set >\n";

		set<Production> S;
		S.insert(Grammar::Plist[0]);
		S.insert(Grammar::Plist[1]);
		S.insert(Grammar::Plist[2]);
		S.insert(Grammar::Plist[3]);
		S.insert(Grammar::Plist[3]);
		S.insert(Grammar::Plist[2]);
		S.insert(Grammar::Plist[1]);
		S.insert(Grammar::Plist[0]);

		cout << "set size : " << S.size() << '\n';
		for(set<Production>::iterator it = S.begin(); it != S.end(); ++it)
		{
			Production p = *it;
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
	}

	// test Production::operator ==
	{
		cout << "\n< test Production::operator == >\n";
		cout << (Grammar::Plist[0] == Grammar::Plist[0]) << '\n';
		cout << (Grammar::Plist[0] == Grammar::Plist[1]) << '\n';
		cout << '\n';
	}

	return 0;
}
