#include "libFunc.hpp"

struct tm* currentTime(){
#ifdef __VERBOSE

#endif
	time_t sec=time(NULL);
	struct tm* current=localtime(&sec);
#ifdef __VERBOSE

#endif
	return current;
}

std::vector<std::string> toStdVector(std::string toConvert){
#ifdef __VERBOSE

#endif
	std::string buf;
	std::stringstream ss(toConvert);
	std::vector<std::string> tokens;
	while (ss >> buf){
#ifdef __VERBOSE

#endif
		tokens.push_back(buf);
	}
	return tokens;
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
#ifdef __VERBOSE

#endif
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
#ifdef __VERBOSE

#endif
		elems.push_back(item);
	}
	return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
#ifdef __VERBOSE

#endif
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}
