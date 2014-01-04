#ifndef __DEF_EVENT_HPP
#define __DEF_EVENT_HPP

#include <string>
#include <vector>

#include "C_MACRO.hpp"
#include "Hour.hpp"
#include "Day.hpp"

class Event
{
	public:
		Event();
		Event(int ind,Day day,Hour hour);
		Event(int ind,std::string day,std::string hour,std::string name);
		Event(std::vector<std::string> vector);

		int getId() const{return this->_id;}
		Day getBeginDate() const{return this->_dBegin;}
		Hour getBeginHour() const{return this->_hBegin;}
		std::string getName() const{return this->_name;}

		virtual ~Event();

	protected :
		int _id;
		Day _dBegin;
		Hour _hBegin;
		std::string _name;
};

std::ostream& operator << (std::ostream& flux,Event const& day);

#endif // __DEF_EVENT_HPP
