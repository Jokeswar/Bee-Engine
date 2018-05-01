#ifndef SPRITE_H
#define SPRITE_H

#include "Utility.h"
#include "Component.h"

#include <SDL2/SDL.h>

class Sprite: public Component
{
    public:
        Sprite();
        Sprite(void*);
        ~Sprite();

        void update() override;

        int getWidth();
        int getHeight();
        void setNumberOfFrames(int);
        void loadImage(const char*, Vector3);

        bool show;
        bool isValid;

    private:
        SDL_Texture* texture;

        int imageWidth;
        int imageHeight;

        int currentFrame;
        int numberOfFrames;
};

#endif // SPRITE_H
