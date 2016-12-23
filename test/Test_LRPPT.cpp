/*
Author 		: 	Lv Yang
Created 	: 	20 December 2016
Modified 	: 	21 December 2016
Version 	: 	1.0
*/

/* This file used to test the class 'LRPPT' */

#include "../grammar/LRPPT.h"
using Seven::Grammar;
using Seven::LRPPT;

/* test build LRPPT */
void test_1()
{
	LRPPT * ppt = LRPPT::create();
	ppt->print();
	delete ppt;
}

int main()
{
	Grammar::init("/home/seven/gitspace/compiler/conf/production.conf");
	test_1();
	return 0;
}
