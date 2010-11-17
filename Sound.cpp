#include <iostream>
#include <stdexcept>
#include <iostream>

#include "Sound.h"

Sound::Sound() {
	result = FMOD::System_Create(&system);
	system->setOutput(FMOD_OUTPUTTYPE_ALSA);
	system->init(32, FMOD_INIT_NORMAL, 0); 

	if (result != FMOD_OK) {
		throw std::runtime_error("Error in the sound creation");
	}
}

Sound::~Sound() {
	system->release();
	sound->release();
}

void Sound::play(void) {
#ifdef STREAM_MODE
	/* Pour un flux (lecture en live) */
	system->createStream("./Sounds/music.mp3", FMOD_SOFTWARE, 0, &sound);
#endif
#ifdef SOUND_MODE
	/* Pour un son (lecture en tampon) */
	system->createSound("./Sounds/music.mp3", FMOD_SOFTWARE, 0, &sound);
#endif
	system->playSound(FMOD_CHANNEL_FREE, sound, 0, &channel);
}
