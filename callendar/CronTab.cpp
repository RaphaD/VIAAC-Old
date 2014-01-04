#include "CronTab.hpp"

CronTab::CronTab(std::string name) :
	DataBase::DataBase(name)
{
	if(maj()){
		std::cout << "MAJ de la base de données terminée" << std::endl;
#ifdef __VERBOSE

#endif
	}else{
		std::cout << "Erreur lors de la MAJ de la base de données" << std::endl;
	}
#ifdef __VERBOSE

#endif
}

void CronTab::addToTable(std::string day,std::string hour,std::string name){
#ifdef __VERBOSE

#endif

#ifdef __VERBOSE

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

#endif
	time_t binz=this->fillTm(event->getBeginDate(),event->getBeginHour());
	if(mktime(time)-binz<0){
#ifdef __VERBOSE

#endif
		return true;
	}else{
#ifdef __VERBOSE

#endif
		return false;
	}
}


void CronTab::addToVector(std::vector<Event*>* events,std::vector<std::string>* inter){
#ifdef __VERBOSE
	std::cout << "[CronTab] CronTab::addToVector(std::vector<Event*>* events,std::vector<std::string>* inter)" << std::endl;
#endif
	Event* toPush=new Event(*inter);
	std::cout << "    " << *toPush << std::endl;
	events->push_back(toPush);
}

void CronTab::writeInFile(int ind,Event *event, std::ofstream &flux){
#ifdef __VERBOSE

#endif
	flux << ind << " #";
	flux << event->getBeginDate() << " #";
	flux << event->getBeginHour() << " #";
	flux << event->getName() << " # \n";
#ifdef __VERBOSE

#endif
}
