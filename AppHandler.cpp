#include "AppHandler.hpp"

AppHandler::AppHandler(std::string callendar,std::string crontab) :
	music_(false),time_(TimeHandler(callendar,crontab))
{
}

void AppHandler::treat(char *val,int* mPere_mFils){
	std::string valConverted=std::string(val);
	int command(-1);
	std::string details;
	details=this->parse(&command,valConverted.substr(0,valConverted.size()-1));

	// music part
	if(command<=5){
		this->musicHandle(command,mPere_mFils);
	}
}

std::string AppHandler::parse(int* command,std::string val){
	std::string res="";
	if(val.compare("***UTTERANCE*** start music")==0){
		std::cout << "STARTING MUSIC" << std::endl;
		*command=0;
	}else if(val.compare("***UTTERANCE*** stop music")==0){
		std::cout << "STOPPING MUSIC" << std::endl;
		*command=1;
	}else if(val.compare("***UTTERANCE*** next song")==0){
		std::cout << "NEXT SONG" << std::endl;
		*command=2;
	}else if(val.compare("***UTTERANCE*** previous song")==0){
		std::cout << "NEXT SONG" << std::endl;
		*command=3;
	}else if(val.compare("***UTTERANCE*** interruption song")==0){
		std::cout << "PAUSE SONG" << std::endl;
		*command=4;
	}
	return res;
}

void AppHandler::musicHandle(int &command,int* mPere_mFils){
	if(command==0 && !(this->music_)){ //start music case
		this->music_=true;
		this->forkMusic(mPere_mFils);
	}else if (command==1 && (this->music_)){ // stop music case
		this->music_=false;
		this->stopMusic(mPere_mFils);
	}else if (command==2 && (this->music_)){ // next song case
		this->nextSong(mPere_mFils);
	}else if (command==3 && (this->music_)){ // previous song cases
		this->previousSong(mPere_mFils);
	}else if (command==4 && (this->music_)){ // pause song
		this->pauseSong(mPere_mFils);
	}
}

void AppHandler::forkMusic(int* mPere_mFils){
	pid_t pid;
	pid=fork();
	if(pid==0){
		this->launchMusic(mPere_mFils);
		exit(0);
	}else if (pid==-1){
		std::cout << "Error while forking" << std::endl;
	}
}

void AppHandler::launchMusic(int *mPere_mFils){
	close(mPere_mFils[1]);
	int val=0;
	MusicMaker M(PORT_NAME,MUSIC_FILE);
	std::thread t(&AppHandler::playMusic,this,&M);
	while(val!=-1){
		read(mPere_mFils[0],(void*) &val,sizeof(int));
		std::cout << "launch Music received value : " << val << std::endl;
		if(val==-1)
			M.setCommand('q');
		else if(val==0){
			M.setCommand('n');
		}else if(val==1){
			M.setCommand('p');
		}else if(val==2)
			M.setCommand('s');
	}
	t.join();
}

void AppHandler::playMusic(MusicMaker* M){
	M->mainLoop();
}

