#include "CommandInterpretor.hpp"

CommandInterpretor::CommandInterpretor(std::string file,AppHandler* app) :
	commands_(std::vector<Command*>()),app_(app)
{
	this->buildTree(file);
}

void CommandInterpretor::buildTree(std::string file){
	std::vector<Command*> res;
	std::ifstream flux(file.c_str());

	if (flux){

		std::string line;
		std::string commandName;
		std::vector<std::string> commands;

		while (getline(flux,line)){
			std::vector<std::string> splitted=splitLine(line);

			if (splitted[0]=="<command"){
				commandName=splitted[1].substr(0,splitted[1].size()-1);
			}else if(splitted[0]=="</command>"){
				std::vector<std::string> copy;
				for(unsigned i(0);i<commands.size();++i){
					copy.push_back(commands[i]);
				}
				commands=std::vector<std::string>();
				Command* toAdd=new Command(commandName,copy);
				res.push_back(toAdd);
			}else if(line.size()>=1){
				commands.push_back(line);
			}
		}

	}else{
		throw("[Erreur] Didn't succeed in opening .xml file");
	}
	this->commands_=res;
}

void CommandInterpretor::mainLoop(){
#ifdef __VERBOSE
	std::cout << "VIAAC Creation of pipes" << std::endl;
#endif

	bool isFinished(false);
	int mPere_mFils[2];

	try{
		if(pipe(mPere_mFils)==-1){
			isFinished=true;
			throw("[Error] Creation of music pipe..");
		}
	}catch(char const* e){
		std::cout << e << std::endl;
	}

	std::string command("");
	std::vector<std::string> parsed;

	while(not isFinished){
		std::cout << "> " ;
		std::getline(std::cin,command);
		try{
			parsed=this->parseCommand(command);
		}catch(const char* e){
			std::cout << e << std::endl;
		}
		try{
			this->execCommand(parsed,mPere_mFils);
		}catch(const char* e){
			std::cout << e << std::endl;
		}
	}
}

std::vector<std::string> CommandInterpretor::splitLine(std::string line){
	std::vector<std::string> res;
	std::istringstream iss(line);

	do{
		std::string sub;
		iss >> sub;
		if(sub.size()>0)
			res.push_back(sub);
	}while(iss);
	return res;
}

std::vector<std::string> CommandInterpretor::parseCommand(std::string command){
	std::vector<std::string> splitted=this->splitLine(command);
	if(command.size()==0)
		return std::vector<std::string>();
	int commandNo(this->isCommand(splitted[0]));
	if (commandNo!=-1){
		if (splitted.size()==2){
			if(not (this->commands_[commandNo]->isOption(splitted[1])))
				splitted=std::vector<std::string>();
		}
	}else{
		splitted=std::vector<std::string>();
	}
	return splitted;
}

int CommandInterpretor::isCommand(std::string command){
	int i(0);
	bool run(true);
	while (run and (this->commands_[i]->getCommand()!=command)){
		++i;
		if (i==this->commands_.size()-1)
			run=false;
	}
	if(this->commands_[i]->getCommand()!=command){
		i=-1;
	}
	return i;
}

void CommandInterpretor::execCommand(std::vector<std::string> command,int mPere_mFils[2]){
	if(command.size()==0){
		std::cout << "Command not found !" << std::endl;
	}else{
		if(command.size()==1){
			this->app_->handle(command[0]);
		}else if (command.size()==2){
			this->app_->handle(command,mPere_mFils);
		}
	}
}

void CommandInterpretor::showCommandTree(){
	for(unsigned i(0);i<this->commands_.size();++i){
		Command* com=this->commands_[i];
		std::cout << "Command " << com->getCommand() << std::endl;
		std::cout << "Option : " << std::endl;
		for(unsigned j(0);j<com->getOptions().size();++j){
			std::cout << "    " << com->getOptions()[j] << std::endl;
		}
	}
}