## C compiler ##


Lexical analyzer & grammar analyzer for C language.  
I just want to experience what a compiler is.  


### 一.　目录结构 ###

        doc/  
            设计文档  

        lexical/  
            词法分析代码模块  
        
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
        	const char * path_conf = "/home/seven/gitspace/compiler/conf/regex.conf";  
        	const char * path_odfa = "/home/seven/gitspace/compiler/bin/odfa.dat";  
        	const char * path_input = "/home/seven/gitspace/compiler/bin/input.cpp";  
        	const char * path_res = "/home/seven/gitspace/compiler/bin/res.log";  
        	const char * path_error = "/home/seven/gitspace/compiler/bin/error.log";  
        
        	// 2. init regex's conf  
        	RegexConf::init(path_conf);  
        
        	// 3. load or build ODFA  
        	ODFA * odfa = ODFA::load(path_odfa);  
        	if(odfa == NULL){  
        		// if load failed, then build NFA, DFA, optimized-DFA  
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
