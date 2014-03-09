#ifndef __LIBTREATER_HPP
#define __LIBTREATER_HPP

#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include <string.h>
#include <algorithm>

//#define MUSIC_LIB "./music/"

bool isMP3(char file[]);
std::vector<std::string> getNames(std::string filename);

#endif // LIBTREATER_HPP
