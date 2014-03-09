#include "Song.hpp"

   #include <unistd.h>
   #include <stdio.h>
   #include <errno.h>


Song::Song() :
	name_("")
{
}

Song::Song(std::string name):
	name_(name)
{
	this->initSong();
}

void Song::initSong(){
	FMOD_System_Create(&this->system_);
	FMOD_System_Init(this->system_,1,FMOD_INIT_NORMAL,0);
	this->resultat_ = FMOD_System_CreateSound(this->system_,this->name_.c_str(),
					FMOD_SOFTWARE|FMOD_2D|FMOD_CREATESTREAM,0,&this->musique_);
}

FMOD_BOOL Song::isSongPlaying(){
	FMOD_BOOL isplaying;
	FMOD_Channel_IsPlaying(this->canal_,&isplaying);
	return isplaying;
}

FMOD_BOOL Song::isCreated(){
	return this->resultat_;
}

FMOD_BOOL Song::isInPause(){
	FMOD_BOOL pause;
	FMOD_Channel_GetPaused(this->canal_,&pause);
	return pause;
}

void Song::setPause(FMOD_BOOL pause){
	FMOD_Channel_SetPaused(this->canal_,pause);
}

void Song::getSpectrum(float spectre[],int size){
	FMOD_Channel_GetSpectrum(this->canal_,spectre,size,0,FMOD_DSP_FFT_WINDOW_RECT);
}

void Song::playSong(){
	/* On joue la musique */
	FMOD_System_PlaySound(this->system_,FMOD_CHANNEL_FREE,this->musique_,0,0);

	/* On récupère le pointeur du canal */
	FMOD_System_GetChannel(this->system_,0,&this->canal_);
}

void Song::stopSong(){
	FMOD_Sound_Release(this->musique_);
	FMOD_System_Close(this->system_);
	FMOD_System_Release(this->system_);
}

Song::~Song(){
}
