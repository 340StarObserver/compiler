#!/bin/sh

g++ -c lexical/RegexOperator.cpp -o bin/RegexOperator.obj
echo "[OK] lexical/RegexOperator.h"
echo "[OK] lexical/RegexOperator.cpp"

g++ -c lexical/RegexConf.cpp -o bin/RegexConf.obj
echo "[OK] lexical/RegexConf.h"
echo "[OK] lexical/RegexConf.cpp"

g++ -c lexical/Regex.cpp -o bin/Regex.obj
echo "[OK] lexical/Regex.h"
echo "[OK] lexical/Regex.cpp"

g++ -c lexical/FANode.cpp -o bin/FANode.obj
echo "[OK] lexical/FANode.h"
echo "[OK] lexical/FANode.cpp"

g++ -c lexical/NFA.cpp -o bin/NFA.obj
echo "[OK] lexical/NFA.h"
echo "[OK] lexical/NFA.cpp"

g++ -c lexical/DFA.cpp -o bin/DFA.obj
echo "[OK] lexical/DFA.h"
echo "[OK] lexical/DFA.cpp"

g++ -c lexical/ODFA.cpp -o bin/ODFA.obj
echo "[OK] lexical/ODFA.h"
echo "[OK] lexical/ODFA.cpp"

g++ -c lexical/main.cpp -o bin/main_lexical.obj
echo "[OK] lexical/main.cpp"
echo "compile success"

g++ bin/RegexOperator.obj bin/RegexConf.obj bin/Regex.obj bin/FANode.obj bin/NFA.obj bin/DFA.obj bin/ODFA.obj bin/main_lexical.obj -o bin/main_lexical.exe
echo "link success"
echo "you can run ./bin/main_lexical.exe for a try"
