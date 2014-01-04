#include "TimeHandler.hpp"

TimeHandler::TimeHandler():
	_call(new TimeDB(CALLENDAR_DB)),_cron(new CronTab(CRONTAB_DB))
{
#ifdef __VERBOSE
	std::cout << "[TimeHandler] TimeHandler::TimeHandler()" << std::cout;
#endif
}

void TimeHandler::showTime() const{
#ifdef __VERBOSE
	std::cout << "[TimeHandler] TimeHandler::showTime()" << std::endl;
#endif
	struct tm* current=currentTime();
	std::cout << current->tm_hour << " h " << current->tm_min << " min" << std::endl;
}

void TimeHandler::showDate() const{
#ifdef __VERBOSE
	std::cout << "[TimeHandler] TimeHandler::showDate()" << std::endl;
#endif
	struct tm* current=currentTime();
	std::cout << current->tm_mday << "/" <<
				 current->tm_mon+1 << "/" <<
				 YEAR_BEGIN+current->tm_year << std::endl;
}

void TimeHandler::getProgram(std::string com) const{
#ifdef __VERBOSE
	std::cout << "[TimeHandler] TimeHandler::getProgram(std::string)" << std::endl;
	std::cout << "Param : " << com << std::endl;
#endif
	std::vector<Activity> res;
	std::vector<std::string> inter=split(com,' ');
	if(inter.size()==2){
		Day day(inter[0]);Hour hour(inter[1]);
#ifdef __VERBOSE
		std::cout << "Day and hour call" << std::endl;
		std::cout << "Day : " << day << std::endl;
		std::cout << "Hour : " << hour << std::endl;
#endif
		res=this->_call->search(day,hour);
	}else if(inter.size()==1){
		Day day(inter[0]);
#ifdef __VERBOSE
		std::cout << "Day call" << std::endl;
		std::cout << "Day : " << day << std::endl;
#endif
		res=this->_call->search(day);
	}
	for(unsigned i(0);i<res.size();++i){
		std::cout << res[i] << std::endl;
		std::cout << "===================" << std::endl;
	}
}

void TimeHandler::setProgram(std::string str1,std::string str2){
#ifdef __VERBOSE
	std::cout << "[TimeHandler] TimeHandler::setProgram(std::string,std::string)" << std::endl;
	std::cout << "setProgram method with param : " << str1 << " " << str2 << std::endl;
#endif
	std::vector<std::string> inter=split(str1,' ');
	if(inter.size()==4){
		Day bDay(inter[0]); Hour bHour(inter[1]);
		Day eDay(inter[2]); Hour eHour(inter[3]);
		std::string name(str2);
#ifdef __VERBOSE
		std::cout << "Good number of parameters" << std::endl;
		std::cout << "begin Day : " << bDay << std::endl;
		std::cout << "end Day : " << eDay << std::endl;
		std::cout << "begin Hour : " << bHour << std::endl;
		std::cout << "end Hour : " << eHour << std::endl;
#endif
		this->_call->add(Activity(0,name,bDay,eDay,bHour,eHour));
	}
}
