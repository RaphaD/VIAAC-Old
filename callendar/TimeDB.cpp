#include "TimeDB.hpp"

// jockey-backend

TimeDB::TimeDB(std::string DBName) :
	DataBase::DataBase(DBName)
{
#ifdef __VERBOSE
	std::cout << "[TimeDB] TimeDB::TimeDB(std::string)" << std::endl;
#endif
	if(maj()){
		std::cout << "MAJ de la base de données terminée" << std::endl;
	}else{
		std::cout << "Erreur lors de la MAJ de la base de données" << std::endl;
	}
}

std::vector<Activity> TimeDB::search(Day& day){
#ifdef __VERBOSE
	std::cout << "[TimeDB] TimeDB::search(Day&)" << std::endl;
	std::cout << "    Param : " << day << std::endl;
	std::cout << "    Reading database" << std::endl;
#endif
	/* Ouverture et lecture du fichier */
	std::ifstream fichierR(this->_dbFile.c_str(),std::ios::in);
	std::vector<Activity> activities;
	Hour h;
	Hour h2(23,59,59);
	time_t comp1=this->fillTm(day,h);
	time_t comp2=this->fillTm(day,h2);
	if(!fichierR){
		std::cout << "Error while opening file " << this->_dbFile << std::endl;
	}else{
		std::string contennu;
		bool areOlder(false);
		while((std::getline(fichierR,contennu)) && (!areOlder)){
			std::vector<std::string> inter=split(contennu,' ');
			Activity acti=Activity(inter);
			time_t begA=this->fillTm(acti.getBeginDate(),acti.getBeginHour());
			time_t endA=this->fillTm(acti.getEndDate(),acti.getEndHour());
			//si fin de l'event dans day
#ifdef __VERBOSE
	std::cout << "    Loop) Current line : " << contennu << std::endl;
#endif
			if((difftime(begA,comp1)<0 && difftime(endA,comp1)>0) ||
					//Si event entièrement dans day
					(difftime(begA,comp1)>=0 && difftime(endA,comp2)<=0) ||
					//Si début de l'event dans day
					(difftime(begA,comp2)<0 && difftime(endA,comp2)>=0)){
				activities.push_back(acti);
			}else if(difftime(begA,comp2)>=0){
#ifdef __VERBOSE
				std::cout << "    2°) Stop with : " << acti << std::endl;
#endif
				areOlder=true;
			}
		}
	}
#ifdef __VERBOSE
	std::cout << "    3°) Closing file" << std::endl;
	std::cout << "    End TimeDB::search(Day&)" << std::endl;
#endif
	fichierR.close();
	return activities;
}

std::vector<Activity> TimeDB::search(Day& day,Hour& hour){
#ifdef __VERBOSE
	std::cout << "[TimeDB] TimeDB::search(Day&,Hour&)" << std::endl;
	std::cout << "    Param : " << day << "\n" << hour << std::endl;
#endif
	/* Ouverture et lecture du fichier */
	std::ifstream fichierR(this->_dbFile.c_str(),std::ios::in);
	std::vector<Activity> activities;
	time_t comp=this->fillTm(day,hour);
	if(!fichierR){
		std::cout << "Error while opening file " << this->_dbFile << std::endl;
	}else{
		std::string contennu;
		bool areOlder(false);
		while((std::getline(fichierR,contennu)) && (!areOlder)){
#ifdef __VERBOSE
	std::cout << "    Loop) Current : " << contennu << std::endl;
#endif
			std::vector<std::string> inter=split(contennu,' ');
			Activity acti=Activity(inter);
			time_t begA=this->fillTm(acti.getBeginDate(),acti.getBeginHour());
			time_t endA=this->fillTm(acti.getEndDate(),acti.getEndHour());
			if(difftime(comp,begA)>=0 && difftime(comp,endA)<0){
				activities.push_back(acti);
			}else if(difftime(comp,begA)<0){
				areOlder=true;
			}
		}
	}
#ifdef __VERBOSE
	std::cout << "    3°) Closing file" << std::endl;
	std::cout << "    End TimeDB::search(Day&,Hour&)" << std::endl;
#endif
	fichierR.close();
	return activities;
}

