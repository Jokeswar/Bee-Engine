#include <iostream>
#include "Bee.h"

using namespace std;

/***********************************************
// @todo features
 *		-collision for rotated objects
 *      -render text, optional: include loading custom font
***********************************************/

Bee my_bee;

class Bar
{
    public:
        Bar(int id, int screenWidth, int screenHeight, const char* filename)
        {
            if(id == 0)
            {
                this->obj = new Object(0, 0);
                this->obj->entityName = "player";

                Sprite* s = new Sprite(obj);
                s->loadImage(filename, Vector3(-1));
                obj->addComponent(s);
                s->show = false;

                Transform *t = getComponentFrom<Transform>(obj, "Transform");
                t->coordX = 20;
                t->coordY = screenHeight/2 - s->getHeight()/2;
            }
            else if(id == 1)
            {
                this->obj = new Object(0, 0);
                this->obj->entityName = "enemy";

                Sprite* s = new Sprite(obj);
                s->loadImage(filename, Vector3(-1));
                obj->addComponent(s);

                Transform *t = getComponentFrom<Transform>(obj, "Transform");
                t->coordX = screenWidth - 20 - s->getWidth();
                t->coordY = screenHeight/2 - s->getHeight()/2;
            }
            else return;

            Physics* p = new Physics(obj);
            p->isFixed = true;
            obj->addComponent(p);

            SquareCollider* sq = new SquareCollider(obj);
            obj->addComponent(sq);
        }

        ~Bar()
        {
            my_bee.removeObject(obj);
        }

        void D_collider()
        {
            SquareCollider *sq = getComponentFrom<SquareCollider>(this->obj, "SquareCollider");
            SDL_Rect r = {sq->getX(), sq->getY(), sq->getWidth(), sq->getHeight()};

            SDL_SetRenderDrawColor(my_bee.game_window_renderer, 255, 0, 0, 255);
            SDL_RenderDrawRect(my_bee.game_window_renderer, &r);
            SDL_SetRenderDrawColor(my_bee.game_window_renderer, 0, 0, 0, 255);
        }

        void setSpeed(int value)
        {
            this->speed = value;
        }

        void update()
        {
            this->D_collider();
            if(obj->entityName.compare("player") == 0) this->doMovement();
        }

    private:
        Object *obj;
        int speed = 150;

        void doMovement()
        {
            Vector2 v;
            if(my_bee.isKeyPressed("w") == true)
            {
                v = {0, -speed};    /**< SDL is top right-down based, so we go against common sense */
            }
            else if(my_bee.isKeyPressed("s") == true)
            {
                v = {0, +speed};
            }
            else
            {
                v = {0, 0};
            }

            getComponentFrom<Physics>(this->obj, "Physics")->setVelocity(v);

        }
};

void DdrawSquareCollider(SquareCollider *sq)
{
    SDL_Rect r = {sq->getX(), sq->getY(), sq->getWidth(), sq->getHeight()};

    SDL_SetRenderDrawColor(my_bee.game_window_renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(my_bee.game_window_renderer, &r);
    SDL_SetRenderDrawColor(my_bee.game_window_renderer, 0, 0, 0, 255);
}

int main(int argc, char *argv[])
{
    my_bee.createWindow(1000, 700, "Test");

    Bar player(0, 1000, 700, "bar.bmp");
    //Bar enemy(1, 1000, 700, "bar2.bmp");

    Object upWall(0, 0);
    upWall.entityName = "upWall";
    SquareCollider* sqWall = new SquareCollider(&upWall);
    Physics* p = new Physics(&upWall);
    p->isFixed = true;
    sqWall->setSize(1000, 10);
    upWall.addComponent(sqWall);
    upWall.addComponent(p);

    Object ball(100, 335);
	ball.entityName = "ball";

    Sprite* s2 = new Sprite(&ball);
    s2->loadImage("ball.bmp", Vector3(255, 255, 255));
    s2->show = false;
    ball.addComponent(s2);

    Physics* p2 = new Physics(&ball);
    Vector2 v = {-20, 0};
    p2->setVelocity(v);
    ball.addComponent(p2);

    SquareCollider* sq = new SquareCollider(&ball);
    ball.addComponent(sq);

    while(my_bee.isKeyPressed("q") != 1)
    {
        DdrawSquareCollider(sq);
        DdrawSquareCollider(sqWall);

//        enemy.update();
        player.update();
        my_bee.update();
    }

    return 0;
}
