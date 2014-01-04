#include <iostream>

#include "TimeHandler.hpp"
#include "MusicMaker.hpp"

//#define __VERBOSE

int main()
{
#ifdef __VERBOSE
	std::cout << "========== Begin of VIAAC ==========" << std::endl;
#endif
	TimeHandler T;
#ifdef __VERBOSE
	std::cout << " === Finished creating TimeHandler ===" << std::endl;
#endif

	return 0;
}

