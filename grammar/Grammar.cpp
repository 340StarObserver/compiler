/*
Author 		: 	Lv Yang
Created 	: 	19 December 2016
Modified 	: 	21 December 2016
Version 	: 	1.0
*/

#include "Grammar.h"

#include <fstream>
using std::ifstream;
using std::ios;

#include <sstream>
using std::stringstream;

namespace Seven
{
	/* init static data */
	string Production::Null;
	vector<Production> Grammar::Plist;


	/* operator < */
	bool Production::operator < (const Production & p)const
	{
		// 1. compare ppos
		if(ppos < p.ppos)
			return true;
		if(ppos > p.ppos)
			return false;

		// 2. compare sstr
		if(sstr < p.sstr)
			return true;
		if(sstr > p.sstr)
			return false;

		// 3. compare exp
		int n1 = this->exp.size();
		int n2 = p.exp.size();
		if(n1 < n2)
			return true;
		if(n1 > n2)
			return false;
		for(int i = 0; i < n1; i++){
			if(this->exp[i] < p.exp[i])
				return true;
			if(this->exp[i] > p.exp[i])
				return false;
		}
		return false;
	}


	/* operator == */
	bool Production::operator == (const Production & p)const
	{
		// 1. compare ppos
		if(ppos != p.ppos)
			return false;

		// 2. compare sstr
		if(sstr != p.sstr)
			return false;

		// 3. compare exp
		int n1 = this->exp.size();
		int n2 = p.exp.size();
		if(n1 != n2)
			return false;
		for(int i = 0; i < n1; i++){
			if(this->exp[i] != p.exp[i])
				return false;
		}

		return true;
	}


	/* init from a conf file */
	void Grammar::init(const char * path)
	{
		// open file
		ifstream in;
		in.open(path, ios::in);

		// clear the original data
		Plist.clear();

		if(in.is_open() == true)
		{
			// read line by line
			string line;
			while(getline(in, line)){
				// 1. create a Production
				Production prod;
				prod.ppos = 0;

				// 2. split this line into words
				stringstream ss(line);
				string word;
				while(getline(ss, word, ' '))
					prod.exp.push_back(word);
				prod.exp.erase(prod.exp.begin() + 1);
				if(prod.exp.size() == 1){
					// push ε
					prod.exp.push_back(Production::Null);
				}

				// 3. fill prod._isVt[]
				int n = prod.exp.size();
				int value;
				while(n > 0){
					in >> value;
					prod.isVt.push_back(bool(value));
					n--;
				}

				// 4. push this production
				Plist.push_back(prod);

				// 5. jump '\n' & an empty line
				getline(in, line);
				getline(in, line);
			}

			// finally close file
			in.close();
		}
	}

}
