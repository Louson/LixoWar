#include <iostream>

#include "Sound.h"

Sound::Sound() {
	FMOD_System_Create(&sys);
	FMOD_System_Init(sys, NB_CANAL, FMOD_INIT_NORMAL, NULL);
}

Sound::~Sound() {
	FMOD_System_Release(sys);
}

void Sound::lecture(void) {
#ifdef STREAM_MODE
	/* Pour un flux (lecture en live) */
	FMOD_System_CreateStream(sys, "Sounds/music.mp3", FMOD_HARDWARE | FMOD_LOOP_OFF | FMOD_2D, 0, &sound);
#endif
#ifdef SOUND_MODE
	/* Pour un son (lecture en tampon) */
	FMOD_System_CreateSound(sys, "Sounds/music.mp3", FMOD_HARDWARE | FMOD_LOOP_OFF | FMOD_2D, 0, &sound);
#endif
	FMOD_System_PlaySound(sys, FMOD_CHANNEL_FREE, sound, 0, &channel);
}
