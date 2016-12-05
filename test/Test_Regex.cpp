/*
Author 		: 	Lv Yang
Created 	: 	08 November 2016
Modified 	: 	12 November 2016
Version 	: 	1.0
*/

/* This file used to test the class 'Regex' */

#include "../lexical/Regex.h"
#include "../lexical/RegexConf.h"
using Seven::Regex;
using Seven::RegexConf;

#include <iostream>
using std::cout;

#include <string>
using std::string;

#include <vector>
using std::vector;

// 测试把配置文件定义的中缀正规表达式转化为后缀
void test_1()
{
	const char * path = "/home/seven/gitspace/compiler/conf/regex.conf";
	RegexConf::init(path);

	for(size_t i = 0; i < RegexConf::Items.size(); i++){
		cout << "infix  : " << RegexConf::Items[i].infix << '\n';
		cout << "suffix : " << Regex::transfer(RegexConf::Items[i].infix) << '\n';
		cout << '\n';
	}
}

// 着重测试各运算符之间的优先级是否在转化过程中被正确使用
void test_2()
{
	string str;

	str = "a.a*.((b.a.b*.a)*.(a|b).b*)*";
	cout<<"infix  : "<<str<<'\n';
	cout<<"suffix : "<<Regex::transfer(str)<<'\n'<<'\n';

	str = "a|b|c";
	cout<<"infix  : "<<str<<'\n';
	cout<<"suffix : "<<Regex::transfer(str)<<'\n'<<'\n';

	str = "a.b.c";
	cout<<"infix  : "<<str<<'\n';
	cout<<"suffix : "<<Regex::transfer(str)<<'\n'<<'\n';

	str = "(a|b)**";
	cout<<"infix  : "<<str<<'\n';
	cout<<"suffix : "<<Regex::transfer(str)<<'\n'<<'\n';

	str = "a|b**";
	cout<<"infix  : "<<str<<'\n';
	cout<<"suffix : "<<Regex::transfer(str)<<'\n'<<'\n';

	str = "a|b.c";
	cout<<"infix  : "<<str<<'\n';
	cout<<"suffix : "<<Regex::transfer(str)<<'\n'<<'\n';

	str = "(a|b).c";
	cout<<"infix  : "<<str<<'\n';
	cout<<"suffix : "<<Regex::transfer(str)<<'\n'<<'\n';

	str = "a.b|c";
	cout<<"infix  : "<<str<<'\n';
	cout<<"suffix : "<<Regex::transfer(str)<<'\n'<<'\n';

	str = "a.(b|c)";
	cout<<"infix  : "<<str<<'\n';
	cout<<"suffix : "<<Regex::transfer(str)<<'\n'<<'\n';
}

int main()
{
	test_1();
	test_2();
	return 0;
}
