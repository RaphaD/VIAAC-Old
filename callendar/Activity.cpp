#include "Activity.hpp"

// --------------------------------------------------------

Activity::Activity() : Event::Event(0,Day(),Hour()),
	_dEnd(Day()),_hEnd(Hour())
{
}

// --------------------------------------------------------

Activity::Activity(std::vector<std::string> vector){
	for(unsigned i(0);i<vector.size();++i){
		if(vector[i][0]=='#'){
			vector[i].erase(0,1);
		}
	}
	for(unsigned i(0);i<vector[5].size();++i){
		if(vector[5][i]=='~'){
			vector[5][i]=' ';
		}
	}
	this->_id=atoi(vector[0].c_str());
	this->_dBegin=Day(vector[1]);
	this->_hBegin=Hour(vector[2]);
	this->_dEnd=Day(vector[3]);
	this->_hEnd=Hour(vector[4]);
	this->_name=vector[5];
}

// --------------------------------------------------------

Activity::Activity(int ind,std::string name,Day& dBegin,Day& dEnd,Hour& hBegin,Hour& hEnd ) : Event::Event(ind,dBegin,hBegin),
	_dEnd(dEnd),_hEnd(hEnd)
{
	this->_name=name;
}

// --------------------------------------------------------

std::ostream& operator <<(std::ostream& flux,Activity const& acti){
	flux << "Date de début :" << acti.getBeginDate() << "\n";
	flux << "Heure de début : " << acti.getBeginHour() << "\n";
	flux << "Date de fin :" << acti.getEndDate() << "\n";
	flux << "Heure de fin : " << acti.getEndHour() << "\n";
	flux << "Activité : " << acti.getName();
	return flux;
}
