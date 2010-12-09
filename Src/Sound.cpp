#include <iostream>
#include <stdexcept>

#include "Sound.h"
#include "File.h"

#define PATH_CONFIG_FILE "./sound.cfg"

#define NB_CANAL 4
#define MUSIC_VOLUME 0.15

Sound::Sound():
        channelMusic(0),
        vroum_playing(NONE)
{
        result = FMOD::System_Create(&system);
        checkError("Error in the sound system creation");

        result = system->init(32, FMOD_INIT_NORMAL, 0); 
        checkError("Error in the sound system init");
}

void Sound::init(void) throw(File::ExceptionBadPath, File::ExceptionParamInexistent)
{
        for(int i = 0; i < SOUND_NUMBER; i++)
                fmod_sounds[i] = NULL;

        File config_file(PATH_CONFIG_FILE);
        sounds[EXPLOSION] = config_file.getParamString("explosion");
        sounds[VROUM] = config_file.getParamString("vroum");
        sounds[LASER] = config_file.getParamString("laser");
        sounds[VROUM_UP] = config_file.getParamString("vroum_up");
        sounds[VROUM_DOWN] = config_file.getParamString("vroum_down");
        sounds[VICTORY] = config_file.getParamString("victory");
        sounds[GAMEOVER] = config_file.getParamString("game_over");
        sounds[START] = config_file.getParamString("start");
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

void Sound::play(enum SON son, bool loop)
{
        FMOD::Channel **channel = &channelEffect;
        bool channel_playing;

        FMOD_MODE settings = FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM;
        if(loop)
                settings |= FMOD_LOOP_NORMAL;

                channelVroum->isPlaying(&channel_playing);
        if(son == VROUM_UP || son == VROUM_DOWN){
                /* the wanted vroum song is currently playing, we exit */
                if(vroum_playing == son && channel_playing)
                        return;
                channelVroum->stop();
                vroum_playing = son;
                channel = &channelVroum;
        }

        if(fmod_sounds[son] == NULL)
                result = system->createSound(sounds[son].c_str(), settings, 0, &fmod_sounds[son]);

        checkError("The music does not exist");
        result = system->playSound(FMOD_CHANNEL_FREE, fmod_sounds[son], 0, channel);
        checkError("The music does not exist");

}
