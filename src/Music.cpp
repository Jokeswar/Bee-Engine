#include "Music.h"
#include "Utility.h"

Music::Music()	/**< Stub function for creating component */
{
	this->id = 3;
	this->name = "Music";
	this->parentObject = NULL;

	this->music = NULL;
	return;
}

Music::Music(void* parent)
{
	this->id = 3;					/**< Component specific initialization */
	this->name = "Music";			/**< Component specific initialization */
	this->parentObject = parent;	/**< Component specific initialization */

	this->music = NULL;
	return;
}

Music::~Music()
{
	Mix_FreeMusic(music);
	music = NULL;
}

void Music::loadMusic(const char* filename)
{
	music = Mix_LoadMUS(filename);
}

/// \brief Set's the volume
///
/// \param Volume [0-128]. If less than 0 it defaults to 0 and if bigger than 128 it defaults to 128
void Music::setVolume(char vol)
{
    if(vol < 0) vol = 0;
    if(vol > 128) vol = 128;

	Mix_VolumeMusic(vol);
}

void Music::play()
{
	if(Mix_PlayingMusic() == 0)
		Mix_PlayMusic(music, -1);
}

void Music::pause()
{
	Mix_PauseMusic();
}

void Music::restart()
{
	Mix_RewindMusic();
}
