#ifndef _SOUND_H
#define _SOUND_H

#include <string>

#include "File.h"
/* #include <AL/alut.h> */
/* #include <AL/alc.h> */
#include "fmod/fmod.hpp"
#include "fmod/fmod_errors.h"
#include "fmod/wincompat.h"

class Sound {
public:
        Sound();
        ~Sound();
	void playMainMusic(void);
	void playVroum(void);

        void init(void) throw(File::ExceptionBadPath, File::ExceptionParamInexistent); 
	bool isMusic();
	bool isFoley();
private:

        /* sounds used */
        std::string path_theme;
        std::string path_vroum;


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
