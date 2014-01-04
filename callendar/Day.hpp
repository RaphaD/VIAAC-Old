#ifndef __DEF_DAY_HPP
#define __DEF_DAY_HPP

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#include "C_MACRO.hpp"
#include "libFunc.hpp"

class Day
{
	public:
		Day();
		Day(int number,int month);
		Day(int number,int month,int year);
		Day(std::string str);

		int getNumberVal() const{return this->_numbVal;}
		int getMonthVal() const{return this->_monthVal;}
		int getYearVal() const{return this->_yearVal;}

		std::string toStr() const;

	private :
		int _numbVal;
		int _monthVal;
		int _yearVal;
};

std::ostream& operator << (std::ostream& flux,Day const& day);

#endif // __DEF_DAY_HPP
