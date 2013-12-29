#include "TimeDB.hpp"

TimeDB::TimeDB(std::string DBName) :
	_dbFile(DBName)
{
	if(this->maj()){
		std::cout << "MAJ de la base de données terminée" << std::endl;
	}else{
		std::cout << "Erreur lors de la MAJ de la base de données" << std::endl;
	}
}

bool TimeDB::maj(){
	/* Ouverture et lecture du fichier */
	std::ifstream fichierR(this->_dbFile.c_str(),std::ios::in);

	std::vector<Activity> activities;
	if(!fichierR){
		std::cout << "Error while opening file " << this->_dbFile << std::endl;
		return false;
	}else{
		std::string contennu;
		while(std::getline(fichierR,contennu)){
			std::vector<std::string> inter=split(contennu,' ');
			activities.push_back(Activity(inter));
		}
	}
	fichierR.close();

	/* Ouverture et écriture dans le fichier */
	std::ofstream fichierW(this->_dbFile.c_str(), std::ios::out | std::ios::trunc);

	struct tm* time=currentTime();
	for(unsigned i(0);i<activities.size();++i){
		time_t current=this->fillTm(activities[i].getEndDate(),activities[i].getEndHour());
		if(difftime(mktime(time),current)<0){
			this->writeInFile(activities[i],fichierW);
		}
	}
	fichierW.close();
	return true;
}

std::vector<Activity> TimeDB::search(Day& day){
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
			if((difftime(begA,comp1)<0 && difftime(endA,comp1)>0) ||
					//Si event entièrement dans day
					(difftime(begA,comp1)>=0 && difftime(endA,comp2)<=0) ||
					//Si début de l'event dans day
					(difftime(begA,comp2)<0 && difftime(endA,comp2)>=0)){
				activities.push_back(acti);
			}else if(difftime(begA,comp2)>=0){
				areOlder=true;
			}
		}
	}
	fichierR.close();
	return activities;
}

std::vector<Activity> TimeDB::search(Day& day,Hour& hour){
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
	fichierR.close();
	return activities;
}

void TimeDB::add(Activity actiP){
	std::ifstream fichierR(this->_dbFile.c_str(),std::ios::in);
	std::vector<Activity> activities;
	if(!fichierR){
		std::cout << "Error while opening file " << this->_dbFile << std::endl;
	}else{
		std::string contennu;
		Activity actiC;
		bool stop(false);
		while((std::getline(fichierR,contennu)) && !stop){
			std::vector<std::string> inter=split(contennu,' ');
			actiC=Activity(inter);
			if(this->isSmaller(actiP,actiC)){
				stop=true;
			}else{
				activities.push_back(actiC);
			}
		}
		std::cout << contennu << std::endl;
		std::cout << actiP << std::endl;
		activities.push_back(actiP);
		if(contennu!=""){
			activities.push_back(actiC);
			activities.push_back(Activity(split(contennu,' ')));
		}
		while(std::getline(fichierR,contennu)){
			activities.push_back(Activity(split(contennu,' ')));
		}
	}
	fichierR.close();
	std::ofstream fichierW(this->_dbFile.c_str(), std::ios::out | std::ios::trunc);
	for(unsigned i(0);i<activities.size();++i){
		this->writeInFile(activities[i],fichierW);
	}
}

time_t TimeDB::fillTm(Day day,Hour hour){
	struct tm current;
	current.tm_year=day.getYearVal()-YEAR_BEGIN;
	current.tm_mon=day.getMonthVal()-1;
	current.tm_mday=day.getNumberVal();
	current.tm_hour=hour.getHourVal();
	current.tm_min=hour.getMinVal();
	current.tm_sec=hour.getSecVal();
	return mktime(&current);
}

bool TimeDB::isSmaller(Activity const& acti1,Activity const& acti2){
	time_t beg1=this->fillTm(acti1.getBeginDate(),acti1.getBeginHour());
	time_t end1=this->fillTm(acti1.getEndDate(),acti1.getEndHour());
	time_t beg2=this->fillTm(acti2.getBeginDate(),acti2.getBeginHour());
	time_t end2=this->fillTm(acti2.getEndDate(),acti2.getEndHour());
	if(difftime(beg1,beg2)<0){
		return true;
	}else if(difftime(beg1,beg2)==0){
		if(difftime(end1,end2)<0){
			return true;
		}else if(difftime(end1,end2)==0){
			std::vector<std::string> names;
			names.push_back(acti1.getName());
			names.push_back(acti2.getName());
			std::sort(names.begin(),names.end());
			if(names[0]==acti1.getName()){
				return true;
			}
		}
	}
	return false;
}

void TimeDB::writeInFile(Activity& acti,std::ofstream& flux){
	flux << acti.getBeginDate() << " #";
	flux << acti.getBeginHour() << " #";
	flux << acti.getEndDate() << " #";
	flux << acti.getEndHour() << " #";
	flux << acti.getName() << " # \n";
}
