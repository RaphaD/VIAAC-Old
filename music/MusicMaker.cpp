#include "MusicMaker.hpp"

MusicMaker::MusicMaker(std::string port,std::string music) :
	port_(new PortSender(QString::fromStdString(port))),musics_(getNames(music)),
	commands_(std::vector<char>()),goOn_(true),song_(0),songPlaying_(new Song()),
	comm_('0')
{
	std::cout << "MusicMaker::MusicMaker(std::string port,std::string music)" << std::endl;
}

MusicMaker::MusicMaker(PortSender* port,std::vector<std::string>& res) :
	port_(port),musics_(res),commands_(std::vector<char>()),goOn_(true),song_(0),
	songPlaying_(new Song()),comm_('0')
	{
	this->commands_.push_back('n');
	this->commands_.push_back('p');
	this->commands_.push_back('s');
	this->commands_.push_back('q');
}

void MusicMaker::mainLoop(){
	this->showManual();

	float spectre[TAILLE_SPECTRE];
/*
	//if musicMaker is launched by another program
	// Initialisation du thread
	std::thread T(&MusicMaker::interpretTouch,this,&this->comm_);
*/
	while (this->goOn_){
		/* Nom de la musique actuelle */
		std::string songName(this->musics_[this->song_]);

		this->songPlaying_=new Song(songName);

		/* On vérifie si elle a bien été ouverte (IMPORTANT) */
		this->checkFile(this->musics_,this->songPlaying_);

		/* On joue la musique */
		this->songPlaying_->playSong();

		/* Montre si la musique est terminée */
		FMOD_BOOL isplaying=1;

		while((this->goOn_) && (isplaying) && ((this->comm_=='0') || (this->comm_=='s'))){
			if(this->port_->isPortOk()){
				this->songPlaying_->getSpectrum(spectre,TAILLE_SPECTRE);
				this->port_->sendData(this->port_->calculateValue(spectre,TAILLE_SPECTRE));
				usleep(REFRESH);
			}

			isplaying=this->songPlaying_->isSongPlaying();
			if(this->comm_=='s'){
				this->pauseSong(this->songPlaying_);
				this->comm_='0';
			}
		}

		if(this->comm_!='0'){
			this->applyCommEffect();
			this->comm_='0';
		}

		this->songPlaying_->stopSong();
		usleep(REFRESH);
		this->nextSong();
	}
	//if musicMaker is launched by another program
	/*
	T.join();
	*/
}

void MusicMaker::nextSong(){
	if(this->song_==this->musics_.size()-1){
		this->song_=0;
	}else{
		++this->song_;
	}
}

void MusicMaker::previousSong(){
	if(this->song_==0){
		this->song_=this->musics_.size()-2;
	}else{
		--this->song_;
		--this->song_;
	}
}

void MusicMaker::pauseSong(Song* song){
	FMOD_BOOL pause;
	pause=song->isInPause();
	song->setPause(!pause);
}

void MusicMaker::checkFile(std::vector<std::string> &musics,Song* song){
	while(song->isCreated()!=FMOD_OK){
		song->stopSong();
		std::cout << "Lecture of " << musics[this->song_] << " impossible !" << std::endl;
		std::cout << "Skipping to next song... " << std::endl;
		this->nextSong();
		song=new Song(musics[this->song_]);
	}
	std::cout << "Now Playing : " << musics[this->song_] << std::endl;
}

void MusicMaker::refreshList(std::string filename){
	this->musics_=getNames(filename);
}

void MusicMaker::interpretTouch(){
	char inter('0');
	while(inter!='q'){
		inter='0';
		std::cout << "Entry : " << std::endl;
		std::cin >> inter;
		if(this->isCommand(inter)){
			this->comm_=inter;
		}else{
			MusicMaker::showManual();
		}
	}
}

bool MusicMaker::isCommand(char& entered){
	unsigned i(0);
	while((i<this->commands_.size()) && (entered!=this->commands_[i])){
		++i;
	}
	return entered==this->commands_[i];
}

void MusicMaker::applyCommEffect(){
	if(this->comm_=='q'){
		this->goOn_=false;
	}else if(this->comm_=='p'){
		//Si on est en début de liste, on retourne à la dernière musique
		this->previousSong();
	}
	// Pas besoin de traiter 'n' car count sera incrémenté en fin de boucle
}

void MusicMaker::showManual(){
	std::cout << "========== USER MANUAL ==========" << std::endl;
	std::cout << "Type one of the following command :" << std::endl;
	std::cout << "(n) load next song" << std::endl;
	std::cout << "(p) load previous song" << std::endl;
	std::cout << "(s) pause current song" << std::endl;
	std::cout << "(q) quit" << std::endl;
	std::cout << "=================================" << std::endl;
	std::cout << std::endl;
}

MusicMaker::~MusicMaker(){
}
