#include "CronTab.hpp"

// --------------------------------------------------------

CronTab::CronTab(std::string name) :
	DataBase::DataBase(name)
{
#ifdef __VERBOSE
	std::cout << "[CronTab] CronTab::CronTab(std::string)" << std::endl;
	std::cout << "    Param : " << name << std::endl;
#endif
	if(maj()){
		std::cout << "MAJ de la base de données terminée" << std::endl;
	}else{
		std::cout << "Erreur lors de la MAJ de la base de données" << std::endl;
	}
#ifdef __VERBOSE
	std::cout << "    End CronTab::CronTab(std::string)" << std::endl;
#endif
}

// --------------------------------------------------------

void CronTab::addToTable(Event event){
	/*
#ifdef __VERBOSE
	std::cout << "[CronTab] CronTab::addToTable(std::string,std::string,std::string)" << std::endl;
	std::cout << "    Param : " << day << std::endl;
	std::cout << "    " << hour << std::endl;
	std::cout << "    " << name << std::endl;
#endif
	std::ifstream fichierR(this->_dbName.c_str(),std::ios::in);
	std::vector<Event> activities;
	if(!fichierR){
		std::cout << "Error while opening file " << this->_dbName << std::endl;
	}else{
		std::string contennu;
		Event actiC;
		bool stop(false);
		if (this->isRepetitive(event)){
			activities.push_back(event);
			while(std::getline(fichierR,contennu))
				activities.push_back(Event(split(contennu,' ')));
		}else{
			while((std::getline(fichierR,contennu)) && !stop){
#ifdef __VERBOSE
	std::cout << "    Loop 1) Current line : " << contennu << std::endl;
#endif
				std::vector<std::string> inter=split(contennu,' ');
				actiC=Event(inter);
				if(this->isSmaller(actiP,actiC)){
					stop=true;
				}else{
					activities.push_back(actiC);
				}
			}
		}
#ifdef __VERBOSE
	std::cout << "    2°) Place found before : " << actiC << std::endl;
#endif
		activities.push_back(actiP);
		if(contennu!=""){
			activities.push_back(actiC);
			activities.push_back(Event(split(contennu,' ')));
		}
#ifdef __VERBOSE
	std::cout << "    3°) Filling the rest" << std::endl;
#endif
		while(std::getline(fichierR,contennu)){
			activities.push_back(Event(split(contennu,' ')));
		}
	}
	fichierR.close();
	std::ofstream fichierW(this->_dbName.c_str(), std::ios::out | std::ios::trunc);
	for(unsigned i(0);i<activities.size();++i){
#ifdef __VERBOSE
	std::cout << "    Loop 2) writting file : " << activities[i] << std::endl;
#endif
		this->writeInFile(i,&activities[i],fichierW);
	}
#ifdef __VERBOSE
	std::cout << "    End CronTab::addToTable(std::string,std::string,std::string)" << std::endl;
#endif
	*/
}

// --------------------------------------------------------

time_t CronTab::getNextAlarm(int ind){
	std::ifstream fichierR(this->_dbName.c_str(),std::ios::in);
	std::string contennu;
	std::getline(fichierR,contennu);
	Event current=Event(split(contennu,' '));
	time_t smallerT;
	if (this->isRepetitive(current)){
		smallerT=this->getNextIte(current);
	}else{
		smallerT=this->fillTm(current.getBeginDate(),current.getBeginHour());
	}
	while(this->isRepetitive(current) && std::getline(fichierR,contennu)){
		current=Event(split(contennu,' '));
		if(this->isRepetitive(current)){
			if(this->getNextIte(current)<smallerT){
				smallerT=this->getNextIte(current);
			}
		}
	}
	if(std::getline(fichierR,contennu)){
		current=Event(split(contennu,' '));
		if(this->fillTm(current.getBeginDate(),current.getBeginHour())<smallerT){
			smallerT=this->fillTm(current.getBeginDate(),current.getBeginHour());
		}
	}
	fichierR.close();

	return smallerT;
}

// --------------------------------------------------------

time_t CronTab::getNextIte(Event& event){
	struct tm* time=currentTime();
	if(event.getBeginDate().getYearVal()==-1){
		++time->tm_year;
	}else if(event.getBeginDate().getMonthVal()==-1){
		++time->tm_mon;
	}else if(event.getBeginDate().getNumberVal()==-1){
		++time->tm_yday;
	}else if(event.getBeginHour().getHourVal()==-1){
		++time->tm_hour;
	}else if(event.getBeginHour().getMinVal()==-1){
		++time->tm_min;
	}else if(event.getBeginHour().getSecVal()==-1){
		++time->tm_sec;
		++time->tm_sec;
	}
	return mktime(time);
}

// --------------------------------------------------------

bool CronTab::isRepetitive(Event &event){
	return ((event.getBeginDate().getNumberVal()==-1 ) || (event.getBeginDate().getMonthVal()==-1 ) ||
				(event.getBeginDate().getYearVal()==-1) || (event.getBeginHour().getHourVal()==-1) ||
				(event.getBeginHour().getMinVal()==-1) || (event.getBeginHour().getSecVal()==-1));
}

bool CronTab::isOlder(struct tm* time,Event* event){
#ifdef __VERBOSE
	std::cout << "[CronTab] CronTab::isOlder(struct tm*,Event*)" << std::endl;
	std::cout << "    Param : " << *event <<std::endl;
#endif
	if(this->isRepetitive(*event)){
#ifdef __VERBOSE
	std::cout << "    1°) True case" << std::endl;
#endif
		return true;
	}
	time_t binz=this->fillTm(event->getBeginDate(),event->getBeginHour());
	if(mktime(time)-binz<0){
#ifdef __VERBOSE
	std::cout << "    2°) True case" << std::endl;
#endif
		return true;
	}else{
#ifdef __VERBOSE
	std::cout << "    3°) False case" << std::endl;
#endif
		return false;
	}
}

// --------------------------------------------------------

void CronTab::addToVector(std::vector<Event*>* events,std::vector<std::string>* inter){
#ifdef __VERBOSE
	std::cout << "[CronTab] CronTab::addToVector(std::vector<Event*>* events,std::vector<std::string>* inter)" << std::endl;
#endif
	Event* toPush=new Event(*inter);
	events->push_back(toPush);
}

void CronTab::writeInFile(int ind,Event *event, std::ofstream &flux){
#ifdef __VERBOSE
	std::cout << "[CronTab] CronTab::writeInFile(int,Event*,std::ofstream&)" << std::endl;
	std::cout << "    Param : " << ind << std::endl;
	std::cout << "    " << *event << std::endl;
#endif
	flux << ind << " #";
	flux << event->getBeginDate() << " #";
	flux << event->getBeginHour() << " #";
	flux << event->getName() << " # \n";
#ifdef __VERBOSE
	std::cout << "End CronTab::writeInFile(int,Event*,std::ofstream&)" << std::endl;
#endif
}
