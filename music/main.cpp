#include <QString>

#include <exception>
#include <vector>

#include "PortSender.hpp"
#include "MusicMaker.hpp"
#include "libTreater.cpp"

#define PORT "/dev/ttyACM0"
#define MUSIC_LIB "./music/"

int main(){
    std::vector<std::string> res;
    res=getNames(MUSIC_LIB);

    QString portName = QString(PORT);  // update this to use your port of choice
    PortSender Listener(portName); // signals get hooked up internally
    MusicMaker Music(&Listener,res);
    Music.mainLoop();

    return 0;
}
