#ifndef MUSIC_H
#define MUSIC_H

#include <SDL2/SDL_mixer.h>

#include "Utility.h"
#include "Component.h"
#include "Transform.h"

class Music: public Component
{
    public:
        Music();
        Music(void*);
        ~Music();

		void loadMusic(const char*);
		void play();
		void pause();
		void restart();
		void setVolume(char);

		bool isValid;

    private:
    	Mix_Music *music;
};

#endif // MUSIC_H
