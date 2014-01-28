#include "PortSender.hpp"

#ifdef __STATISTICS
long double turn(0);
long unsigned number_turn(0);
#endif //__STATISTICS

#include <exception>
#include <thread>
#include <fstream>

PortSender::PortSender(QString portName) : isPortOk_(true){
	//on commence par créer l'objet port série
	this->port_ = new QextSerialPort();

	//on règle le port utilisé (sélectionné dans la liste déroulante)
	this->port_->setPortName(portName);

	//on règle la vitesse utilisée
	this->port_->setBaudRate(BAUD9600);

	//quelques règlages pour que tout marche bien
	this->port_->setParity(PAR_NONE);//parité
	this->port_->setStopBits(STOP_1);//nombre de bits de stop
	this->port_->setDataBits(DATA_8);//nombre de bits de données
	this->port_->setFlowControl(FLOW_OFF);//pas de contrôle de flux

#ifdef __STATISTICS
	openStat(turn,number_turn);
#endif

	try{
		//on démarre !
		this->port_->open(QextSerialPort::ReadWrite);
	}catch(std::exception const& e){
		std::cout << "Port sélectionné incorrect !" << std::endl;
		this->isPortOk_=false;
	}
}

QString PortSender::calculateValue(float spectre[],int size){
	float res(0);
	for(int i(0);i<size;++i){
		res+=spectre[i];
#ifdef __STATISTICS
	turn+=((res-MEDIAN_VALUE)**2);
	++number_turn;
#endif
	}
	return this->determineValue(res);
}

/*
QString PortSender::determineValue(float an){
	QString value;
	if(an>=MEDIAN_VALUE+5*STEP){
		value="0";
	}else if(an>=MEDIAN_VALUE+4*STEP){
		value="1";
	}else if(an>=MEDIAN_VALUE+3*STEP){
		value="2";
	}else if(an>=MEDIAN_VALUE+2*STEP){
		value="3";
	}else if(an>=MEDIAN_VALUE+STEP){
		value="4";
	}else if(an>=MEDIAN_VALUE){
		value="5";
	}else if(an>=MEDIAN_VALUE-STEP){
		value="6";
	}else if(an>=MEDIAN_VALUE-2*STEP){
		value="7";
	}else if(an>=MEDIAN_VALUE-3*STEP){
		value="8";
	}else if(an>=MEDIAN_VALUE-4*STEP){
		value="9";
	}else{
		value="A";
	}
	return value;
}
*/

QString PortSender::determineValue(float an){
	QString value("A");
	if(an<=STEP){
		value="A";
	}else if(an<=2*STEP){
		value="9";
	}else if(an<=3*STEP){
		value="8";
	}else if(an<=4*STEP){
		value="7";
	}else if(an<=5*STEP){
		value="6";
	}else if(an<=6*STEP){
		value="5";
	}else if(an<=7*STEP){
		value="4";
	}else if(an<=8*STEP){
		value="3";
	}else if(an<=9*STEP){
		value="2";
	}else if(an<=10*STEP){
		value="1";
	}else if(an<=11*STEP){
		value="0";
	}
	return value;
}

void PortSender::sendData(QString toSend){
	if(this->port_ != 0)
		this->port_->write(toSend.toStdString().c_str());
}

PortSender::~PortSender(){
#ifdef __STATISTICS
	writeStat(turn,number_turn);
#endif
	delete this->port_;
}
