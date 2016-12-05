/*
Author 		: 	Lv Yang
Created 	: 	22 November 2016
Modified 	: 	01 December 2016
Version 	: 	1.0
*/

#ifndef _REGEXCONF_H
#define _REGEXCONF_H

#include <vector>
using std::vector;

#include <string>
using std::string;

namespace Seven
{
	/* one regex conf item */
	struct RegexConfItem
	{
		int id; 			// 该正则的编号( 从1开始 )
		int priority; 		// 该正则的优先级( 越大优先级越高 )
		string mean; 		// 该正则的含义
		string infix; 		// 该正则的中缀表达式
	};


	/* regex conf */
	class RegexConf
	{
	public:
		/* all the regexs' conf items */
		static vector<RegexConfItem> Items;

		/*
		init from a conf file
		Tip1 :
			由于C++的相对路径的计算是以执行命令所在的路径为参考的,
			并不是相对于这份代码文件
			例如 :
				A目录下有a.cpp和b.conf,代码中调用的是"b.conf",
				编译链接后生成的a.exe也在A目录下,
				我在A目录下执行 ./a.exe 是可以读取配置文件的,
				而在A的上级目录下执行 ./A/a.exe 是会报运行时错误的
			所以，参数推荐使用绝对路径
		Tip2 :
			配置文件的格式
			每一行定义了一个正规表达式的信息，形如 : 编号 优先级 含义 中缀表达式
		Tip3 :
			该方法必须在构造NFA,DFA之前就被调用
		*/
		static void init(const char * path);
	};
}

#endif
