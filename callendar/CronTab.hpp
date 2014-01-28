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

		void addToTable(Event event);
		time_t getNextAlarm(int ind);

		time_t getNextIte(Event &event);
		bool isRepetitive(Event& event);
		bool isOlder(struct tm* time,Event* event);
		void addToVector(std::vector<Event*>* events,std::vector<std::string>* inter);
		void writeInFile(int ind,Event *event,std::ofstream& flux);

	private:
		std::string _dbName;
};

#endif // __DEF_CRONTAB_HPP
