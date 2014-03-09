#include "Command.hpp"

Command::Command() :
	command_("NULL"),options_(std::vector<std::string>())
{
}

Command::Command(std::string name) :
	command_(name),options_(std::vector<std::string>())
{
}

Command::Command(std::string name,std::vector<std::string>& commands) :
	command_(name),options_(commands)
{
}

void Command::addOption(std::string option){
	this->options_.push_back(option);
}

bool Command::isCommand(std::string toTest){
	return (this->command_==toTest);
}

bool Command::isOption(std::string toTest){
	bool isInOption(false);
	unsigned i(0);
	while (not (isInOption) && (i<this->options_.size())){
		isInOption=(this->options_[i]==toTest);
		++i;
	}
	return isInOption;
}
