#ifndef __DEF_ACTIVITY_HPP
#define __DEF_ACTIVITY_HPP

#include <ctime>

#include "C_MACRO.hpp"
#include "Event.hpp"
#include "Day.hpp"
#include "Hour.hpp"
#include "libFunc.hpp"

class Activity : public Event
{
	public:
		Activity();
		Activity(std::vector<std::string> vector);
		Activity(int ind, std::string name, Day &dBegin, Day &dEnd, Hour &hBegin, Hour &hEnd);

		Day getEndDate() const{return this->_dEnd;}
		Hour getEndHour() const{return this->_hEnd;}

	private :
		Day _dEnd;
		Hour _hEnd;
};

std::ostream& operator <<(std::ostream& flux,Activity const& acti);

#endif // __DEF_ACTIVITY_HPP
