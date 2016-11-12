## 我要支持哪些正则 ##


    在前面的几篇设计文档中，我们分析了如何根据若干个正则来构造出一个大NFA  

    {  
        关于中缀正则变换成后缀正则，见于 doc/01-SuffixRegex.md  
        关于多个后缀正则构造  NFA，见于 doc/02-NFA.md  
    }  
    
    
    那么，我们接下来要解决的便是如何根据NFA来构造DFA了  
    然而在此之前，先来明确一下我们打算支持哪些正则表达式（中缀形式）吧  
    
    
    01. 标识符  
        (_|A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z|a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z)  
        .  
        (0|1|2|3|4|5|6|7|8|9|_|A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z|a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z)*  
    
    02. 空白符  
        (\t| |\n).(\t| |\n)*  
    
    03. 整数  
        0|(1|2|3|4|5|6|7|8|9).(0|1|2|3|4|5|6|7|8|9)*  
    
    04. 左花括号  
        {  
    
    05. 右花括号  
        }  
    
    06. 左小括号  
        (  
    
    07. 右小括号  
        )  
    
    08. 语句结束符  
        ;  
    
    09. 运算符  
        +    -    *    /    +.=    -.=    *.=    /.=  
        
        &    |    ^  
        
        &.&    |.|    !  
        
        =  
        
        >    <    =.=    >.=    <.=    
        
        //　注意　：　乘号，乘等于，按位或，逻辑或　需要用简单NFA的方式来构造然后合并，因为它们与后缀正则中的*和|冲突了  
    
    10. 保留字  
        #. .i.n.c.l.u.d.e    #. .i.f.n.d.e.f    #. .d.e.f.i.n.e    #. .e.n.d.i.f  
        
        m.a.i.n  
        
        n.a.m.e.s.p.a.c.e    u.s.i.n.g  
        
        c.l.a.s.s    s.t.r.u.c.t    u.n.i.o.n    e.n.u.m  
        
        p.r.i.v.a.t.e    p.u.b.l.i.c    s.t.a.t.i.c    c.o.n.s.t  
        
        v.o.i.d    b.o.o.l    c.h.a.r    i.n.t    l.o.n.g    f.l.o.a.t    d.o.u.b.l.e  
        
        :.:    ~  
        
        r.e.t.u.r.n    i.f    e.l.s.e    d.o    w.h.i.l.e    f.o.r  
