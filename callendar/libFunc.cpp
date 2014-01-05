#include "libFunc.hpp"

struct tm* currentTime(){
#ifdef __VERBOSE
	std::cout << "[libFunc] currentTime()" << std::endl;
#endif
	time_t sec=time(NULL);
	struct tm* current=localtime(&sec);
#ifdef __VERBOSE
	std::cout << "    End currentTime" << std::endl;
#endif
	return current;
}

std::vector<std::string> toStdVector(std::string toConvert){
#ifdef __VERBOSE
	std::cout << "[libFunc] toStdVector(std::string)" << std::endl;
#endif
	std::string buf;
	std::stringstream ss(toConvert);
	std::vector<std::string> tokens;
	while (ss >> buf){
#ifdef __VERBOSE
	std::cout << "    Loop) inVector " << buf << std::endl;
#endif
		tokens.push_back(buf);
	}
#ifdef __VERBOSE
	std::cout << "    End toStdVector(std::string)" << std::endl;
#endif
	return tokens;
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
#ifdef __VERBOSE
	std::cout << "[libFunc] split(std::string const&,char,std::vector<std::string>)" << std::endl;
#endif
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
#ifdef __VERBOSE
	std::cout << "    Loop) in Vector : " << item << std::endl;
#endif
		elems.push_back(item);
	}
#ifdef __VERBOSE
	std::cout << "    End split(std::string const&,char,std::vector<std::string>)" << std::endl;
#endif
	return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
#ifdef __VERBOSE
	std::cout << "[libFunc] split(std::string const&,char)" << std::endl;
#endif
	std::vector<std::string> elems;
	split(s, delim, elems);
#ifdef __VERBOSE
	std::cout << "    End split(std::string const&,char)" << std::endl;
#endif
	return elems;
}
