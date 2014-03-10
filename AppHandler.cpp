#include "AppHandler.hpp"

AppHandler::AppHandler() :
	isMusic_(false),port_(new PortHandler(QString::fromStdString(PORT_NAME)))
{
}

void AppHandler::handle(std::string command){

}

void AppHandler::handle(std::vector<std::string> command,int mPere_mFils[2]){
	if(command[0]=="music"){
		this->musicHandle(command[1],mPere_mFils);
	}else if(command[0]=="color"){
		this->colorHandle(command[1]);
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
	MusicMaker M(this->port_,MUSIC_FILE);
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

void AppHandler::colorHandle(std::string color){
	if(color=="red")
		this->port_->sendData("R");
	else if(color=="green")
		this->port_->sendData("G");
	else if(color=="blue")
		this->port_->sendData("B");
	else if(color=="yellow")
		this->port_->sendData("Y");
	else if(color=="light_blue")
		this->port_->sendData("L");
	else if(color=="purple")
		this->port_->sendData("P");
	else if(color=="white")
		this->port_->sendData("W");
	else if(color=="none")
		this->port_->sendData("N");
}