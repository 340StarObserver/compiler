/*
Author 		: 	Lv Yang
Created 	: 	05 December 2016
Modified 	: 	28 December 2016
Version 	: 	1.0
*/

/* shows how to use lexical analyze */

#include "RegexConf.h"
#include "ODFA.h"
using Seven::RegexConf;
using Seven::NFA;
using Seven::DFA;
using Seven::ODFA;

#include <iostream>
using std::cout;

int main()
{
	// 1. 首先定义一些路径
	//    ( 请换成你自己的路径，并且推荐使用绝对路径 )

	// 正规表达式配置文件
	const char * path_conf = "/home/seven/gitspace/compiler/conf/regex.conf";

	// 最终生成optimized-DFA的存放路径
	const char * path_odfa = "/home/seven/gitspace/compiler/bin/odfa.dat";

	// 待分析源代码的路径
	const char * path_input = "/home/seven/gitspace/compiler/bin/input_code.cpp";

	// 分析结果日志的路径
	const char * path_res = "/home/seven/gitspace/compiler/bin/lex_res.log";

	// 分析报错日志的路径
	const char * path_error = "/home/seven/gitspace/compiler/bin/lex_error.log";


	// 2. 尝试从磁盘上加载 optimized-DFA
	ODFA * odfa = ODFA::load(path_odfa);

	// 3. 若磁盘上当前没有 optimized-DFA，则需要构建它
	if(odfa == NULL){
		// 读取正规表达式配置文件
		RegexConf::init(path_conf);

		// 依次构建 NFA, DFA, ODFA
		NFA * nfa = NFA::create();
		DFA * dfa = DFA::create(nfa);
		odfa = ODFA::create(dfa);

		// 保存这个ODFA，以便下次使用
		odfa->save(path_odfa);

		// 删除无用的 NFA, DFA
		delete nfa;
		delete dfa;
	}


	// 4. 扫描一段源程序
	//     日志以 json 格式记录
	odfa->scan(path_input, path_res, path_error);


	// 5. 删除 ODFA
	delete odfa;

	return 0;
}
