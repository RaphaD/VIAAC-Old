#include <iostream>

#include "TimeHandler.hpp"

int main()
{
	TimeHandler T;

	T.showDate();
	T.showTime();

	T.getProgram("15/2/2014 9:30:0");

	T.setProgram("20/2/2014 14:00:00 21/2/2014 15:00:00","TEST de la mort kitue");
	return 0;
}

