#ifndef SOUNDEFFECT_H
#define SOUNDEFFECT_H

#include <SDL2/SDL_mixer.h>

#include "Component.h"

class SoundEffect: public Component
{
	public:
		SoundEffect();
		SoundEffect(void*);
		~SoundEffect();

		void loadSound(const char*);
		void play();
		void setVolume(char);

	private:
		Mix_Chunk* soundEffect;
};

#endif // SOUNDEFFECT_H
