/*
Author 		: 	Lv Yang
Created 	: 	22 November 2016
Modified 	: 	22 November 2016
Version 	: 	1.0
*/

/* This file used to test the class 'RegexType' */

#include "../lexical/RegexType.h"
using Seven::RegexType;

#include <iostream>
using std::cout;

int main()
{
	for(int i = 1; i <= 58; i++){
		cout<<"type : "<<i<<'\t';
		cout<<"priority : "<<RegexType::priority(i)<<'\t';
		cout<<RegexType::represent(i)<<'\n';
	}
	return 0;
}
