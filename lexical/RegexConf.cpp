/*
Author 		: 	Lv Yang
Created 	: 	22 November 2016
Modified 	: 	14 December 2016
Version 	: 	1.0
*/

#include "RegexConf.h"

#include <fstream>
using std::ifstream;
using std::ios;

namespace Seven
{
	/* init static data */
	vector<RegexConfItem> RegexConf::Items;


	/* init from a conf file */
	void RegexConf::init(const char * path)
	{
		// open file
		ifstream in;
		in.open(path, ios::in);

		if(in.is_open() == true){
			// prepare some temp variables
			int id = 0, pri;
			string mean, infix;
			RegexConfItem item;

			// clear the original items
			Items.clear();

			// read each line
			while(in >> pri >> mean){
				/*
				其中，pri是整数，mean是不带有空格的字符串，故直接读取即可
				其中，infix是可能带有空格的字符串，故需要从mean的结尾处开始读完这一行剩下的全部字符
				又因为mean和infix之间有一个空格隔开，故读取infix后需要丢弃开头的空格
				*/
				getline(in, infix);
				infix = infix.substr(1, infix.length() - 1);

				item.id = ++id;
				item.priority = pri;
				item.mean = mean;
				item.infix = infix;

				Items.push_back(item);
			}

			// finally close file
			in.close();
		}
	}

}
