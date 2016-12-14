/*
Author 		: 	Lv Yang
Created 	: 	08 November 2016
Modified 	: 	14 November 2016
Version 	: 	1.0
*/

#include "Regex.h"
#include "RegexOperator.h"

namespace Seven
{
	/*
	encapsulate an action

	( 记参数opstack为栈A，记参数expstack为栈B )
	从栈A中弹出一个运算符，记作 op

	if op 是一元运算符 :  
		从栈B中弹出一个表达式，记作 exp  
		把 exp op 这个整体压入栈B  
		// 例如，op是*，exp是ab|，则把 ab|* 这个整体作为一个临时后缀，压入栈B  
            
	if op 是二元运算符 :  
		从栈B中依次弹出两个表达式，记作 exp1 exp2  
		把 exp2 exp1 op 这个整体（注意exp1和exp2的顺序）压入栈B  
		// 例如，op是.，从栈A先弹出exp1=a，再弹出exp2=b，则把 ba. 这个整体压入栈B  
	*/
	void Regex::action(stack<char> & opstack,stack<string> & expstack)
	{
		char op = opstack.top();
		opstack.pop();

		int op_feature = RegexOperator::feature(op);
		if(op_feature == 1){
			expstack.top() += op;
		}
		else if(op_feature == 2){
			string exp1 = expstack.top();
			expstack.pop();
			string exp2 = expstack.top();
			expstack.pop();
			exp2 += exp1;
			exp2 += op;
			expstack.push(exp2);
		}
	}

	/* transfer a infix-regex into a suffix-regex */
	/* 算法的详细叙述见于 "doc/01-SuffixRegex.md" */
	string Regex::transfer(const string & infix)
	{
		// 若原中缀的长度<=1，则原样返回
		if(infix.length() <= 1){
			string res(infix);
			return res;
		}

		// 准备运算符栈A，后缀表达式栈B
		stack<char> A;
		stack<string> B;

		int n = infix.length();
		int i = 0;
		char ch;
		string tmp;

		while(i < n){
			ch = infix[i];
			if(RegexOperator::support(ch) == true && ch != ')'){
				if(A.empty() == false && RegexOperator::outerPriority(ch) < RegexOperator::innerPriority(A.top()))
					action(A,B);
				else{
					A.push(ch);
					i++;
				}
			}
			else if(ch == ')'){
				do{
					action(A,B);
				}while(A.top() != '(');
				A.pop();
				i++;
			}
			else if(ch == '\\'){
				tmp.clear();
				tmp += ch;
				tmp += infix[i + 1];
				B.push(tmp);
				i = i + 2;
			}
			else{
				tmp.clear();
				tmp += ch;
				B.push(tmp);
				i++;
			}
		}

		while(A.empty() == false && B.empty() == false)
			action(A,B);

		return B.top();
	}

}
