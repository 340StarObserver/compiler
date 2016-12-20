/*
Author 		: 	Lv Yang
Created 	: 	20 December 2016
Modified 	: 	20 December 2016
Version 	: 	1.0
*/

/* This file used to test the class 'LRPPT' */

#include "../grammar/Grammar.h"
using Seven::Grammar;

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


int main()
{
	Grammar::init("/home/seven/gitspace/compiler/conf/production.conf");
	test_2();
	return 0;
}
