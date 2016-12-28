#!/bin/sh

g++ -c grammar/Grammar.cpp -o bin/Grammar.obj
echo "[OK] grammar/Grammar.h"
echo "[OK] grammar/Grammar.cpp"

g++ -c grammar/LRPPT.cpp -o bin/LRPPT.obj
echo "[OK] grammar/LRPPT.h"
echo "[OK] grammar/LRPPT.cpp"

g++ -c grammar/main.cpp -o bin/main_grammar.obj
echo "[OK] grammar/main.cpp"
echo "compile success"

g++ bin/Grammar.obj bin/LRPPT.obj bin/main_grammar.obj -o bin/main_grammar.exe
echo "link success"
echo "you can run ./bin/main_grammar.exe for a try"
