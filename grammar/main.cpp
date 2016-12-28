/*
Author 		: 	Lv Yang
Created 	: 	28 December 2016
Modified 	: 	28 December 2016
Version 	: 	1.0
*/

/* shows how to use grammar analyze */

#include "LRPPT.h"
using Seven::Grammar;
using Seven::LRPPT;

int main()
{
	// 1. 首先定义一些路径
	//    ( 请换成你自己的路径，并且推荐使用绝对路径 )

	// 文法产生式配置文件
	const char * path_conf = "/home/seven/gitspace/compiler/conf/production.conf";

	// tokens序列的输入文件
	const char * path_input = "/home/seven/gitspace/compiler/bin/input_token.txt";

	// 语法分析的结果日志
	const char * path_res = "/home/seven/gitspace/compiler/bin/grammar_res.log";

	// 语法分析的报错日志
	const char * path_error = "/home/seven/gitspace/compiler/bin/grammar_error.log";

	// 2. 初始化配置
	Grammar::init(path_conf);

	// 3. 创建LR(1)语法的预测分析表
	LRPPT * ppt = LRPPT::create();

	// 4. 做语法分析
	ppt->scan(path_input, path_res, path_error);

	// 5. 删除预测分析表
	delete ppt;

	return 0;
}
