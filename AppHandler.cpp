#include "AppHandler.hpp"

AppHandler::AppHandler() :
	isMusic_(false)
{
}

void AppHandler::handle(std::string command){

}

void AppHandler::handle(std::vector<std::string> command,int mPere_mFils[2]){
	if(command[0]=="music"){
		this->musicHandle(command[1],mPere_mFils);
	}
}


void AppHandler::musicHandle(std::string command,int mPere_mFils[2]){
	char val;
	if(command=="start" && !(this->isMusic_)){ //start music case
		this->isMusic_=true;
		this->forkMusic(mPere_mFils);
	}else if (command=="stop" && (this->isMusic_)){ // stop music case
		val='q';
		this->isMusic_=false;
		write(mPere_mFils[1],(void*) &val,sizeof(char));
	}else if (command=="next" && (this->isMusic_)){ // next song case
		val='n';
		write(mPere_mFils[1],(void*) &val,sizeof(char));
	}else if (command=="previous" && (this->isMusic_)){ // previous song cases
		val='p';
		write(mPere_mFils[1],(void*) &val,sizeof(char));
	}else if (command=="pause" && (this->isMusic_)){ // pause song
		val='s';
		write(mPere_mFils[1],(void*) &val,sizeof(char));
	}
}

void AppHandler::forkMusic(int mPere_mFils[2]){
	pid_t pid;
	pid=fork();
	if(pid==0){
		this->launchMusic(mPere_mFils);
		exit(0);
	}else if (pid==-1){
		std::cout << "Error while forking" << std::endl;
	}else{
		std::cout << "processus pere" << std::endl;
	}
}

void AppHandler::launchMusic(int *mPere_mFils){
	close(mPere_mFils[1]);
	char val;
	MusicMaker M(PORT_NAME,MUSIC_FILE);
	std::thread t(&AppHandler::playMusic,this,&M);
	while(val!='q'){
		read(mPere_mFils[0],(void*) &val,sizeof(char));
		M.setCommand(val);
	}
	t.join();
}

void AppHandler::playMusic(MusicMaker* M){
	M->mainLoop();
}