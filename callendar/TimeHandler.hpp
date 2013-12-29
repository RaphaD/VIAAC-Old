#ifndef __DEF_TIMEHANDLER_HPP
#define __DEF_TIMEHANDLER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "Day.hpp"
#include "TimeDB.hpp"
#include "Activity.hpp"
#include "libFunc.hpp"

#define CALLENDAR_DB "CALLENDAR.txt"

class TimeHandler
{
	public:
		TimeHandler();

		void showDate() const;
		void showTime() const;

		void getProgram(std::string com) const;

		void setProgram(std::string str1, std::string str2);

	private :
		TimeDB* _db;
};

#endif // __DEF_TIMEHANDLER_HPP
