#include "Activity.hpp"

Activity::Activity() : Event::Event(0,Day(),Hour()),
	_dEnd(Day()),_hEnd(Hour())
{
#ifdef __VERBOSE

#endif
}

Activity::Activity(std::vector<std::string> vector){
#ifdef __VERBOSE

#endif
	for(unsigned i(0);i<vector.size();++i){
		if(vector[i][0]=='#'){
			vector[i].erase(0,1);
		}
	}
#ifdef __VERBOSE

#endif
	for(unsigned i(0);i<vector[5].size();++i){
		if(vector[5][i]=='~'){
			vector[5][i]=' ';
		}
	}
#ifdef __VERBOSE

#endif
	this->_id=atoi(vector[0].c_str());
	this->_dBegin=Day(vector[1]);
	this->_hBegin=Hour(vector[2]);
	this->_dEnd=Day(vector[3]);
	this->_hEnd=Hour(vector[4]);
	this->_name=vector[5];
#ifdef __VERBOSE
	std::cout << *this << std::endl;
#endif
}

Activity::Activity(int ind,std::string name,Day& dBegin,Day& dEnd,Hour& hBegin,Hour& hEnd ) : Event::Event(ind,dBegin,hBegin),
	_dEnd(dEnd),_hEnd(hEnd)
{
	this->_name=name;
#ifdef __VERBOSE

#endif
}

std::ostream& operator <<(std::ostream& flux,Activity const& acti){
#ifdef __VERBOSE

#endif
	flux << "Date de début :" << acti.getBeginDate() << "\n";
	flux << "Heure de début : " << acti.getBeginHour() << "\n";
	flux << "Date de fin :" << acti.getEndDate() << "\n";
	flux << "Heure de fin : " << acti.getEndHour() << "\n";
	flux << "Activité : " << acti.getName();
#ifdef __VERBOSE

#endif
	return flux;
}
