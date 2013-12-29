#include "Song.hpp"

Song::Song(std::string name):
	_name(name)
{
	this->initSong();
}

void Song::initSong(){
	FMOD_System_Create(&this->_system);
	FMOD_System_Init(this->_system,1,FMOD_INIT_NORMAL,0);
	this->_resultat = FMOD_System_CreateSound(this->_system,this->_name.c_str(),
					FMOD_SOFTWARE|FMOD_2D|FMOD_CREATESTREAM,0,&this->_musique);
}

FMOD_BOOL Song::isSongPlaying(){
	FMOD_BOOL isplaying;
	FMOD_Channel_IsPlaying(this->_canal,&isplaying);
	return isplaying;
}

FMOD_BOOL Song::isCreated(){
	return this->_resultat;
}

FMOD_BOOL Song::isInPause(){
	FMOD_BOOL pause;
	FMOD_Channel_GetPaused(this->_canal,&pause);
	return pause;
}

void Song::setPause(FMOD_BOOL pause){
	FMOD_Channel_SetPaused(this->_canal,pause);
}

void Song::getSpectrum(float spectre[],int size){
	FMOD_Channel_GetSpectrum(this->_canal,spectre,size,0,FMOD_DSP_FFT_WINDOW_RECT);
}

void Song::playSong(){
	/* On joue la musique */
	FMOD_System_PlaySound(this->_system,FMOD_CHANNEL_FREE,this->_musique,0,0);

	/* On récupère le pointeur du canal */
	FMOD_System_GetChannel(this->_system,0,&this->_canal);
}

void Song::stopSong(){
	FMOD_Sound_Release(this->_musique);
	FMOD_System_Close(this->_system);
	FMOD_System_Release(this->_system);
}

Song::~Song(){
}
