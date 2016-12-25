## compiler ##


Lexical analyzer & grammar analyzer for any language.  
I just want to experience what a compiler is.  


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

        lexical/  
            词法分析代码模块  
        
        grammar/  
            语法分析代码模块  
        
        test/  
            测试代码模块  
        
        conf/  
            配置文件模块  
        
        bin/  
            一些样例输入文件，样例输出文件  


### 二.　如何调用词法分析 ###

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
        	// 1. define some paths  
        	//    ( please change to your own path )  
        	
        	// 正规表达式配置文件  
        	const char * path_conf = "/home/seven/gitspace/compiler/conf/regex.conf";  
        	
        	// 最终生成optimized-DFA的存放路径  
        	const char * path_odfa = "/home/seven/gitspace/compiler/bin/odfa.dat";  
        	
        	// 待分析源代码的路径  
        	const char * path_input = "/home/seven/gitspace/compiler/bin/input.cpp";  
        	
        	// 分析结果日志的路径  
        	const char * path_res = "/home/seven/gitspace/compiler/bin/lex_res.log";  
        	
        	// 分析报错日志的路径  
        	const char * path_error = "/home/seven/gitspace/compiler/bin/lex_error.log";  
        
        
        	// 2. try to load optimized-DFA  
            ODFA * odfa = ODFA::load(path_odfa);  


            // 3. if optimized-DFA not exist  
            if(odfa == NULL){  
                // read regex conf  
                RegexConf::init(path_conf);  

                // build NFA, DFA, optimized-DFA  
                NFA * nfa = NFA::create();  
                DFA * dfa = DFA::create(nfa);  
                odfa = ODFA::create(dfa);  

                // save the optimized-DFA for next time use  
                odfa->save(path_odfa);  

                // delete useless NFA, DFA  
                delete nfa;  
                delete dfa;  
            }  
        
        
        	// 4. scan a code file  
        	//    logs with json format  
        	odfa->scan(path_input, path_res, path_error);  
        
        
        	// 5. delete  
        	delete odfa;  
        
        
        	return 0;  
        }  
        
        // 你可以通过执行 make_lexical.sh 来进行词法模块的编译和链接  
        // 编译成功后，执行 ./bin/main_lexical.sh 试一试吧  
        
        // 注意，如果想用vs编译的话，确保先设置默认编码是UTF8，然后再创建工程导入代码，否则编码问题呵呵  
