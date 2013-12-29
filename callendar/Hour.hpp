#ifndef __DEF_HOUR_HPP
#define __DEF_HOUR_HPP

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include "libFunc.hpp"

class Hour
{
	public:
		Hour();
		Hour(std::string val);
		Hour(int hour,int min,int sec);

		int getHourVal() const{return this->_hourVal;}
		int getMinVal() const{return this->_minVal;}
		int getSecVal() const{return this->_secVal;}

		std::string toStr() const;

	private:
		int _hourVal;
		int _minVal;
		int _secVal;
};

std::ostream& operator << (std::ostream& flux,Hour const& hour);

#endif // __DEF_HOUR_HPP
