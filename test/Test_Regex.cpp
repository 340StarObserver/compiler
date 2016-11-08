/*
Author 		: 	Lv Yang
Created 	: 	08 November 2016
Modified 	: 	08 November 2016
Version 	: 	1.0
*/

/* This file used to test the class 'Regex' */

#include "../lexical/Regex.h"
using Seven::Regex;

#include <iostream>
using std::cout;

#include <string>
using std::string;

int main()
{
	string infix("(_|a|b|c|d|e).(0|1|2|3|4|_|a|b|c|d|e)*");
	string suffix = Regex::transfer(infix);

	cout<<"infix  : "<<infix<<'\n';
	cout<<"suffix : "<<suffix<<'\n';

	return 0;
}
