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

	system->init(1, FMOD_INIT_NORMAL, 0); 
	checkError("Error in the sound system init");
}

void Sound::init(void) throw(File::ExceptionBadPath, File::ExceptionParamInexistent)
{
                File config_file(PATH_CONFIG_FILE);
                path_theme = config_file.getParamString("theme");
                path_vroum = config_file.getParamString("vroum");
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

void Sound::playMainMusic(void) {
#ifdef STREAM_MODE
	/* Pour un flux (lecture en live) */
	//result = system->createStream(path_theme.c_str(), FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &mainMusic);
	result = system->createSound(path_theme.c_str(), FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &mainMusic);
#endif

#ifdef SOUND_MODE
	/* Pour un son (lecture en tampon) */
	result = system->createSound(path_theme.c_str(), FMOD_SOFTWARE, 0, &mainMusic);
#endif
	checkError("The theme does not exist");

	result = system->playSound(FMOD_CHANNEL_FREE, mainMusic, 0, &channelMusic);
	checkError("The theme can't be played");
}

void Sound::playVroum(void) {
#ifdef STREAM_MODE
	/* Pour un flux (lecture en live) */
	result = system->createStream(path_vroum.c_str(), FMOD_SOFTWARE, 0, &mainMusic);
#endif

#ifdef SOUND_MODE
	/* Pour un son (lecture en tampon) */
	result = system->createSound(path_vroum, FMOD_SOFTWARE, 0, &mainMusic);
#endif
	checkError("The music does not exist");
		
	result = system->playSound(FMOD_CHANNEL_FREE, mainMusic, 0, &channelFoley);
	checkError("The music can't be played");
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
