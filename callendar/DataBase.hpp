#ifndef __DEF_DATABASE_HPP
#define __DEF_DATABASE_HPP

#include <iostream>
#include <ostream>
#include <sstream>
#include <fstream>
#include <string>
#include <ctime>

#include "C_MACRO.hpp"
#include "Event.hpp"
#include "Day.hpp"
#include "Hour.hpp"
#include "libFunc.hpp"

class DataBase
{
	public:
		DataBase(std::string name);

		bool maj();
		void removeFromTable(int ind);

		std::string isEventSmaller(const Event &first,const Event &second);
		time_t fillTm(Day day,Hour hour);

		virtual bool isOlder(struct tm* time,Event* event)=0;
		virtual void addToVector(std::vector<Event*>* events,std::vector<std::string>* inter)=0;
		virtual void writeInFile(int ind,Event *event,std::ofstream& flux)=0;

	protected :
		std::string _dbName;
};

#endif // __DEF_DATABASE_HPP
