## 我要支持哪些正则 ##


    在此明确一下我们打算支持哪些正则表达式（中缀形式）吧  
    
    
    01. 标识符  
        (_|A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z|a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z)  
        .  
        (0|1|2|3|4|5|6|7|8|9|_|A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z|a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z)*  
    
    02. 整数  
        0|(1|2|3|4|5|6|7|8|9).(0|1|2|3|4|5|6|7|8|9)*  
    
    03. 左花括号  
        {  
    
    04. 右花括号  
        }  
    
    05. 左小括号  
        (  
    
    06. 右小括号  
        )  
    
    07. 语句结束符  
        ;  
    
    08. 运算符  
        +    -    +.=    -.=  
        
        =  
        
        >    <    =.=    >.=    <.=    
    
    09. 类中成员权限的冒号  
        :  
    
    10. 保留字  
        m.a.i.n  
        
        c.l.a.s.s    s.t.r.u.c.t    u.n.i.o.n    e.n.u.m  
        
        p.r.i.v.a.t.e    p.u.b.l.i.c    s.t.a.t.i.c    c.o.n.s.t  
        
        v.o.i.d    b.o.o.l    c.h.a.r    i.n.t    l.o.n.g    f.l.o.a.t    d.o.u.b.l.e  
        
        :.:    ~  
        
        r.e.t.u.r.n    i.f    e.l.s.e    d.o    w.h.i.l.e    f.o.r  
