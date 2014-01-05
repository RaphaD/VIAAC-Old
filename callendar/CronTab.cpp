#include "CronTab.hpp"

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

void CronTab::addToTable(std::string day,std::string hour,std::string name){
#ifdef __VERBOSE
	std::cout << "[CronTab] CronTab::addToTable(std::string,std::string,std::string)" << std::endl;
	std::cout << "    Param : " << day << std::endl;
	std::cout << "    " << hour << std::endl;
	std::cout << "    " << name << std::endl;
#endif

#ifdef __VERBOSE
	std::cout << "    End CronTab::addToTable(std::string,std::string,std::string)"
#endif
}

/*
Event CronTab::getNextAlarm(int ind){

}

Event CronTab::getNextAlarm(Hour* hour,Day* day){

}
*/

bool CronTab::isOlder(struct tm* time,Event* event){
#ifdef __VERBOSE
	std::cout << "[CronTab] CronTab::isOlder(struct tm*,Event*)" << std::endl;
	std::cout << "    Param : " << *event <<std::endl;
#endif
	time_t binz=this->fillTm(event->getBeginDate(),event->getBeginHour());
	if(mktime(time)-binz<0){
#ifdef __VERBOSE
	std::cout << "    1°) True case" << std::endl;
#endif
		return true;
	}else{
#ifdef __VERBOSE
	std::cout << "    2°) False case" << std::endl;
#endif
		return false;
	}
}


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
