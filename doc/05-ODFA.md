## 如何对DFA进行优化 ##


我们使用弱等价的思想来进行DFA的优化，简要概括为 :  

    1. 设初始的总集 U = { S0, S1, S2, ... Sn }  
    
    2. 把 U 拆分为 终结态集A 和 非终结态集B  
        // A中的每个元素，都包含原来NFA中的终结结点  
        // B中的每个元素，都不包含原来NFA中的终结结点  
    
    3. 不断地把A,B拆分，直至所有的状态集都是弱等价的  
        // 即不断地进行迭代，直至不进行拆分操作  
    
    // 举例说明弱等价的意思 :  
    // 等价类状态集 P = { S1, S3, S5 }，总共的终结符有'a'和'b'，那么要求 :  
    // goto(S1, a) 和 goto(S3, a) 和 goto(S5, a)，是属于同一个等价类状态集的  
    // goto(S1, b) 和 goto(S3, b) 和 goto(S5, b)，是属于同一个等价类状态集的  



### 一. 重要操作 -- 拆分状态集 ###

        /*  
        用来拆分状态集的函数  
        
        参数的解释 :  
                table   是DFA的状态转化表  
                vt_num  是终结符的总个数，即table中的每一行的列数  
                U       是当前的等价划分  
                index   是我想对 U[index] 进行拆分  
        
        返回值解释 :  
                当需要对 U[index] 进行进一步拆分 :  
                    从U中移除U[index]  
                    把拆分后的两个新的状态集A1,A2添加到U的尾部  
                    return true  
                当不需要对 U[index] 进行进一步拆分 :  
                    return false  
        */  
        bool split( const vector<int *> & table, int vt_num,  
                    vector<set<int>> & U,        int index )  
        {  
            vector<int> next;                  // 准备邻接状态表  
            
            for(i = 0; i < vt_num; i++)        // 对第i个终结符做分析，看U[index]是否需要进一步拆分  
            {  
                对于U[index]中的每个元素e :  
                    e_next = table[e][i];      // table[e][i]是在原本DFA中，状态e在第i个终结符下的后继状态  
                    e_next = find(U, e_next);  // table[e][i]在当前的划分中，是属于哪一个等价类里的  
                    add e_next into next       // 如此，便得到了 U[index]这个状态集，在当前划分下，的后继状态集  
                
                判断next中的元素是否都一样  
                
                if 都一样 :                     // 即对于这个终结符来说，U[index]不需要进一步拆分  
                    next.clear();              // 清空邻接状态表，以进行下一个终结符的分析  
                
                if 不一样 :  
                    first = next[0];  
                    以first为参照，把 U[index] 分成对应的后继是first的，不是first的两个集合A1,A2  
                    从U中移除U[index]  
                    把A1,A2添加到U的尾部  
                    return true;  
            }  
            
            return false;                      // 对于所有的终结符，U[index]都不需要进行拆分  
        }  



### 二. 算法流程 -- 第一块 -- 状态的等价类划分 ###



### 三. 算法流程 -- 第二块 -- 根据划分好的等价类，构建新的状态转换表 ###

