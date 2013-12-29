#include "MusicMaker.hpp"

#define TAILLE_SPECTRE 512
#define REFRESH 21500

MusicMaker::MusicMaker(PortSender* port,std::vector<std::string>& res) :
	_port(port),_musics(res),_commands(std::vector<char>()),_goOn(true),_song(0)
	{
	#ifdef __STATISTICS
		openStat(STAT_FILE);
	#endif

	this->_commands.push_back('n');
	this->_commands.push_back('p');
	this->_commands.push_back('s');
	this->_commands.push_back('q');

	QObject::connect(this,SIGNAL(stop()),this,SLOT(finish()));
}

void MusicMaker::mainLoop(){
	this->showManual();

	float spectre[TAILLE_SPECTRE];

	/* Initialisation du compteur de musique */
	char comm('0');

	/* Initialisation du thread */
	std::thread T(&MusicMaker::interpretTouch,this,&comm);

	while (this->_goOn){

		/* Initialisation */
		/*
		FMOD_SYSTEM *system;
		FMOD_SOUND *musique;
		FMOD_CHANNEL *canal;
		FMOD_RESULT resultat;
		*/

		/* Nom de la musique actuelle */
		std::string songName(this->_musics[this->_song]);

		Song songPlaying=Song(songName);

		/* On vérifie si elle a bien été ouverte (IMPORTANT) */
		this->checkFile(this->_musics,&songPlaying);

		/* On joue la musique */
		songPlaying.playSong();

		/* Montre si la musique est terminée */
		FMOD_BOOL isplaying=1;

		while((isplaying) && ((comm=='0') || (comm=='s'))){
			if(this->_port->isPortOk()){
				songPlaying.getSpectrum(spectre,TAILLE_SPECTRE);
				this->_port->sendData(this->_port->calculateValue(spectre,TAILLE_SPECTRE));
				#ifdef __STATISTICS
					++number_turn;
				#endif
				usleep(REFRESH);
			}

			isplaying=songPlaying.isSongPlaying();
			if(comm=='s'){
				this->pauseSong(&songPlaying);
				comm='0';
			}
		}

		if(comm!='0'){
			this->applyCommEffect(comm);
			comm='0';
		}

		songPlaying.stopSong();

		#ifdef __STATISTICS
			std::cout << "nb_turn : " << nb_turn << std::endl;
			std::cout << "turn : " << turn << std::endl;
		#endif // __STATISTICS

			usleep(REFRESH);

		this->nextSong();
	}
	T.join();
	#ifdef __STATISTICS
		writeStat(STAT_FILE);
	#endif
}

void MusicMaker::nextSong(){
	if(this->_song==this->_musics.size()-1){
		this->_song=0;
	}else{
		++this->_song;
	}
}

void MusicMaker::previousSong(){
	if(this->_song==0){
		this->_song=this->_musics.size()-2;
	}else{
		--this->_song;
		--this->_song;
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
		std::cout << "Lecture of " << musics[this->_song] << " impossible !" << std::endl;
		std::cout << "Skipping to next song... " << std::endl;
		this->nextSong();
		song=new Song(musics[this->_song]);
	}
	std::cout << "Now Playing ! : " << musics[this->_song] << std::endl << "Entry : ";
}

void MusicMaker::interpretTouch(char* comm){
	char inter('0');
	while(inter!='q'){
		inter='0';
		std::cin >> inter;
		if(this->isCommand(inter)){
			*comm=inter;
		}else{
			MusicMaker::showManual();
		}
	}
}

bool MusicMaker::isCommand(char& entered){
	unsigned i(0);
	while((i<this->_commands.size()) && (entered!=this->_commands[i])){
		++i;
	}
	return entered==this->_commands[i];
}

void MusicMaker::applyCommEffect(char& comm){
	if(comm=='q'){
		this->_goOn=false;
	}else if(comm=='p'){
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
//	delete this->_port;
}
