/*
Author 		: 	Lv Yang
Created 	: 	22 November 2016
Modified 	: 	29 November 2016
Version 	: 	1.0
*/

/* This file used to test the class 'RegexType' */

#include "../lexical/RegexType.h"
using Seven::RegexType;

#include <iostream>
using std::cout;

int main()
{
	RegexType::init("/home/seven/gitspace/compiler/conf/regex.conf");

	for(int i = 1; i <= 58; i++){
		cout<<"id       : "<<i<<'\n';
		cout<<"priority : "<<RegexType::priority(i)<<'\n';
		cout<<"mean     : "<<RegexType::Means[i]<<'\n';
		cout<<"infix    : "<<RegexType::Infixs[i]<<'\n';
		cout<<'\n';
	}
	return 0;
}
