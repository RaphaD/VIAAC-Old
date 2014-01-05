#include "Event.hpp"

Event::Event() :
	_id(0),_dBegin(Day()),_hBegin(Hour())
{
}

Event::Event(int ind,Day day,Hour hour) :
	_id(ind),_dBegin(day),_hBegin(hour)
{
}

Event::Event(int ind,std::string day,std::string hour, std::string name) :
	_id(ind),_dBegin(day),_hBegin(hour),_name(name)
{
}

Event::Event(std::vector<std::string> vector)
{
	for(unsigned i(0);i<vector.size();++i){
		if(vector[i][0]=='#'){
			vector[i].erase(0,1);
		}
	}
	this->_id=atoi(vector[0].c_str());
	this->_dBegin=Day(vector[1]);
	this->_hBegin=Hour(vector[2]);
	this->_name=vector[3];
}

Event::~Event(){
}

std::ostream& operator << (std::ostream& flux,Event const& day){
	flux << "ID : " << day.getId() << std::endl;
	flux << "Day begin : " << day.getBeginDate() << std::endl;
	flux << "Hour begin : " << day.getBeginHour() << std::endl;
	flux << "Name : " << day.getName() << std::endl;
	return flux;
}
