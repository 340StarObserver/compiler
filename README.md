## compiler ##


Lexical analyzer & grammar analyzer for any language.  
I just want to experience what a compiler is.  

本工程在输入输出上用了一个第三方库 : rapidjson  


### 一.　目录结构 ###

        doc/  
            设计文档，其中 :  
                词法分析  :  
                    01-SuffixRegex.md    --  中缀正规表达式转后缀  
                    02-Regex.md          --  我要支持哪些正规表达式  
                    03-NFA.md            --  根据后缀正规表达式，构造NFA  
                    04-DFA.md            --  根据NFA，构造DFA  
                    05-ODFA.md           --  根据DFA，构造optimized-DFA  
                    06-Scan.md           --  使用optimized-DFA，对一段代码做词法分析  
                语法分析  :  
                    07-Grammar.md        --  文法如何表示  
                    08-LR1.md            --  根据文法，构造LR(1)语法的预测分析表  
                    09-ScanGrammar.md    --  使用预测分析表，对token序列（词法分析的结果）做语法分析  

        lexical/  
            词法分析代码模块，其中 :  
                main.cpp                 --  词法分析的驱动程序  
                other files              --  词法分析的实现  
        
        grammar/  
            语法分析代码模块，其中 :  
                main.cpp                 --  语法分析的驱动程序  
                other files              --  语法分析的实现  
        
        test/  
            测试代码模块  
        
        conf/  
            配置文件，其中 :  
                regex.conf               --  词法分析所需的正规表达式的配置  
                production.conf          --  语法分析所需的文法产生式的配置  
        
        bin/  
            一些样例输入输出文件，其中 :  
            {  
                input_code.cpp           --  待做词法分析的样例源程序  
                odfa.dat                 --  构建的优化DFA的持久化形式  
                lex_res.log              --  词法分析的结果日志  
                lex_error.log            --  词法分析的报错日志  
            }  
            {  
                input_token.txt          --  待做语法分析的token序列  
                grammar_res.log          --  语法分析的结果日志  
                grammar_error.log        --  语法分析的报错日志  
            }  


### 二.　如何调用词法分析 ###

```c++

// it is the "lexical/main.cpp"  

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
	//    日志以 json 格式记录  
	odfa->scan(path_input, path_res, path_error);  


	// 5. 删除 ODFA  
	delete odfa;  


	return 0;  
}  

// 你可以通过执行 make_lexical.sh 来进行词法分析模块的编译和链接  
// 编译成功后，执行 ./bin/main_lexical.sh 试一试吧  

// 注意，如果想用vs编译的话，确保先设置默认编码是UTF8，然后再创建工程导入代码，否则编码问题呵呵  

```


### 三. 如何调用语法分析 ###

```c++

// it is the "grammar/main.cpp"  

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

// 你可以通过执行 make_grammar.sh 来进行语法分析模块的编译和链接  
// 编译成功后，执行 ./bin/main_grammar.sh 试一试吧  

// 注意，如果想用vs编译的话，确保先设置默认编码是UTF8，然后再创建工程导入代码，否则编码问题呵呵  

```
