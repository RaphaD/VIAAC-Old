#include <iostream>

#include "TimeHandler.hpp"

int main()
{
	std::cout << "Hello World!" << std::endl;
	TimeHandler T;
	T.showTime();
	T.setProgram("30/12/2013 14:00:00 31/12/2013 8:00:00","Pré nouvel an");
	T.getProgram("30/12/2013");
	return 0;
}

