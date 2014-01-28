#ifndef __MUSIC_MAKER_HPP
#define __MUSIC_MAKER_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <thread>
#include <fmod/fmod.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>

#include <QObject>
#include <QString>

#include "PortSender.hpp"
#include "Song.hpp"
#include "libTreater.hpp"

#define TAILLE_SPECTRE 512
#define REFRESH 21500

class MusicMaker : public QObject{

	Q_OBJECT

	public :
		MusicMaker(std::string port,std::string music);
		MusicMaker(PortSender* port,std::vector<std::string>& res);

		void nextSong();
		void previousSong();
		void pauseSong(Song *song);
		void showManual();

		void mainLoop();
		void refreshList(std::string filename);
		void interpretTouch();
		bool isCommand(char& entered);
		void checkFile(std::vector<std::string>& musics,Song *song);
		void applyCommEffect();

		void setGoOn(bool goOn){this->goOn_=goOn;}
		Song* getCurrentSong(){return this->songPlaying_;}
		void setCommand(char newChar){ this->comm_=newChar; }

		~MusicMaker();

	private :
		PortSender* port_;
		std::vector<std::string> musics_;
		std::vector<char> commands_;
		bool goOn_;
		unsigned int song_;
		bool isLaunched_;
		Song* songPlaying_;
		char comm_;
};

#endif // __MUSIC_MAKER_HPP
