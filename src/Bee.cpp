#include "Bee.h"
#include "Utility.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "Transform.h"
#include "Physics.h"
#include "SquareCollider.h"

Bee* Bee::gameWorld = NULL;

Bee::Bee()
{
    SDL_Init(SDL_INIT_EVERYTHING);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);	/**< Audio Initialization */

    game_window = NULL;
    game_window_renderer = NULL;

	gameWorld = this;
    memset(keysPressed, 0, sizeof(keysPressed));
    memset(keysPressed, 0, sizeof(keysReleased));
}

Bee::~Bee()
{
	Mix_CloseAudio();

    SDL_DestroyWindow(game_window);
    game_window = NULL;

    SDL_DestroyRenderer(game_window_renderer);
    game_window_renderer = NULL;

    SDL_Quit();
}

void Bee::update()
{
	unsigned int frameStart = SDL_GetTicks();

    updateKeysPressed();	/**< User input */
    doPhysics();
    checkCollision();

    for(unsigned int i = 0; i < objectList.size(); ++i)	/**< Objects update */
		objectList[i]->update();

    SDL_RenderPresent(game_window_renderer);	/**< Flipping screen */
    SDL_RenderClear(game_window_renderer);

	unsigned int frameEnd = SDL_GetTicks();		/**< VSync */
	if(frameEnd - frameStart < 33)
		SDL_Delay(33 - (frameEnd - frameStart));
}

void Bee::updateKeysPressed()
{
    memset(keysPressed, 0, sizeof(keysPressed));
    memset(keysReleased, 0, sizeof(keysReleased));
    SDL_Event event;

    while(SDL_PollEvent(&event) != 0)
        switch(event.type)
        {
		case(SDL_KEYDOWN):
			keysPressed[event.key.keysym.scancode] = 1;
			break;

		case(SDL_KEYUP):
			keysReleased[event.key.keysym.scancode] = 1;
			break;
        }
}

bool Bee::isKeyPressed(const char* key)
{
    return keysPressed[SDL_GetScancodeFromName(key)] != 0;
}

bool Bee::isKeyReleased(const char* key)
{
    return keysReleased[SDL_GetScancodeFromName(key)] != 0;
}

void Bee::solveCollision(Object* object1, Object* object2)
{
	float e = 1.0; /**< Energy Retention Coefficient */

	SquareCollider* sc1 = getComponentFrom<SquareCollider>(object1, "SquareCollider");
	SquareCollider* sc2 = getComponentFrom<SquareCollider>(object2, "SquareCollider");

	Physics* p1 = getComponentFrom<Physics>(object1, "Physics");
	Physics* p2 = getComponentFrom<Physics>(object2, "Physics");

	Vector2 relativeVelocity = p2->getVelocity() - p1->getVelocity();
	Vector2 normal = sc1->getCollisionNormal(sc2);

	float veloctiyAlongNormal = normal * relativeVelocity;

	if(veloctiyAlongNormal > 0)	/**< Separating anyway */
		return;

	float j = -(1 + e) * veloctiyAlongNormal;	/**< Impulse Scalar */
	j /= 1 / p1->mass + 1 / p2->mass;

	Vector2 impulse = normal * j;

	Vector2 Vel1 = p1->getVelocity() - impulse * (1 / p1->mass);
	Vector2 Vel2 = p2->getVelocity() + impulse * (1 / p2->mass);

	p1->setVelocity(Vel1);
	p2->setVelocity(Vel2);
}

void Bee::checkCollision()
{
	for(unsigned int i = 0; i < objectList.size(); ++i)
		for(unsigned int j = i+1; j < objectList.size(); ++j)
			{
				SquareCollider* scObj1 = getComponentFrom<SquareCollider>(objectList[i], "SquareCollider");
				SquareCollider* scObj2 = getComponentFrom<SquareCollider>(objectList[j], "SquareCollider");

				if(scObj1 != NULL && scObj2 != NULL)
					if(scObj1->collidedWith(scObj2) == true)
                    {
						solveCollision(objectList[i], objectList[j]);
                        scObj1->onCollisionFunction(objectList[j]);
                        scObj2->onCollisionFunction(objectList[i]);
                    }
			}
}

void Bee::doPhysics()
{
	for(unsigned int i = 0; i < objectList.size(); ++i)
	{
        Object* currentObj = objectList[i];

		Transform* t = getComponentFrom<Transform>(currentObj, "Transform");
		Physics* p = getComponentFrom<Physics>(currentObj, "Physics");

		if(p != nullptr)
		{
			Vector2 vel = p->getVelocity();
			Vector2 acc = p->getAcceleration();

			t->coordX = t->coordX + vel.x * TIMESTEP + 0.5 * acc.x * TIMESTEP * TIMESTEP;
			t->coordY = t->coordY + vel.y * TIMESTEP + 0.5 * acc.y * TIMESTEP * TIMESTEP;

			vel.x = vel.x + acc.x * TIMESTEP;
			vel.y = vel.y + acc.y * TIMESTEP;

			p->setVelocity(vel);
		}
	}
}

void Bee::createWindow(int w, int h, const char* title)
{
    game_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
    game_window_renderer = SDL_CreateRenderer(game_window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(game_window_renderer, 0x0, 0x0, 0x0, 0xFF);
    SDL_RenderClear(game_window_renderer);
}

void Bee::addObject(Object* obj)
{
	objectList.push_back(obj);
}

void Bee::removeObject(Object* obj)