void TimeDB::add(Activity actiP){
#ifdef __VERBOSE
	std::cout << "[TimeDB] TimeDB::add(Activity)" << std::endl;
	std::cout << "    Param : " << actiP << std::endl;
#endif
	std::ifstream fichierR(this->_dbFile.c_str(),std::ios::in);
	std::vector<Activity> activities;
	if(!fichierR){
		std::cout << "Error while opening file " << this->_dbFile << std::endl;
	}else{
		std::string contennu;
		Activity actiC;
		bool stop(false);
		while((std::getline(fichierR,contennu)) && !stop){
#ifdef __VERBOSE
	std::cout << "    Loop 1) Current line : " << contennu << std::endl;
#endif
			std::vector<std::string> inter=split(contennu,' ');
			actiC=Activity(inter);
			if(this->isSmaller(actiP,actiC)){
				stop=true;
			}else{
				activities.push_back(actiC);
			}
		}
#ifdef __VERBOSE
	std::cout << "    2°) Place found before : " << actiC << std::endl;
#endif
		activities.push_back(actiP);
		if(contennu!=""){
			activities.push_back(actiC);
			activities.push_back(Activity(split(contennu,' ')));
		}
#ifdef __VERBOSE
	std::cout << "    3°) Filling the rest" << std::endl;
#endif
		while(std::getline(fichierR,contennu)){
			activities.push_back(Activity(split(contennu,' ')));
		}
	}
	fichierR.close();
	std::ofstream fichierW(this->_dbFile.c_str(), std::ios::out | std::ios::trunc);
	for(unsigned i(0);i<activities.size();++i){
#ifdef __VERBOSE
	std::cout << "    Loop 2) writting file : " << activities[i] << std::endl;
#endif
		this->writeInFile(i,&activities[i],fichierW);
	}
#ifdef __VERBOSE
	std::cout << "    End TimeDB::add(Activity)" << std::endl;
#endif
}

bool TimeDB::isSmaller(Activity const& acti1,Activity const& acti2){
#ifdef __VERBOSE
	std::cout << "[TimeDB] TimeDB::isSmaller(Activity&,Activity&)" << std::endl;
	std::cout << "    Param : " << acti1 << "\n" << acti2 << std::endl;
#endif
	time_t end1=this->fillTm(acti1.getEndDate(),acti1.getEndHour());
	time_t end2=this->fillTm(acti2.getEndDate(),acti2.getEndHour());
	if(this->isEventSmaller(acti1,acti2)=="true"){
#ifdef __VERBOSE
	std::cout << "    1°) Case true" << std::endl;
#endif
		return true;
	}else if(this->isEventSmaller(acti1,acti2)=="same"){
		if(difftime(end1,end2)<0){
#ifdef __VERBOSE
	std::cout << "    2°) Case true" << std::endl;
#endif
			return true;
		}else if(difftime(end1,end2)==0){
			std::vector<std::string> names;
			names.push_back(acti1.getName());
			names.push_back(acti2.getName());
			std::sort(names.begin(),names.end());
			if(names[0]==acti1.getName()){
#ifdef __VERBOSE
	std::cout << "    3°) Case true" << std::endl;
#endif
				return true;
			}
		}
	}
#ifdef __VERBOSE
	std::cout << "    4°) Case false" << std::endl;
#endif
	return false;
}

bool TimeDB::isOlder(struct tm* time,Event* event){
#ifdef __VERBOSE
	std::cout << "[TimeDB] TimeDB::isOlder(struct tm*,Event*)" << std::endl;
	std::cout << "    Param : aTime?" << "\n" << *event << std::endl;
#endif
	Activity* acti=dynamic_cast<Activity*>(event);
	time_t end=this->fillTm(acti->getBeginDate(),acti->getBeginHour());
	if(mktime(time)-end<0){
#ifdef __VERBOSE
	std::cout << "    1°) Case true" << std::endl;
#endif
		return true;
	}else{
#ifdef __VERBOSE
	std::cout << "    2°) Case false" << std::endl;
#endif
		return false;
	}
}

void TimeDB::addToVector(std::vector<Event*>* events,std::vector<std::string>* inter){
#ifdef __VERBOSE
	std::cout << "[TimeDB] TimeDB::addToVector(std::vector<Event*>*,std::vector<std::string>*)" << std::endl;
#endif
	Activity* acti=new Activity(*inter);
	std::cout << "    acti : " << *acti << std::endl;
	events->push_back(acti);
}

void TimeDB::writeInFile(int ind,Event *event,std::ofstream& flux){
	Activity* acti=dynamic_cast<Activity*>(event);
#ifdef __VERBOSE
	std::cout << "[TimeDB] TimeDB::writeInFile(Event*,std::ofstream&)" << std::endl;
	std::cout << "    Param : " << *event << std::endl;
	std::cout << "    Acti : " << *acti << std::endl;
#endif
	flux << ind << " #";
	flux << acti->getBeginDate() << " #";
	flux << acti->getBeginHour() << " #";
	flux << acti->getEndDate() << " #";
	flux << acti->getEndHour() << " #";
	flux << acti->getName() << " # \n";
#ifdef __VERBOSE
	std::cout << "    End TimeDB::writeInFile(Event*,std::ofstream&)" << std::endl;
#endif
}
