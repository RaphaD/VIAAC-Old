#include "Activity.hpp"

Activity::Activity() :
	_name("a"), _dBegin(Day()),_dEnd(Day()),_hBegin(Hour()),_hEnd(Hour())
{
}

Activity::Activity(std::vector<std::string> vector){
	for(unsigned i(0);i<vector.size();++i){
		if(vector[i][0]=='#'){
			vector[i].erase(0,1);
		}
	}

	this->_dBegin=Day(vector[0]);
	this->_hBegin=Hour(vector[1]);
	this->_dEnd=Day(vector[2]);
	this->_hEnd=Hour(vector[3]);
	for(unsigned i(0);i<vector[4].size();++i){
		if(vector[4][i]=='~'){
			vector[4][i]=' ';
		}
	}
	this->_name=vector[4];
}

Activity::Activity(std::string name,Day& dBegin,Day& dEnd,Hour& hBegin,Hour& hEnd ) :
	_name(name), _dBegin(dBegin),_dEnd(dEnd),_hBegin(hBegin),_hEnd(hEnd)
{
}

std::ostream& operator <<(std::ostream& flux,Activity const& acti){
	flux << "Date de début :" << acti.getBeginDate() << "\n";
	flux << "Heure de début : " << acti.getBeginHour() << "\n";
	flux << "Date de fin :" << acti.getEndDate() << "\n";
	flux << "Heure de fin : " << acti.getEndHour() << "\n";
	flux << "Activité : " << acti.getName();
	return flux;
}
