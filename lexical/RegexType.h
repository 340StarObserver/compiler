/*
Author 		: 	Lv Yang
Created 	: 	22 November 2016
Modified 	: 	22 November 2016
Version 	: 	1.0
*/

#ifndef _REGEXTYPE_H
#define _REGEXTYPE_H

namespace Seven
{
	/* Regex Type */
	class RegexType
	{
	public:
		/* give a string which can represent a type of regex */
		static const char * represent(int type);

		/* give a priority of a type of regex */
		static int priority(int type);
	};
}

#endif
