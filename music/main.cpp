#include <QApplication>
#include <QString>

#include <exception>
#include <vector>

#include "PortSender.hpp"
#include "MusicMaker.hpp"
#include "libTreater.cpp"

#define PORT "/dev/ttyACM0"

#define __STATISTICS

#ifdef __STATISTICS
	#define STAT_FILE "STAT_FILE.txt"
	long double turn(0);
	long unsigned number_turn(0);
#endif

int main(){
	//QApplication app(argc, argv);

	std::vector<std::string> res;
	res=getNames(MUSIC_LIB);

	QString portName = QString(PORT);  // update this to use your port of choice
	PortSender Listener(portName); // signals get hooked up internally
	MusicMaker Music(&Listener,res);
	Music.mainLoop();

	return 0;
}
