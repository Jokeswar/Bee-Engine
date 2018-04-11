#include "SoundEffect.h"
#include "Utility.h"

SoundEffect::SoundEffect()
{
	this->id = 4;
	this->name = "SoundEffect";
	this->parentObject = NULL;

	this->soundEffect = NULL;
	return;
}

SoundEffect::SoundEffect(void* parent)
{
	this->id = 4;
	this->name = "SoundEffect";
	this->parentObject = parent;

	this->soundEffect = NULL;
	return;
}

SoundEffect::~SoundEffect()
{
	Mix_FreeChunk(soundEffect);
	soundEffect = NULL;
}

void SoundEffect::loadSound(const char* filename)
{
	soundEffect = Mix_LoadWAV(filename);
}

/// \brief Set's the volume
///
/// \param Volume [0-128]. If less than 0 it defaults to 0 and if bigger than 128 it defaults to 128
void SoundEffect::setVolume(char vol)
{
    if(vol < 0) vol = 0;
    if(vol > 128) vol = 128;
	Mix_VolumeChunk(soundEffect, vol);
}

void SoundEffect::play()
{
	Mix_PlayChannel(-1, soundEffect, 0);
}
