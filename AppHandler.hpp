#ifndef __APPHANDLER_HPP
#define __APPHANDLER_HPP

#include <vector>
#include <thread>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "TimeHandler.hpp"
#include "MusicMaker.hpp"

#define PORT_NAME "/dev/ttyACM0"
#define MUSIC_FILE "./music/music/"

class AppHandler
{
	public:
		AppHandler(std::string,std::string);

		void treat(char*, int *mPere_mFils);

		void playMusic(MusicMaker *M);

		std::string parse(int *command,std::string val);
		void musicHandle(int &command,int* mPere_mFils);
		void forkMusic(int* mPere_mFils);
		void launchMusic(int* mPere_mFils);

	private :
		bool music_;
		std::vector<int*> pipes_;
		TimeHandler time_;
};

#endif // __APPHANDLER_HPP
