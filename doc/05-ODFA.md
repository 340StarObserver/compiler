## 如何对DFA进行优化 ##


我们使用弱等价的思想来进行DFA的优化，简要概括为 :  

    1. 设初始的总集 T = { S0, S1, S2, ... Sn }  
    
    2. 把 T 拆分为 终结态集A 和 非终结态集B  
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

        设：全部状态的总集 T = { S0, S1, S2, ... Sn }  
        
        divide T into A & B  
        // A 是终结态集合  
        // B 是非终结态集合  
        
        vector< set<int> > U;  
        U.push_back(A);  
        U.push_back(B);  
        // 创建一个初始划分  
        // 这个初始划分中，一开始仅仅包含终结太集合&非终结态集合  
        
        int ori_size;  
        int cur_size = U.size();  
        // ori_size 是每一轮迭代前的划分中的等价类的数目  
        // cur_size 是每一轮迭代后的划分中的等价类的数目  
        
        do  
        {  
            ori_size = cur_size;  
            // 临时记录上一轮迭代后的U的规模  
        
            int i = 0;  
            
            // 针对当前划分中的每一个等价类，去分析它是否需要进一步的划分  
            // 因为在这过程中，如果存在等价类是要进一步划分的，那么U的规模会增大，所以U.size()是动态的  
            while( i < U.size() )  
            {  
                if( split(DFA的状态转化表, 终结符数目, U, i) == false )  
                    i++;  
                    // 发生拆分的时候，下标指针是不变的  
                    // 不发生拆分的时候，下标指针才会加一  
            }  
            
            cur_size = U.size();  
            // 这一轮迭代后的，新的U的规模  
            
        }while( cur_size != ori_size );  
        // 当某次迭代完成后，发现划分中的等价类的数目没有发生变化  
        // 则说明所有的等价类都满足弱等价了，即可以结束了  
        
        至此，得到了弱等价的划分U  



### 三. 算法流程 -- 第二块 -- 根据划分好的等价类，构建新的状态转换表 ###

        int m = U.size();  
        int n = the number of vt  
        // m 是优化过后的新的DFA的状态数  
        // n 是终结符的总数  
        
        int new_table[m][n];  
        // 新的DFA的状态转化表的结构  
        // 这里只是为了表示得简单一些，大家也知道这语法是不通过的  
        
        for(i = 0; i < m; i++)  
        {  
            for(j = 0; j < n; j++)  
            {  
                该等价类的代表元素represent = U[i][0];  
                // 就选取每个等价类里的第零个元素作为代表吧  
                
                next = table[represent][j];  
                // 注意，这里是table，而不是new_table  
                // next 是原来未优化的时候，状态represent在j号终结符下的后继状态  
                
                next = find(U, next);  
                new_table[i][j] = next;  
                // next 是属于哪一个等价类，则那个等价类的下标，就是优化DFA情况下的后继  
            }  
        }  
        
        至此，得到了优化DFA的状态转换表  
        // 虽然我们可以根据这个状态转换表，来构建一个有向图，它会占用更少的内存  
        // 但是 ：  
        // I . 有向图结构难以方便地做序列化和反序列化，即很难很明晰地持久化到磁盘上  
        // II. 而数组容易进行持久化和恢复，即只需要计算一次，并存储到磁盘上，以后做词法分析时直接从磁盘上load这张表即可  
