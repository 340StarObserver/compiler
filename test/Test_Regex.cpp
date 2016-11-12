/*
Author 		: 	Lv Yang
Created 	: 	08 November 2016
Modified 	: 	12 November 2016
Version 	: 	1.0
*/

/* This file used to test the class 'Regex' */

#include "../lexical/Regex.h"
using Seven::Regex;

#include <iostream>
using std::cout;

#include <string>
using std::string;

#include <vector>
using std::vector;

void test_1()
{
	vector<string> all_suffixs;

	// id
	all_suffixs.push_back(
		Regex::transfer(
			"(_|A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z|a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z).(0|1|2|3|4|5|6|7|8|9|_|A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z|a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z)*"
		)
	);

	// whitespace
	all_suffixs.push_back(Regex::transfer("(\t| |\n).(\t| |\n)*"));

	// integer
	all_suffixs.push_back(Regex::transfer("0|(1|2|3|4|5|6|7|8|9).(0|1|2|3|4|5|6|7|8|9)*"));

	// {    }    (    )    ;
	all_suffixs.push_back("{");
	all_suffixs.push_back("}");
	all_suffixs.push_back("(");
	all_suffixs.push_back(")");
	all_suffixs.push_back(";");

	// operators( not includes : *  *=  |  || )
	all_suffixs.push_back(Regex::transfer("+"));
	all_suffixs.push_back(Regex::transfer("-"));
	all_suffixs.push_back(Regex::transfer("/"));
	all_suffixs.push_back(Regex::transfer("+.="));
	all_suffixs.push_back(Regex::transfer("-.="));
	all_suffixs.push_back(Regex::transfer("/.="));
	all_suffixs.push_back(Regex::transfer("&"));
	all_suffixs.push_back(Regex::transfer("^"));
	all_suffixs.push_back(Regex::transfer("&.&"));
	all_suffixs.push_back(Regex::transfer("!"));
	all_suffixs.push_back(Regex::transfer("="));
	all_suffixs.push_back(Regex::transfer(">"));
	all_suffixs.push_back(Regex::transfer("<"));
	all_suffixs.push_back(Regex::transfer(">.="));
	all_suffixs.push_back(Regex::transfer("<.="));
	all_suffixs.push_back(Regex::transfer("=.="));

	// key words
	all_suffixs.push_back(Regex::transfer("#. .i.n.c.l.u.d.e"));
	all_suffixs.push_back(Regex::transfer("#. .i.f.n.d.e.f"));
	all_suffixs.push_back(Regex::transfer("#. .d.e.f.i.n.e"));
	all_suffixs.push_back(Regex::transfer("#. .e.n.d.i.f"));
	all_suffixs.push_back(Regex::transfer("m.a.i.n"));
	all_suffixs.push_back(Regex::transfer("n.a.m.e.s.p.a.c.e"));
	all_suffixs.push_back(Regex::transfer("u.s.i.n.g"));
	all_suffixs.push_back(Regex::transfer("c.l.a.s.s"));
	all_suffixs.push_back(Regex::transfer("s.t.r.u.c.t"));
	all_suffixs.push_back(Regex::transfer("u.n.i.o.n"));
	all_suffixs.push_back(Regex::transfer("e.n.u.m"));
	all_suffixs.push_back(Regex::transfer("p.r.i.v.a.t.e"));
	all_suffixs.push_back(Regex::transfer("p.u.b.l.i.c"));
	all_suffixs.push_back(Regex::transfer("s.t.a.t.i.c"));
	all_suffixs.push_back(Regex::transfer("c.o.n.s.t"));
	all_suffixs.push_back(Regex::transfer("v.o.i.d"));
	all_suffixs.push_back(Regex::transfer("b.o.o.l"));
	all_suffixs.push_back(Regex::transfer("c.h.a.r"));
	all_suffixs.push_back(Regex::transfer("i.n.t"));
	all_suffixs.push_back(Regex::transfer("l.o.n.g"));
	all_suffixs.push_back(Regex::transfer("f.l.o.a.t"));
	all_suffixs.push_back(Regex::transfer("d.o.u.b.l.e"));
	all_suffixs.push_back(Regex::transfer(":.:"));
	all_suffixs.push_back(Regex::transfer("~"));
	all_suffixs.push_back(Regex::transfer("r.e.t.u.r.n"));
	all_suffixs.push_back(Regex::transfer("i.f"));
	all_suffixs.push_back(Regex::transfer("e.l.s.e"));
	all_suffixs.push_back(Regex::transfer("d.o"));
	all_suffixs.push_back(Regex::transfer("w.h.i.l.e"));
	all_suffixs.push_back(Regex::transfer("f.o.r"));

	size_t n = all_suffixs.size();
	for(size_t i = 0; i < n; i++)
		cout<<all_suffixs[i]<<'\n'<<'\n';
}

void test_2()
{
	string str;

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
	// test_1();
	test_2();
	return 0;
}
