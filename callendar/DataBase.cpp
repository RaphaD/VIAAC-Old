#include "DataBase.hpp"

DataBase::DataBase(std::string name) : _dbName(name)
{
}

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
			std::cout << "    Line read : " << contennu << std::endl;
#endif
			std::vector<std::string> inter=split(contennu,' ');
			this->addToVector(&events,&inter);
		}
	}
#ifdef __VERBOSE
	std::cout << "    Closing callendar database" << std::endl;
#endif
	fichierR.close();

	/* Ouverture et écriture dans le fichier */
#ifdef __VERBOSE
	std::cout << "    Opening " << this->_dbName << " in writting mode" << std::endl;
#endif
	std::ofstream fichierW(this->_dbName.c_str(), std::ios::out | std::ios::trunc);

	struct tm* time=currentTime();
	int count(0);
	for(unsigned i(0);i<events.size();++i){
		if(this->isOlder(time,events[i])){
#ifdef __VERBOSE
			std::cout << "Written in file : " << events[i] << std::endl;
#endif
			this->writeInFile(count,events[i],fichierW);
			++count;
		}
	}
#ifdef __VERBOSE
	std::cout << "Closing callendar database" << std::endl;
#endif
	fichierW.close();
	return true;
}

void DataBase::removeFromTable(int id){
#ifdef __VERBOSE

#endif
	std::ifstream fichierR(this->_dbName.c_str(),std::ios::in);
	std::vector<Event*> events;
	if(!fichierR){
		std::cout << "Error while opening file " << this->_dbName << std::endl;
	}else{
#ifdef __VERBOSE

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

#endif
		while(std::getline(fichierR,contennu)){
			std::vector<std::string> inter=split(contennu,' ');
			this->addToVector(&events,&inter);
		}
	}
#ifdef __VERBOSE

#endif
	fichierR.close();
	std::ofstream fichierW(this->_dbName.c_str(), std::ios::out | std::ios::trunc);
	for(unsigned i(0);i<events.size();++i){
#ifdef __VERBOSE

#endif
		this->writeInFile(i,events[i],fichierW);
	}
}

std::string DataBase::isEventSmaller(Event const& first, Event const& second){
#ifdef __VERBOSE

#endif
		time_t beg1=this->fillTm(first.getBeginDate(),first.getBeginHour());
		time_t beg2=this->fillTm(second.getBeginDate(),second.getBeginHour());
		if(difftime(beg1,beg2)<0){
#ifdef __VERBOSE

#endif
			return "true";
		}else if(difftime(beg1,beg2)==0){
#ifdef __VERBOSE

#endif
			return "same";
		}else{
#ifdef __VERBOSE

#endif
			return "false";
		}
}

time_t DataBase::fillTm(Day day,Hour hour){
#ifdef __VERBOSE

#endif
	struct tm current;
	current.tm_year=day.getYearVal()-YEAR_BEGIN;
	current.tm_mon=day.getMonthVal()-1;
	current.tm_mday=day.getNumberVal();
	current.tm_hour=hour.getHourVal();
	current.tm_min=hour.getMinVal();
	current.tm_sec=hour.getSecVal();
#ifdef __VERBOSE

#endif
	return mktime(&current);
}
