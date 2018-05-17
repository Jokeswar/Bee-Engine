#ifndef BEE_H
#define BEE_H

#include "Object.h"
#include "Utility.h"
#include "SquareCollider.h"

#include <SDL2/SDL.h>
#include <thread>

class Bee
{
    public:
        Bee();
        ~Bee();

        void update();
        void createWindow(int, int, const char*);
        bool isKeyPressed(const char*);
        bool isKeyReleased(const char*);

        void addObject(Object*);
        void removeObject(Object*);
        Object* getObject(std::string);

        static Bee* gameWorld;  /**< Pointer to the newest created class */

        SDL_Window* game_window;
        SDL_Renderer* game_window_renderer;
        bool alive;

    private:
        void updateKeysPressed();
        void doPhysics();
        void checkCollision();
        void solveCollision(Object*, Object*);

        bool keysPressed[SDL_NUM_SCANCODES];
        bool keysReleased[SDL_NUM_SCANCODES];

        std::vector<Object*> objectList;
       // std::thread physics;
};

#endif // BEE_H
