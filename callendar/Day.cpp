#include "Day.hpp"

Day::Day() :
	_numbVal(0),_monthVal(0),_yearVal(0)
{
#ifdef __VERBOSE

#endif
}

Day::Day(int number,int month) :
	_numbVal(number),_monthVal(month),_yearVal(2013)
{
#ifdef __VERBOSE

#endif
}

Day::Day(int number,int month,int year) :
	_numbVal(number),_monthVal(month),_yearVal(year)
{
#ifdef __VERBOSE

#endif
}

Day::Day(std::string str){
	std::vector<std::string> values=split(str,'/');
	this->_numbVal=atoi(values[0].c_str());
	this->_monthVal=atoi(values[1].c_str());
	this->_yearVal=atoi(values[2].c_str());
#ifdef __VERBOSE

#endif
}

std::string Day::toStr() const{
	std::string res=std::to_string(this->_numbVal)+"/"+
			std::to_string(this->_monthVal)+"/"+std::to_string(this->_yearVal);
#ifdef __VERBOSE

#endif
	return res;
}

std::ostream& operator <<(std::ostream& flux,Day const& day) {
	flux << day.toStr();
#ifdef __VERBOSE

#endif
	return flux;
}
