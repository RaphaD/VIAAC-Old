#include "MusicPort.hpp"

#ifdef __STATISTICS
long double turn(0);
long unsigned number_turn(0);
#endif //__STATISTICS

MusicPort::MusicPort(PortHandler* port) : 
    PortHandler(*port)
{
}

MusicPort::MusicPort(QString portName) :
    PortHandler(portName)
{
#ifdef __STATISTICS
    openStat(turn,number_turn);
#endif
}

QString MusicPort::calculateValue(float spectre[],int size){
    float res(0);
    for(int i(0);i<size-1;++i){
        res+=spectre[i];
#ifdef __STATISTICS
    turn+=((res-MEDIAN_VALUE)**2);
    ++number_turn;
#endif
    }
    return this->determineValue(res);
}

QString MusicPort::determineValue(float an){
    QString value("0");
    if(an<=STEP){
        value="0";
    }else if(an<=2*STEP){
        value="1";
    }else if(an<=3*STEP){
        value="2";
    }else if(an<=4*STEP){
        value="3";
    }else if(an<=5*STEP){
        value="4";
    }else if(an<=6*STEP){
        value="5";
    }else if(an<=7*STEP){
        value="6";
    }else if(an<=8*STEP){
        value="7";
    }else if(an<=9*STEP){
        value="8";
    }else if(an<=10*STEP){
        value="9";
    }else if(an<=11*STEP){
        value="A";
    }
    return value;
}

MusicPort::~MusicPort(){
#ifdef __STATISTICS
    writeStat(turn,number_turn);
#endif
}
