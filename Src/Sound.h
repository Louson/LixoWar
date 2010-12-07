#ifndef _SOUND_H
#define _SOUND_H

#include <string>

#include "File.h"

#include "fmod/fmod.hpp"
#include "fmod/fmod_errors.h"
#include "fmod/wincompat.h"

enum SON {EXPLOSION, THEME, VROUM};

class Sound {
        public:
                Sound();
                ~Sound();

                void init(void) throw(File::ExceptionBadPath, File::ExceptionParamInexistent); 
                bool isMusic();
                bool isFoley();
                void play(enum SON);
        private:
                /* sounds used */
                std::string sounds[3];
                FMOD::Sound *fmod_sounds[3];

                void checkError(std::string s);
                FMOD::System *system;
                FMOD_RESULT result;

                FMOD::Channel *channelMusic;
                FMOD::Channel *channelFoley;
};

#endif
