#ifndef SONG_HPP
#define SONG_HPP

#include <iostream>
#include <string>
#include <fmod/fmod.h>

class Song
{
public:
	Song();
	Song(std::string name);

	void initSong();
	FMOD_BOOL isSongPlaying();
	FMOD_BOOL isCreated();
	FMOD_BOOL isInPause();
	void setPause(FMOD_BOOL pause);
	void getSpectrum(float spectre[],int size);
	void playSong();
	void stopSong();

	~Song();

private :
	std::string name_;
	FMOD_SYSTEM *system_;
	FMOD_SOUND *musique_;
	FMOD_CHANNEL *canal_;
	FMOD_RESULT resultat_;
};

#endif // SONG_HPP
