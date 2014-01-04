#ifndef __DEF_CRONTAB_HPP
#define __DEF_CRONTAB_HPP

#include <iostream>
#include <sstream>
#include <ostream>
#include <fstream>

#include "C_MACRO.hpp"
#include "DataBase.hpp"
#include "Day.hpp"
#include "Hour.hpp"
#include "Event.hpp"

class CronTab : public DataBase
{
	public:
		CronTab(std::string name);

		//void maj();
		void addToTable(std::string day,std::string hour,std::string name);
		//void removeFromTable(int id);
		//void removeFromTable(Day& day,Hour& hour);
		//Event getNextAlarm(int ind);
		//Event getNextAlarm(Day& day,Hour& hour);

		bool isOlder(struct tm* time,Event* event);
		void addToVector(std::vector<Event*>* events,std::vector<std::string>* inter);
		void writeInFile(int ind,Event *event,std::ofstream& flux);

	private:
		std::string _dbName;
};

#endif // __DEF_CRONTAB_HPP
