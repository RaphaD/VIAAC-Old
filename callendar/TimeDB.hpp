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

#include "C_MACRO.hpp"
#include "DataBase.hpp"
#include "Event.hpp"
#include "Day.hpp"
#include "Hour.hpp"
#include "Activity.hpp"

#define YEAR_BEGIN 1900

class TimeDB : public DataBase
{
	public:
		TimeDB(std::string DBName);

		std::vector<Activity> search(Day& day);
		std::vector<Activity> search(Day& day,Hour& hour);
		void add(Activity acti);
		void removeFromTable(std::string ind);
		bool isSmaller(Activity const& acti1,Activity const& acti2);

		bool isOlder(struct tm* time,Event* event);
		void addToVector(std::vector<Event*>* events,std::vector<std::string>* inter);
		void writeInFile(int ind,Event *event, std::ofstream &flux);

	private:
		std::string _dbFile;
};

#endif // __DEF_TIMEDB_HPP
