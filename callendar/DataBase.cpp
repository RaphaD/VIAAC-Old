#include "DataBase.hpp"

// --------------------------------------------------------

DataBase::DataBase(std::string name) : _dbName(name)
{
}

// --------------------------------------------------------

bool DataBase::maj(){
#ifdef __VERBOSE
	std::cout << "[DataBase] DataBase::maj()" << std::endl;
	std::cout << "    Opening " << this->_dbName << " in reading mode" << std::endl;
#endif
	/* Ouverture et lecture du fichier */
	std::ifstream fichierR(this->_dbName.c_str(),std::ios::in);

	std::vector<Event*> events;
	if(!fichierR){
		std::cout << "Error while opening file " << this->_dbName << std::endl;
		return false;
	}else{
		std::string contennu;
		while(std::getline(fichierR,contennu)){
#ifdef __VERBOSE
			std::cout << "    1°) Line read : " << contennu << std::endl;
#endif
			std::vector<std::string> inter=split(contennu,' ');
			this->addToVector(&events,&inter);
		}
	}
#ifdef __VERBOSE
	std::cout << "    2°) Closing callendar database" << std::endl;
#endif
	fichierR.close();

	/* Ouverture et écriture dans le fichier */
#ifdef __VERBOSE
	std::cout << "    3°) Opening " << this->_dbName << " in writting mode" << std::endl;
#endif
	std::ofstream fichierW(this->_dbName.c_str(), std::ios::out | std::ios::trunc);

	struct tm* time=currentTime();
	int count(0);
	for(unsigned i(0);i<events.size();++i){
		if(this->isOlder(time,events[i])){
#ifdef __VERBOSE
			std::cout << "    Loop) Written in file : " << events[i] << std::endl;
#endif
			this->writeInFile(count,events[i],fichierW);
			++count;
		}
	}
#ifdef __VERBOSE
	std::cout << "    4°) Closing callendar database" << std::endl;
#endif
	fichierW.close();
	return true;
}

// --------------------------------------------------------

void DataBase::removeFromTable(int id){
#ifdef __VERBOSE
	std::cout << "[DataBase] DataBase::removeFromTable(int)" << std::endl;
	std::cout << "    Param :" << id << std::endl;
#endif
	std::ifstream fichierR(this->_dbName.c_str(),std::ios::in);
	std::vector<Event*> events;
	if(!fichierR){
		std::cout << "Error while opening file " << this->_dbName << std::endl;
	}else{
#ifdef __VERBOSE
	std::cout << "    1°) Opening database in reading mode ok" << std::endl;
#endif
		std::string contennu;
		Event eventC;
		bool stop(false);
		while((std::getline(fichierR,contennu)) && !stop){
			std::vector<std::string> inter=split(contennu,' ');
			eventC=Event(inter);
			if(eventC.getId()==id){
				stop=true;
			}else{
				this->addToVector(&events,&inter);
			}
		}
#ifdef __VERBOSE
	std::cout << "    2°) Stopped with " << contennu << std::endl;
#endif
		while(std::getline(fichierR,contennu)){
			std::vector<std::string> inter=split(contennu,' ');
			this->addToVector(&events,&inter);
		}
	}
#ifdef __VERBOSE
	std::cout << "    3°) Reading mode finished" << std::endl;
#endif
	fichierR.close();
	std::ofstream fichierW(this->_dbName.c_str(), std::ios::out | std::ios::trunc);
	for(unsigned i(0);i<events.size();++i){
#ifdef __VERBOSE
	std::cout << "    Loop) Writting : " << *events[i] << std::endl;
#endif
		this->writeInFile(i,events[i],fichierW);
	}
#ifndef __VERBOSE
	std::cout << "    End DataBase::removeFromTable(int)" << std::endl;
#endif
}

// --------------------------------------------------------

std::string DataBase::isEventSmaller(Event const& first, Event const& second){
#ifdef __VERBOSE
	std::cout << "[DataBase] DataBase::isEventSmaller(Event const&,Event const&)" << std::endl;
#endif
	time_t beg1=this->fillTm(first.getBeginDate(),first.getBeginHour());
	time_t beg2=this->fillTm(second.getBeginDate(),second.getBeginHour());
	if(difftime(beg1,beg2)<0){
#ifdef __VERBOSE
	std::cout << "    1°) True case" << std::endl;
#endif
		return "true";
	}else if(difftime(beg1,beg2)==0){
#ifdef __VERBOSE
	std::cout << "    2°) Same case" << std::endl;
#endif
		return "same";
	}else{
#ifdef __VERBOSE
	std::cout << "    3°) False case" << std::endl;
#endif
		return "false";
	}
}

// --------------------------------------------------------

time_t DataBase::fillTm(Day day,Hour hour){
#ifdef __VERBOSE
	std::cout << "[DataBase] DataBase::fillTm(Day,Hour)" << std::endl;
#endif
	struct tm current;
	current.tm_year=day.getYearVal()-YEAR_BEGIN;
	current.tm_mon=day.getMonthVal()-1;
	current.tm_mday=day.getNumberVal();
	current.tm_hour=hour.getHourVal();
	current.tm_min=hour.getMinVal();
	current.tm_sec=hour.getSecVal();
#ifdef __VERBOSE
	std::cout << "    End DataBase::fillTm(Day,Hour)" << std::endl;
#endif
	return mktime(&current);
}
