## compiler ##


Lexical analyzer & grammar analyzer for any language.  
I just want to experience what a compiler is.  

### 一.　它的特色 ###

        1. 全部由自己实现
        　　词法部分　：　中缀RG  ->  后缀RG          ->  NFA         ->  DFA      ->  ODFA  ->  扫描分析
        　　语法部分　：　文法    ->  LR(1)预测分析表  ->  解决二义冲突  ->  扫描归约
        　　// 只在结果的输入输出上使用了rapidjson这个第三方JSON库
        
        2. 支持任意语言的词法规则和语法规则
        　　a. 通过在词法配置文件中定义若干正规表达式，能支持任意语言的词法规则
        　　b. 支持 * . | ( ) 这五种元符号
        　　c. 通过在语法配置文件中定义若干产生式，能支持任意语言的文法规则
        　　d. 程序中没有一处硬代码
        
        3. 能处理冲突
        　　词法部分　：　通过给RG定义优先级，解决冲突
        　　语法部分　：　通过给文法终结符定义优先级和结合规则，解决"移动-归约冲突"
        
        4. 报错功能
        　　a. 结果日志和错误日志都是以JSON格式记录的
        　　b. 词法分析的时候，可以跳过当前错误，继续分析，来一次性扫描出所有错误


### 二.　目录结构 ###

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
        
        make_lexical.sh                  --  Linux下快速编译词法分析模块的脚本  
        make_grammar.sh                  --  Linux下快速编译语法分析模块的脚本  


### 三.　如何调用词法分析 ###

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
	//     ( 其格式，见于 README.md 的第四点 )  
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


### 四. 如何调用语法分析 ###

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
	//     ( 其格式，见于 README.md 的第四点 )  
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



### 五. 配置文件的格式说明 ###

1. 词法分析所需的正规表达式配置文件 "conf/regex.conf"  

        举个例子 :  

        1 num 0|(1|2|3|4|5|6|7|8|9).(0|1|2|3|4|5|6|7|8|9)*
        1 gt >
        5 gte >.=
        
        每行格式 :  
        
        优先级 含义字符串 正规表达式的中缀形式
        
            // 注意，空格是半角的  
            // 注意，优先级 ≥ 1，且该值越大则优先级越高  
                    上述例子中 >= 要比 > 的优先级高，因为 >= 可以被解释成 > 和 =，但是前者优先级高故取前者  
            // 注意，正规表达式中使用 . | * ( ) 来做运算符  
                    其中 :  
                        . 表示连接  
                        | 表示或运算  
                        * 表示闭包运算  
                        ( 表示左括号
                        ) 表示右括号
                    若你的正规表达式中本身就要出现这三个符号，怎么办 ?  
                        使用 \. 来表示这个 . 要解释成终结符，而不是连接符  
                        使用 \| 来表示这个 | 要解释成终结符，而不是或运算  
                        使用 \* 来表示这个 * 要解释成终结符，而不是闭包运算  
                        使用 \( 来表示这个 ( 要解释成终结符，而不是左括号  
                        使用 \) 来表示这个 ) 要解释成终结符，而不是右括号  


2. 语法分析所需的文法产生式配置文件  

        举个例子 :  
        
        S' -> S
        0 0
        0 0
        0 0
        
        S -> if S else S
        0 1 0 1 0
        0 3 0 4 0
        0 1 0 1 0
        
        每个产生式的格式 :  
        
        1. 第一行形如 产生式左部 -> 右部第一个符号 右部第二个符号 ...  
        
            // 注意，首个产生式必须是 S' -> S  
            // 注意，空格是半角的  
            // 注意，产生式左部与右部之间的 -> 必须写  
            // 注意，如果要表示形如 A -> ε  则直接写成 A ->  
        
        2.　第二行是该产生式中每个文法符号是否是终结符  
        
            // 注意，0 表示 非终结符  
            // 注意，1 表示 终结符  
        
        3. 第三行是该产生式中每个文法符号的优先级  
        
            // 该优先级字段，用来在构造"预测分析表"时处理"移动归约冲突"  
            // 注意，该字段值越大，则优先级越高  
            // 注意，非终结符的优先级一律填 0  
        
        4. 第四行是该产生式中每个文法符号的结合规则  
        
            // 该结合规则，用来在构造"预测分析表"时处理"移动归约冲突"  
            // 注意，非终结符的结合规则一律填 0  
            // 注意，某终结符若是左结合的，则该值填 1  
            // 注意，某终结符若是右结合的，则该值填 0  
        
        5. 接下来是一个空行  
        
            // 注意，相邻产生式定义块，之间的空行，必须写  
            // 注意，最后一个产生式定义块的结尾处，必须不写空行  
