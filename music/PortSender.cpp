#include "PortSender.hpp"

#include <exception>
#include <thread>
#include <fstream>

#define MEDIAN_VALUE 3.8533
#define STEP 0.6

PortSender::PortSender(QString &portName) : _isPortOk(true){
	//on commence par créer l'objet port série
	this->_port = new QextSerialPort();

	//on règle le port utilisé (sélectionné dans la liste déroulante)
	this->_port->setPortName(portName);

	//on règle la vitesse utilisée
	this->_port->setBaudRate(BAUD9600);

	//quelques règlages pour que tout marche bien
	this->_port->setParity(PAR_NONE);//parité
	this->_port->setStopBits(STOP_1);//nombre de bits de stop
	this->_port->setDataBits(DATA_8);//nombre de bits de données
	this->_port->setFlowControl(FLOW_OFF);//pas de contrôle de flux

	try{
		//on démarre !
		this->_port->open(QextSerialPort::ReadWrite);
	}catch(std::exception const& e){
		std::cout << "Port sélectionné incorrect !" << std::endl;
		this->_isPortOk=false;
	}
}

QString PortSender::calculateValue(float spectre[],int size){
	float res(0);
	for(int i(0);i<size;++i){
		res+=spectre[i];
	#ifdef __STATISTICS
		turn+=res;
	#endif
	}
	return this->determineValue(res);
}

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

void PortSender::sendData(QString toSend){
	if(this->_port != 0)
		this->_port->write(toSend.toStdString().c_str());
}

PortSender::~PortSender(){
	delete this->_port;
}
