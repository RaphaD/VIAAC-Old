#include "PortHandler.hpp"

PortHandler::PortHandler(QString portName) :
    isPortOk_(true)
{
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

    try{
        //on démarre !
        this->port_->open(QextSerialPort::ReadWrite);
    }catch(std::exception const& e){
        std::cout << "Port sélectionné incorrect !" << std::endl;
        this->isPortOk_=false;
    }
}

PortHandler::PortHandler(PortHandler const& port) :
    port_(port.getPort()),isPortOk_(port.isPortOk())
{
}

void PortHandler::sendData(QString toSend){
    if(this->port_ != 0)
        this->port_->write(toSend.toStdString().c_str());
}
/*
void PortHandler::sendData(std::string toSend){
    if(this->port_!=0)
        this->port_->write(toSend.c_str());
}
*/
PortHandler::~PortHandler(){
#ifdef __STATISTICS
    writeStat(turn,number_turn);
#endif
    delete this->port_;
}