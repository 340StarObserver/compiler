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
using Seven::GSrule;

#include <iostream>
using std::cout;

#include <set>
using std::set;


void test_1()
{
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

		cout << "\nthe number of GSrules : " << Grammar::VtRules.size() << '\n';
		for(set<GSrule>::iterator it = Grammar::VtRules.begin(); it != Grammar::VtRules.end(); ++it){
			cout << (*it).getSymbol() << '\t';
			cout << (*it).getPriority() << '\t';
			cout << (*it).getCombine() << '\n';
		}
	}
}


void test_2()
{
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
}


void test_3()
{
	// test Production::operator ==
	{
		cout << "\n< test Production::operator == >\n";
		cout << (Grammar::Plist[0] == Grammar::Plist[0]) << '\n';
		cout << (Grammar::Plist[0] == Grammar::Plist[1]) << '\n';
		cout << '\n';
	}
}


void test_4()
{
	vector<string> A, B;

	// test Grammar::classify
	{
		Grammar::classify(A, B);

		cout << "vt     : \t";
		for(int i = 0; i < A.size(); i++)
			cout << A[i] << '\t';
		cout << "\nnum : " << A.size() << '\n';

		cout << "\nnon-vt : \t";
		for(int i = 0; i < B.size(); i++)
			cout << B[i] << '\t';
		cout << "\nnum : " << B.size() << "\n\n";
	}

	// test Grammar::findSymbol
	{
		for(int i = 0; i < A.size(); i++){
			cout << "Find " << A[i] << " in A : " << Grammar::findSymbol(A, A[i]) << '\n';
			cout << "Find " << A[i] << " in B : " << Grammar::findSymbol(B, A[i]) << '\n';
		}
		for(int i = 0; i < B.size(); i++){
			cout << "Find " << B[i] << " in A : " << Grammar::findSymbol(A, B[i]) << '\n';
			cout << "Find " << B[i] << " in B : " << Grammar::findSymbol(B, B[i]) << '\n';
		}
	}
}


int main()
{
	const char * path = "/home/seven/gitspace/compiler/conf/production.conf";
	Grammar::init(path);

	test_1();

	return 0;
}
