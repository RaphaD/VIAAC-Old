#ifndef __MUSIC_MAKER_HPP
#define __MUSIC_MAKER_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <thread>
#include <fmod/fmod.h>

#include <QApplication>
#include <QObject>
#include <QString>

#include "PortSender.hpp"
#include "Song.hpp"

#define TAILLE_SPECTRE 512
#define REFRESH 21500

class MusicMaker : public QObject{

	Q_OBJECT

	public :
		MusicMaker(PortSender* port,std::vector<std::string>& res);

		void nextSong();
		void previousSong();
		void pauseSong(Song *song);
		void showManual();

		void mainLoop();
		void interpretTouch(char* comm);
		bool isCommand(char& entered);
		void checkFile(std::vector<std::string>& musics,Song *song);
		void applyCommEffect(char& comm);

		~MusicMaker();

	private :
		PortSender* _port;
		std::vector<std::string> _musics;
		std::vector<char> _commands;
		bool _goOn;
		unsigned int _song;
};

#endif // __MUSIC_MAKER_HPP
