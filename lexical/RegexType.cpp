/*
Author 		: 	Lv Yang
Created 	: 	22 November 2016
Modified 	: 	29 November 2016
Version 	: 	1.0
*/

#include "RegexType.h"

#include <fstream>
using std::ifstream;
using std::ios;

namespace Seven
{
	/* init static data */
	vector<string> RegexType::Infixs;
	vector<string> RegexType::Means;
	vector<int> RegexType::Prioritys;


	/* init from a conf file */
	void RegexType::init(const char * path)
	{
		// 1. open file
		ifstream in;
		in.open(path, ios::in);

		if(in.is_open() == true){
			// 2. get the number of total items
			int n = 0;
			in >> n;

			// 3. resize all the contains
			Infixs.clear();
			Infixs.resize(n + 1);

			Means.clear();
			Means.resize(n + 1);
			
			Prioritys.clear();
			Prioritys.resize(n + 1);
			for(int i = 1; i <= n; i++)
				Prioritys[i] = 0;

			// 4. analyze each line
			int id, pri;
			string tmp1, tmp2;
			while(in >> id >> pri >> tmp1){
				// get infix regex(may be contains ' ' in a regex)
				getline(in, tmp2);
				tmp2 = tmp2.substr(1, tmp2.length() - 1);

				// fill the three tables
				Infixs[id] = tmp2;
				Means[id] = tmp1;
				Prioritys[id] = pri;
			}

			// 5. add item of whitespace
			Infixs[2] = string("(\t| |\n).(\t| |\n)*");
			Means[2] = string("whitespace");
			Prioritys[2] = 1;

			// 6. finally close file
			in.close();
		}
	}


	/* give a priority of a type of regex */
	int RegexType::priority(int type)
	{
		if(type >=1 && type < Infixs.size())
			return Prioritys[type];
		return 0;
	}

}
