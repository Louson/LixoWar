#include <iostream>
#include <stdexcept>

#include "Sound.h"
#include "File.h"

#define PATH_CONFIG_FILE "./sound.cfg"

#define NB_CANAL 4
/**
 * STREAM_MODE pour une lecture live
 * SOUND_MODE pour une mise en tampon
 */
#define STREAM_MODE
#define CHECK_ERRORS

Sound::Sound():
        channelMusic(0)
{
	result = FMOD::System_Create(&system);
	checkError("Error in the sound system creation");

	result = system->init(32, FMOD_INIT_NORMAL, 0); 
	checkError("Error in the sound system init");
}

void Sound::init(void) throw(File::ExceptionBadPath, File::ExceptionParamInexistent)
{
	File config_file(PATH_CONFIG_FILE);
        sounds[EXPLOSION] = config_file.getParamString("explosion");
	sounds[THEME] = config_file.getParamString("theme");
	sounds[VROUM] = config_file.getParamString("vroum");
        sounds[LASER] = config_file.getParamString("laser");
}

Sound::~Sound() {
        if(system){
                system->release();
                system->close();
                system->release();
        }
}

void Sound::checkError(std::string s) {
#ifdef CHECK_ERRORS
	if (result != FMOD_OK) {
		throw std::runtime_error(s);
	}
#endif
}

void Sound::play(enum SON son){
	result = system->createSound(sounds[son].c_str(), FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &fmod_sounds[son]);
	checkError("The music does not exist");
	result = system->playSound(FMOD_CHANNEL_FREE, fmod_sounds[son], 0, &channelMusic);
	checkError("The music does not exist");
}

bool Sound::isMusic() {
	bool boolean;
	channelMusic->isPlaying(&boolean);
	return boolean;
}

bool Sound::isFoley() {
	bool boolean;
	channelFoley->isPlaying(&boolean);
	return boolean;
}
