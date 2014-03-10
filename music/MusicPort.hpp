#ifndef __DEF_MUSIC_PORT
#define __DEF_MUSIC_PORT

#include <iostream>
#include <vector>
#include <cstdlib>
#include <fmod/fmod.h>
#include <exception>
#include <fstream>

#include <QString>

#include "qextserialport.h"
#include "statFile.hpp"
#include "../PortHandler.hpp"

//#define MEDIAN_VALUE 3.4145444622483727
//#define ECART_TYPE 3.3384111568800794
// V~P(3.4)
// P[V<=x]=0.95 => x=6 => STEP=6/11=0.6
#define STEP 0.545454545454

class MusicPort : public PortHandler
{
    public :
    	MusicPort(PortHandler* port);
        MusicPort(QString portName);

        QString calculateValue(float spectre[],int size);
        QString determineValue(float an);

      	~MusicPort();
};

#endif // __DEF_MUSIC_PORT
