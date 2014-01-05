#include "Hour.hpp"

Hour::Hour() :
	_hourVal(0),_minVal(0),_secVal(1)
{
}

Hour::Hour(int hour,int min,int sec) :
	_hourVal(hour),_minVal(min),_secVal(sec)
{
}

Hour::Hour(std::string val)
{
	std::vector<std::string> x=split(val,':');
	this->_hourVal=atoi(x[0].c_str());
	this->_minVal=atoi(x[1].c_str());
	this->_secVal=atoi(x[2].c_str());
}

std::string Hour::toStr() const{
	std::string res=std::to_string(this->_hourVal)+":"+
			std::to_string(this->_minVal)+":"+std::to_string(this->_secVal);
	return res;
}

std::ostream& operator << (std::ostream& flux,Hour const& hour){
	flux << hour.toStr();
	return flux;
}
