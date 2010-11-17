#ifndef _SOUND_H
#define _SOUND_H

/* #include <AL/alut.h> */
/* #include <AL/alc.h> */
#include "fmod/fmod.hpp"
#include "fmod/fmod_errors.h"
#include "fmod/wincompat.h"

#define NB_CANAL 4
/**
 * STREAM_MODE pour une lecture live
 * SOUND_MODE pour une mise en tampon
 */
#define STREAM_MODE

class Sound {
public:
        Sound();
        ~Sound();
	void play(void);
private:
	FMOD::System *system;
	FMOD::Sound *sound;
	FMOD::Channel *channel;
	FMOD_RESULT result;
};

#endif
