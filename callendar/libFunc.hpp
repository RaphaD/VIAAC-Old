#ifndef __DEF_LIBFUNC_HPP
#define __DEF_LIBFUNC_HPP

#include <ctime>
#include <string>
#include <vector>
#include <sstream>

#include "C_MACRO.hpp"

#define YEAR_BEGIN 1900

struct tm *currentTime();
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);

#endif // __DEF_LIBFUNC_HPP
