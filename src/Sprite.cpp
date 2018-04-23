#include "Sprite.h"
#include "Component.h"
#include "Transform.h"

#include "Utility.h"
#include "Object.h"
#include "Bee.h"

#include <SDL2/SDL.h>

Sprite::Sprite()	/**< Stub function for creating component */
{
	this->id = 1;
	this->name = "Sprite";
	this->show = true;

	return; 		/// @todo Find why does Sprite* s = new Sprite not work when added as component; Blank Fucking Screen !!!
}

Sprite::Sprite(void* parent)
{
	this->id = 1;					/**< Component specific initialization */
	this->name = "Sprite"; 			/**< Component specific initialization */
	this->parentObject = parent;	/**< Component specific initialization */

    this->texture = NULL;
    this->currentFrame = 0;
    this->numberOfFrames = 1;
    this->show = true;
}

Sprite::~Sprite()
{
    SDL_DestroyTexture(texture);
}

/*******************************************//**
 * \brief Loads a given image in a texture specific for the global renderer
 *
 * \param The path to the image file
 ***********************************************/
void Sprite::loadImage(const char* filename, Vector3 colorKey)
{
    SDL_Surface* surface = SDL_LoadBMP(filename);

    if(colorKey.x != -1)
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, (Uint8)colorKey.x, (Uint8)colorKey.y, (Uint8)colorKey.z));

    texture = SDL_CreateTextureFromSurface(Bee::gameWorld->game_window_renderer, surface);

    imageWidth = surface->w;
    imageHeight = surface->h;

    SDL_FreeSurface(surface);
}

int Sprite::getHeight()
{
    return imageHeight;
}

int Sprite::getWidth()
{
    return imageWidth;
}

void Sprite::setNumberOfFrames(int x)
{
    numberOfFrames = x;
}

void Sprite::update()
{
    if(show == true)
    {
        Object* obj = static_cast<Object*>(this->parentObject);
        Transform* t = getComponentFrom<Transform>(obj, "Transform");

        SDL_Rect renderQuad = {(int)t->coordX, (int)t->coordY, (int)(t->scaleX * (float)this->imageWidth), (int)(t->scaleY * (float)this->imageHeight)};
        SDL_Rect sourceQuad = {(imageWidth/numberOfFrames) * currentFrame, 0, imageWidth/numberOfFrames, imageHeight};

        SDL_RenderCopyEx(Bee::gameWorld->game_window_renderer, texture, &sourceQuad, &renderQuad, t->angle, NULL, SDL_FLIP_NONE);

        currentFrame++;
        if(currentFrame == numberOfFrames) currentFrame = 0;
    }
}
