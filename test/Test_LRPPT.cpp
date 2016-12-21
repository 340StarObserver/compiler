/*
Author 		: 	Lv Yang
Created 	: 	20 December 2016
Modified 	: 	21 December 2016
Version 	: 	1.0
*/

/* This file used to test the class 'LRPPT' */

#include "../grammar/Grammar.h"
using Seven::Grammar;
using Seven::Production;

#include "../grammar/LRPPT.h"
using Seven::LRPPT;

#include <iostream>
using std::cout;


/* test LRPPT::First when it is public */
void test_1(const string S[], const bool M[], int num)
{
	// 1. prepare parameters
	vector<string> SS;
	vector<bool> MM;
	for(int i = 0; i < num; i++){
		SS.push_back(S[i]);
		MM.push_back(M[i]);
	}

	// 2. calculate First
	set<string> res = LRPPT::First(SS, MM, 0);

	// 3. print
	cout << "number of vt : " << res.size() << '\n';
	for(set<string>::iterator it = res.begin(); it != res.end(); ++it)
		cout << *it << '\n';
	cout << '\n';
}


/* prepare some test case for test_1 */
void test_2()
{
	// do test 1
	{
		/*
		make sure "conf/production.conf" is :
			E -> T E'
			0 0 0

			E' -> + T E'
			0 1 0 0

			E' ->
			0 1

			T -> F T'
			0 0 0

			T' -> * F T'
			0 1 0 0

			T' ->
			0 1

			F -> ( E )
			0 1 0 1

			F -> id
			0 1
		*/
		// First(T' E) = {ε, *, (, id}
		string s1[] = {"T'", "E"};
		bool m1[] = {false, false};
		test_1(s1, m1, 2);

		// First(T' id F) = {ε, *, id}
		string s2[] = {"T'", "id", "F"};
		bool m2[] = {false, true, false};
		test_1(s2, m2, 3);

		// First(T' E' F) = {ε, *, +, (, id}
		string s3[] = {"T'", "E'", "F"};
		bool m3[] = {false, false, false};
		test_1(s3, m3, 3);

		// First(T E' F) = {(, id}
		string s4[] = {"T", "E'", "F"};
		bool m4[] = {false, false, false};
		test_1(s4, m4, 3);

		// First(* E' F) = {*}
		string s5[] = {"*", "E'", "F"};
		bool m5[] = {true, false, false};
		test_1(s5, m5, 3);

		// First(E' T' T' E' id) = {ε, *, +, id}
		string s6[] = {"E'", "T'", "T'", "E'", "id"};
		bool m6[] = {false, false, false, false, true};
		test_1(s6, m6, 5);
	}
}


/* print a Production-set */
void print_production_set(int id, const set<Production> & pset)
{
	cout << "I[" << id << "] size : " << pset.size() << "\n{\n";
	for(set<Production>::iterator it = pset.begin(); it != pset.end(); ++it){
		cout << "\n\t";
		Production cur = *it;
		for(int j = 0; j < cur.exp.size(); j++)
			cout << cur.exp[j] << '\t';
		cout << "\n\t";
		for(int j = 0; j < cur.isVt.size(); j++)
			cout << cur.isVt[j] << '\t';
		cout << "\n\t";
		cout << "ppos : " << cur.ppos << "\n\t";;
		cout << "sstr : " << cur.sstr << "\n\n";
	}
	cout << "}\n";
}


/* test LRPPT::closure when it is public */
void test_3()
{
	/*
	make sure "conf/production.conf" is :
		S' -> S
		0 0

		S -> if S else S
		0 1 0 1 0

		S -> if S
		0 1 0

		S -> S ; S
		0 0 1 0

		S -> a
		0 1
	*/

	// 1. prepare { [ S' -> ·S, $ ] }
	Production p = Grammar::Plist[0];
	p.ppos = 1;
	p.sstr = "$";
	set<Production> i0;
	i0.insert(p);

	// 2. calculate i0
	i0 = LRPPT::closure(i0);
	print_production_set(0, i0);

	// 3. prepare :
	// 	[ S -> if · S else S, else ]
	// 	[ S -> if · S else S, $ ]
	// 	[ S -> if · S else S, ; ]
	// 	[ S -> if · S, else ]
	// 	[ S -> if · S, $ ]
	// 	[ S -> if · S, ; ]
	set<Production> i6;
	Production p1 = Grammar::Plist[1];
	p1.ppos = 2;
	{
		p1.sstr = "else";
		i6.insert(p1);
		p1.sstr = "$";
		i6.insert(p1);
		p1.sstr = ";";
		i6.insert(p1);
	}
	Production p2 = Grammar::Plist[2];
	p2.ppos = 2;
	{
		p2.sstr = "else";
		i6.insert(p2);
		p2.sstr = "$";
		i6.insert(p2);
		p2.sstr = ";";
		i6.insert(p2);
	}

	// 4. calculate i6
	i6 = LRPPT::closure(i6);
	print_production_set(6, i6);
}


int main()
{
	Grammar::init("/home/seven/gitspace/compiler/conf/production.conf");
	// test_2();
	test_3();
	return 0;
}
