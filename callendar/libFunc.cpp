#include "libFunc.hpp"

struct tm* currentTime(){
	time_t sec=time(NULL);
	struct tm* current=localtime(&sec);
	return current;
}

std::vector<std::string> toStdVector(std::string toConvert){
	std::string buf;
	std::stringstream ss(toConvert);
	std::vector<std::string> tokens;
	while (ss >> buf){
		tokens.push_back(buf);
	}
	return tokens;
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}
