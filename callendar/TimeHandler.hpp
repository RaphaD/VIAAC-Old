#ifndef __DEF_TIMEHANDLER_HPP
#define __DEF_TIMEHANDLER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "C_MACRO.hpp"
#include "Day.hpp"
#include "TimeDB.hpp"
#include "Activity.hpp"
#include "CronTab.hpp"
#include "libFunc.hpp"

//#define __VERBOSE
#define CALLENDAR_DB "./callendar/CALLENDAR.txt"
#define CRONTAB_DB "./callendar/CRONTAB.txt"

class TimeHandler
{
	public:
		TimeHandler();

		void showDate() const;
		void showTime() const;

		void getProgram(std::string com) const;

		void setProgram(std::string str1, std::string str2);

	private :
		TimeDB* _call;
		CronTab* _cron;
};

#endif // __DEF_TIMEHANDLER_HPP
