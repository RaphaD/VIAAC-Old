#ifndef __DEF_APP_HANDLER
#define __DEF_APP_HANDLER

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "MusicMaker.hpp"

#define PORT_NAME "/dev/ttyACM0"
#define MUSIC_FILE "./music/music/"

class AppHandler
{
	public :
		AppHandler();

		void handle(std::string command);
		void handle(std::vector<std::string> command,int mPere_mFils[2]);

		void musicHandle(std::string,int mPere_mFils[2]);
		void forkMusic(int mPere_mFils[2]);
		void launchMusic(int mPere_mFils[2]);
		void playMusic(MusicMaker* M);

	private :
		bool isMusic_;
};

#endif //__DEF_APP_HANDLER