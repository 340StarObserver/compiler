/*
Author 		: 	Lv Yang
Created 	: 	22 November 2016
Modified 	: 	01 December 2016
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
			int id, pri;
			string mean, infix;
			RegexConfItem item;

			// clear the original items
			Items.clear();

			// read each line
			while(in >> id >> pri >> mean){
				getline(in, infix);
				infix = infix.substr(1, infix.length() - 1);

				item.id = id;
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
