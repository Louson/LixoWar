#ifndef _SOUND_H
#define _SOUND_H

#include <string>

#include "File.h"

#include "fmod/fmod.hpp"
#include "fmod/fmod_errors.h"
#include "fmod/wincompat.h"

#define SOUND_NUMBER 30

enum SON {NONE = -1, EXPLOSION, THEME, VROUM, LASER, VROUM_UP, VROUM_DOWN, VICTORY, GAMEOVER};

class Sound {
        public:
                Sound(void);
                ~Sound(void);

                void init(void) throw(File::ExceptionBadPath, File::ExceptionParamInexistent); 
                bool isMusic();
                bool isFoley();
                void play(enum SON, bool loop = false);
        private:
                /* sounds used */
                std::string sounds[SOUND_NUMBER];
                FMOD::Sound *fmod_sounds[SOUND_NUMBER];
                
                void checkError(std::string s);
                FMOD::System *system;
                FMOD_RESULT result;

                FMOD::Channel *channelMusic;
                FMOD::Channel *channelEffect;
                FMOD::Channel *channelVroum;

                enum SON vroum_playing;
};

#endif
