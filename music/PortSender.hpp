#ifndef __DEF_PORT_SENDER
#define __DEF_PORT_SENDER

#include <iostream>
#include <vector>
#include <cstdlib>
#include <thread>
#include <fmod/fmod.h>

#include <QObject>
#include <QString>

#include "statFile.hpp"
#include "qextserialport.h"

//#define MEDIAN_VALUE 3.4145444622483727
//#define ECART_TYPE 3.3384111568800794
// V~P(3.4)
// P[V<=x]=0.95 => x=6 => STEP=6/11=0.6
#define STEP 0.545454545454

class PortSender : public QObject{

	Q_OBJECT

	public :
		PortSender(QString portName);

		void sendData(QString toSend);

		QString calculateValue(float spectre[],int size);
		QString determineValue(float an);

		bool isPortOk() const{
			return this->isPortOk_;
		}

		~PortSender();

	private:
		QextSerialPort *port_;
		bool isPortOk_;

};

#endif // __DEF_PORT_SENDER
