#ifndef __DEF_PORT_SENDER
#define __DEF_PORT_SENDER

#include <iostream>
#include <vector>
#include <cstdlib>
#include <thread>
#include <fmod/fmod.h>

#include <QApplication>
#include <QObject>
#include <QString>

#include "qextserialport.h"


class PortSender : public QObject{

	Q_OBJECT

	public :
		PortSender(QString& portName);

		void sendData(QString toSend);

		QString calculateValue(float spectre[],int size);
		QString determineValue(float an);

		bool isPortOk() const{
			return this->_port;
		}

		~PortSender();

	private:
		QextSerialPort *_port;
		bool _isPortOk;

};

#endif // __DEF_PORT_SENDER
