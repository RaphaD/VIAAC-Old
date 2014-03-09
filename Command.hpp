#ifndef __COMMAND_HPP
#define __COMMAND_HPP

#include <iostream>
#include <vector>
#include <string>

class Command
{
	public :
		Command();
		Command(std::string name);
		Command(std::string name,std::vector<std::string>& v);

		void addOption(std::string option);
		bool isCommand(std::string toTest);
		bool isOption(std::string toTest);

		std::string getCommand() const {return this->command_;}
		std::vector<std::string> getOptions() const {return this->options_;}

	private :
		std::string command_;
		std::vector<std::string> options_;
};

#endif