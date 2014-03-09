#ifndef __COMMAND_INTERPRETOR_HPP
#define __COMMAND_INTERPRETOR_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "Command.hpp"
#include "AppHandler.hpp"

class CommandInterpretor
{
	public :
		CommandInterpretor(std::string file,AppHandler* app);

		void mainLoop();
		void buildTree(std::string file);
		std::vector<std::string> splitLine(std::string line);
		std::vector<std::string> parseCommand(std::string command);
		int isCommand(std::string command);
		void musicHandle(std::string order);
		void execCommand(std::vector<std::string> command,int mPere_mFils[2]);

		void showCommandTree();

	private :
		std::vector<Command*> commands_;
		AppHandler* app_;
};

#endif