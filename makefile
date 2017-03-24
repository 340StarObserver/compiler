run/main.exe:run/RegexOperator.obj run/RegexConf.obj run/Regex.obj run/FANode.obj run/NFA.obj run/DFA.obj run/ODFA.obj run/main.obj
	@g++ run/RegexOperator.obj run/RegexConf.obj run/Regex.obj run/FANode.obj run/NFA.obj run/DFA.obj run/ODFA.obj run/main.obj -o run/main.exe
	@echo "success link"

run/main.obj:lexical/main.cpp
	@g++ -c lexical/main.cpp -o run/main.obj
	@echo "[OK] lexical/main.cpp"
	@echo "success compile"

run/ODFA.obj:lexical/ODFA.cpp
	@g++ -c lexical/ODFA.cpp -o run/ODFA.obj
	@echo "[OK] lexical/ODFA.h"
	@echo "[OK] lexical/ODFA.cpp"

run/DFA.obj:lexical/DFA.cpp
	@g++ -c lexical/DFA.cpp -o run/DFA.obj
	@echo "[OK] lexical/DFA.h"
	@echo "[OK] lexical/DFA.cpp"

run/NFA.obj:lexical/NFA.cpp
	@g++ -c lexical/NFA.cpp -o run/NFA.obj
	@echo "[OK] lexical/NFA.h"
	@echo "[OK] lexical/NFA.cpp"

run/FANode.obj:lexical/FANode.cpp
	@g++ -c lexical/FANode.cpp -o run/FANode.obj
	@echo "[OK] lexical/FANode.h"
	@echo "[OK] lexical/FANode.cpp"

run/Regex.obj:lexical/Regex.cpp
	@g++ -c lexical/Regex.cpp -o run/Regex.obj
	@echo "[OK] lexical/Regex.h"
	@echo "[OK] lexical/Regex.cpp"

run/RegexConf.obj:lexical/RegexConf.cpp
	@g++ -c lexical/RegexConf.cpp -o run/RegexConf.obj
	@echo "[OK] lexical/RegexConf.h"
	@echo "[OK] lexical/RegexConf.cpp"

run/RegexOperator.obj:lexical/RegexOperator.cpp
	@g++ -c lexical/RegexOperator.cpp -o run/RegexOperator.obj
	@echo "[OK] lexical/RegexOperator.h"
	@echo "[OK] lexical/RegexOperator.cpp"

clean:
	rm run/*.obj
	rm run/*.exe
