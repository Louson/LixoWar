#ifndef _SOUND_H
#define _SOUND_H

#include <string>

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
#define CHECK_ERRORS

/**
 * Musics paths
 */
#define MAIN_MUSIC "./Sounds/music.mp3"
#define BIP_START
#define VROUM "./Sounds/vroum.mp3"
#define VROUM_UP
#define VROUM_DOWN
#define TURN

class Sound {
public:
        Sound();
        ~Sound();
	void playMainMusic(void);
	void playVroum(void);

	bool isMusic();
	bool isFoley();
private:
	void checkError(std::string s);
	FMOD::System *system;
	FMOD_RESULT result;

	FMOD::Channel *channelMusic;
	FMOD::Channel *channelFoley;

	FMOD::Sound *mainMusic;
	FMOD::Sound *bipStart;
	FMOD::Sound *vroum;
	FMOD::Sound *vroumUp;
	FMOD::Sound *vroumDown;
	FMOD::Sound *turn;
	FMOD::Sound *boum;
	FMOD::Sound *laugh;
	FMOD::Sound *gameOver;
};

#endif
