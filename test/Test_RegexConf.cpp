/*
Author 		: 	Lv Yang
Created 	: 	22 November 2016
Modified 	: 	01 December 2016
Version 	: 	1.0
*/

/* This file used to test the class 'RegexType' */

#include "../lexical/RegexConf.h"
using Seven::RegexConf;

#include <iostream>
using std::cout;

int main()
{
	RegexConf::init("/home/seven/gitspace/compiler/conf/regex.conf");

	for(size_t i = 0; i < RegexConf::Items.size(); i++){
		cout << "id       : " << RegexConf::Items[i].id << '\n';
		cout << "priority : " << RegexConf::Items[i].priority << '\n';
		cout << "mean     : " << RegexConf::Items[i].mean << '\n';
		cout << "infix    : " << RegexConf::Items[i].infix << '\n';
		cout << "infixlen : " << RegexConf::Items[i].infix.length() << '\n';
		cout << '\n';
	}
	return 0;
}
