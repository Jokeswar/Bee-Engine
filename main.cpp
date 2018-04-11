#include <iostream>
#include "Bee.h"

using namespace std;

/***********************************************
// @todo features
 *		-collision for rotated objects
 *      -render text, optional: include loading custom font
***********************************************/

Bee my_bee();

class Bar
{
    public:
        Bar(int id, int screenWidth, int screenHeight, const char* filename)
        {
            if(id == 0)
            {
                this->obj = new Object(0, 0);

                Sprite* s = new Sprite(obj);
                s->loadImage(filename, Vector3(-1));

                Transform *t = getComponentFrom<Transform>(obj, "Transform");
                t->coordX = 20;
                t->coordY = screenHeight/2 + s->getHeight()/2;

                Physics* p = new Physics(&obj);
                obj->addComponent(p);

                SquareCollider* sq = new SquareCollider(&obj);
                obj->addComponent(sq);
            }
            else
            {
                this->obj = new Object(0, 0);

                Sprite* s = new Sprite(obj);
                s->loadImage(filename, Vector3(-1));

                Transform *t = getComponentFrom<Transform>(obj, "Transform");
                t->coordX = screenWidth - 20;
                t->coordY = screenHeight/2 + s->getHeight()/2;
            }
        }

        ~Bar()
        {
            my_bee.removeObject(obj);
        }

    private:
        Object *obj;
};

int main(int argc, char *argv[])
{
    my_bee.createWindow(1000, 700, "Test");

    Bar player(0, 1000, 700, "bar.bmp");
    Bar enemy(1, 1000, 700, "bar.bmp");

    Object obj2(500, 350);
	obj2.entityName = "hey2";


    Sprite* s2 = new Sprite(&obj2);
    s2->loadImage("ball.bmp", Vector3(255, 255, 255));
    obj2.addComponent(s2);

    Physics* p2 = new Physics(&obj2);
    obj2.addComponent(p2);

    SquareCollider* sq2 = new SquareCollider(&obj2);
    obj2.addComponent(sq2);

    while(my_bee.isKeyPressed("q") != 1)
    {
        if(my_bee.isKeyPressed("w") == true)
        {
            Vector2 v = {0, 100};

        }
        else if(my_bee.isKeyPressed("s") == true)
        {
            Vector2 v = {0, -100};

        }
        else
        {
            Vector2 v = {0, 0};

        }

        my_bee.update();
    }

    return 0;
}
