#ifndef __DEF_PORT_HANDLER
#define __DEF_PORT_HANDLER

#include <iostream>
#include <exception>
#include <fstream>
#include <string>

#include "qextserialport.h"

class PortHandler
{
    public :
        PortHandler(QString portName);
        PortHandler(PortHandler const& port);

        void sendData(QString toSend);

        QextSerialPort* getPort() const {return this->port_;}
        bool isPortOk() const{ return this->isPortOk_; }

        ~PortHandler();

    private:
        QextSerialPort *port_;
        bool isPortOk_;
};

#endif //__DEF_PORT_HANDLER