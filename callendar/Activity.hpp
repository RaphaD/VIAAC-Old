#ifndef __DEF_ACTIVITY_HPP
#define __DEF_ACTIVITY_HPP

#include <ctime>

#include "Day.hpp"
#include "Hour.hpp"
#include "libFunc.hpp"

#define HASH_POS 3

class Activity
{
	public:
		Activity();
		Activity(std::vector<std::string> vector);
		Activity(std::string name, Day &dBegin, Day &dEnd, Hour &hBegin, Hour &hEnd);

		std::string getName() const{return this->_name;}
		Day getBeginDate() const{return this->_dBegin;}
		Hour getBeginHour() const{return this->_hBegin;}
		Day getEndDate() const{return this->_dEnd;}
		Hour getEndHour() const{return this->_hEnd;}

		std::string compare(Day const& day);
		std::string compare(Hour const& hour);

	private :
		std::string _name;
		Day _dBegin;
		Day _dEnd;
		Hour _hBegin;
		Hour _hEnd;
};

std::ostream& operator <<(std::ostream& flux,Activity const& acti);

#endif // __DEF_ACTIVITY_HPP
