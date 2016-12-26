## 如何用LR(1)预测分析表来扫描一段文法符号串 ##


### 一. 如何表示文法符号序列 ###

        首先，语法分析的输入是文法符号序列，而它实际上是词法分析的输出产物  
            // 关于词法分析的扫描算法，见于 doc/06-ScanLex.md  

        我的词法分析的输出结果是多行json，每行json形如 { "id" : 内码, "word" : 单词, "type" : 词素类型 }  
    
        可以把每个json转化成 pair< type, word >  
            // 其中，type就是抽象的文法符号，例如 id num  
            // 其中，word就是该文法符号对应的实际代码中的单词，例如 x 3  
            // 文法符号序列，就是 pair序列  


### 二. 语法分析扫描算法 ###

        文法符号序列 = 文法符号序列 + "$"  
            // "$" 是最后的结束符  
            // 用 q 指向文法符号序列的开头位置  
        
        准备工作栈 :  
            状态栈 A   :   用 p1 维护该栈的栈顶  
            符号栈 B   :   用 p2 维护该栈的栈顶  
        
        把 状态0 压入 状态栈A  
        
        while( true )  
        {  
            if( Action[p1, q] 是 "移动状态x进栈" )  
            {  
                push 状态x           to 状态栈A  
                push q所指向的文法符号 to 符号栈B  
                move q to 下一个位置  
            }  
            
            else if( Action[p1, q] 是 "按i(>=1)号产生式归约" )  
            {  
                n = i号产生式右部的长度  
                
                pop 状态栈A n个元素  
                pop 符号栈B n个元素（假设依次弹出 c1, c2, ...cn）  
                
                令 Ik = 状态栈A.top  
                令 S  = i号产生式的左部  
                
                push S           to 符号栈B  
                push Goto[Ik, S] to 状态栈A  
                
                输出一个归约式 S -> cn cn-1 ... c2 c1                  
            }  
            
            else if( Action[p1, q] 是 "Accept" )  
                return  
            
            else  
                报错  
        }  
