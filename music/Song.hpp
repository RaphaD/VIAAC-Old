#ifndef SONG_HPP
#define SONG_HPP

#include <iostream>
#include <string>
#include <fmod/fmod.h>

class Song
{
public:
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
	std::string _name;
	FMOD_SYSTEM *_system;
	FMOD_SOUND *_musique;
	FMOD_CHANNEL *_canal;
	FMOD_RESULT _resultat;
};

#endif // SONG_HPP
