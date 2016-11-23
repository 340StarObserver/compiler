/*
Author 		: 	Lv Yang
Created 	: 	22 November 2016
Modified 	: 	22 November 2016
Version 	: 	1.0
*/

#include "RegexType.h"

namespace Seven
{
	/* give a string which can represent a type of regex */
	const char * RegexType::represent(int type)
	{
		/* 标识符 */
		if(type == 1) return "id";

		/* 空白符 */
		if(type == 2) return "whitespace";

		/* 整数 */
		if(type == 3) return "integer";

		/* 左花括号 */
		if(type == 4) return "LCurlyBrace";

		/* 右花括号 */
		if(type == 5) return "RCurlyBrace";

		/* 左小括号 */
		if(type == 6) return "LBrace";

		/* 右小括号 */
		if(type == 7) return "RBrace";

		/* 语句结束符(;) */
		if(type == 8) return "end";

		/* 加号 */
		if(type == 9) return "add";

		/* 减号 */
		if(type == 10) return "minus";

		/* 乘号 */
		if(type == 11) return "multi";

		/* 除号 */
		if(type == 12) return "division";

		/* 加等于 */
		if(type == 13) return "ADD";

		/* 减等于 */
		if(type == 14) return "MINUS";

		/* 乘等于 */
		if(type == 15) return "MULTI";

		/* 除等于 */
		if(type == 16) return "DIVISION";

		/* 按位与 */
		if(type == 17) return "BinAnd";

		/* 按位或 */
		if(type == 18) return "BinOr";

		/* 按位异或 */
		if(type == 19) return "BinXor";

		/* 逻辑与 */
		if(type == 20) return "LogicAnd";

		/* 逻辑或 */
		if(type == 21) return "LogicOr";

		/* 逻辑非 */
		if(type == 22) return "LogicNot";

		/* 赋值号 */
		if(type == 23) return "assign";

		/* 大于号 */
		if(type == 24) return "gt";

		/* 小于号 */
		if(type == 25) return "lt";

		/* 等于号 */
		if(type == 26) return "eq";

		/* 大于等于号 */
		if(type == 27) return "gte";

		/* 小于等于号 */
		if(type == 28) return "lte";

		/* # include */
		if(type == 29) return "include";

		/* # ifndef */
		if(type == 30) return "ifndef";

		/* # define */
		if(type == 31) return "define";

		/* # endif */
		if(type == 32) return "endif";

		/* main函数 */
		if(type == 33) return "main";

		/* 名称空间 */
		if(type == 34) return "ns";

		/* using */
		if(type == 35) return "using";

		/* 类 */
		if(type == 36) return "class";

		/* 结构体 */
		if(type == 37) return "struct";

		/* 联合体 */
		if(type == 38) return "union";

		/* 枚举 */
		if(type == 39) return "enum";

		/* 私有 */
		if(type == 40) return "private";

		/* 公有 */
		if(type == 41) return "public";

		/* 静态 */
		if(type == 42) return "static";

		/* 常量 */
		if(type == 43) return "const";

		/* void */
		if(type == 44) return "void";

		/* bool */
		if(type == 45) return "bool";

		/* char */
		if(type == 46) return "char";

		/* int */
		if(type == 47) return "int";

		/* long */
		if(type == 48) return "long";

		/* float */
		if(type == 49) return "float";

		/* double */
		if(type == 50) return "double";

		/* 域运算符 */
		if(type == 51) return "region";

		/* ~(used in deconstructor) */
		if(type == 52) return "~";

		/* return */
		if(type == 53) return "return";

		/* if */
		if(type == 54) return "if";

		/* else */
		if(type == 55) return "else";

		/* do */
		if(type == 56) return "do";

		/* while */
		if(type == 57) return "while";

		/* for */
		if(type == 58) return "for";

		/* otherwise */
		return "";
	}


	/* give a priority of a type of regex */
	int RegexType::priority(int type)
	{
		/* 保留字 has the highest priority */
		if(type >=29 && type <= 58)
			return 10;

		/* +=,  -=,  *=,  /=,  &&,  ||,  ==,  >=,  <= */
		if((type >= 13 && type <= 16) || (type >= 20 && type <= 21) || (type >= 26 && type <= 28))
			return 5;

		/* other valid */
		if(type >= 1 && type <= 58)
			return 1;

		/* invalid */
		return 0;
	}

}
