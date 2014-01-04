#ifndef __DEF_STATFILE_HPP
#define __DEF_STATFILE_HPP

//#define __STATISTICS

#ifdef __STATISTICS

#include <iostream>
#include <fstream>
#include <sstream>
#include <ostream>
#include <istream>

#define STAT_COUNT "STAT_FILE.txt"

void openStat(long double &turn,long unsigned& number_turn);
void writeStat(long double &turn,long unsigned& number_turn);

#endif //__STATISTICS

#endif // __DEF_STATFILE_HPP
