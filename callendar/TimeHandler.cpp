#include "TimeHandler.hpp"

TimeHandler::TimeHandler():
	_db(new TimeDB(CALLENDAR_DB))
{
}

void TimeHandler::showTime() const{
	struct tm* current=currentTime();
	std::cout << current->tm_hour << " h " << current->tm_min << " min" << std::endl;
}

void TimeHandler::showDate() const{
	struct tm* current=currentTime();
	std::cout << current->tm_mday << "/" <<
				 current->tm_mon+1 << "/" <<
				 YEAR_BEGIN+current->tm_year << std::endl;
}

void TimeHandler::getProgram(std::string com) const{
	std::vector<Activity> res;
	std::vector<std::string> inter=split(com,' ');
	if(inter.size()==2){
		Day day(inter[0]);Hour hour(inter[1]);
		res=this->_db->search(day,hour);
	}else if(inter.size()==1){
		Day day(inter[0]);
		res=this->_db->search(day);
	}
	for(unsigned i(0);i<res.size();++i){
		std::cout << res[i] << std::endl;
		std::cout << "===================" << std::endl;
	}
}

void TimeHandler::setProgram(std::string str1,std::string str2){
	std::vector<std::string> inter=split(str1,' ');
	if(inter.size()==4){
		Day bDay(inter[0]); Hour bHour(inter[1]);
		Day eDay(inter[2]); Hour eHour(inter[3]);
		std::string name(str2);
		this->_db->add(Activity(name,bDay,eDay,bHour,eHour));
	}
}
