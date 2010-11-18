#include <iostream>
#include <stdexcept>

#include "Sound.h"

Sound::Sound() {
	result = FMOD::System_Create(&system);
	checkError("Error in the sound system creation");

	result = system->setOutput(FMOD_OUTPUTTYPE_ALSA);
	checkError("Error in the sound system setOutput");

	system->init(32, FMOD_INIT_NORMAL, 0); 
	checkError("Error in the sound system init");

}

Sound::~Sound() {
	system->release();
	mainMusic->release();
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
	result = system->createStream(MAIN_MUSIC, FMOD_SOFTWARE, 0, &mainMusic);
#endif

#ifdef SOUND_MODE
	/* Pour un son (lecture en tampon) */
	result = system->createSound("./Sounds/music.mp3", FMOD_SOFTWARE, 0, &mainMusic);
#endif
	checkError("The music does not exist");

	result = system->playSound(FMOD_CHANNEL_FREE, mainMusic, 0, &channelMusic);
	checkError("The music can't be played");
}

void Sound::playVroum(void) {
#ifdef STREAM_MODE
	/* Pour un flux (lecture en live) */
	result = system->createStream("./Sounds/vroum.mp3", FMOD_SOFTWARE, 0, &mainMusic);
#endif

#ifdef SOUND_MODE
	/* Pour un son (lecture en tampon) */
	result = system->createSound("./Sounds/vroum.mp3", FMOD_SOFTWARE, 0, &mainMusic);
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
