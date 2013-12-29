#ifndef __DEF_TIMEDB_HPP
#define __DEF_TIMEDB_HPP

#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <sstream>
#include <ostream>
#include <fstream>
#include <algorithm>

#include "Day.hpp"
#include "Hour.hpp"
#include "Activity.hpp"

#define YEAR_BEGIN 1900

class TimeDB
{
	public:
		TimeDB(std::string DBName);

		bool maj();

		std::vector<Activity> search(Day& day);
		std::vector<Activity> search(Day& day,Hour& hour);
		void add(Activity acti);

		bool isSmaller(Activity const& acti1,Activity const& acti2);
		time_t fillTm(Day day,Hour hour);
		void writeInFile(Activity& acti,std::ofstream& flux);
	private:
		std::string _dbFile;
};

#endif // __DEF_TIMEDB_HPP
