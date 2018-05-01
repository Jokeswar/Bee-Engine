#include <iostream>
#include "Bee.h"

using namespace std;

/***********************************************
// @todo features
 *		-collision for rotated objects
 *      -render text, optional: include loading custom font
***********************************************/

Bee my_bee;
int pointsP;
int pointsE;
bool addPoint = false;

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

                Transform *t = getComponentFrom<Transform>(obj, "Transform");
                t->coordX = 20;
                t->coordY = screenHeight/2 - s->getHeight()/2;

                initialPos = {t->coordX, t->coordY};
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

                initialPos = {t->coordX, t->coordY};
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

        void setSpeed(int value)
        {
            this->speed = value;
        }

        void update()
        {
            if(obj->entityName.compare("player") == 0) this->doAI();
            else this->doAI();

            Transform* t = getComponentFrom<Transform>(this->obj, "Transform");
            Sprite* s = getComponentFrom<Sprite>(this->obj, "Sprite");
            if(t->coordY < 10) t->coordY = 10;
            if(t->coordY + s->getHeight() > 690) t->coordY = 690 - s->getHeight();
        }

        void restart()
        {
            getComponentFrom<Transform>(this->obj, "Transform")->coordX = initialPos.x;
            getComponentFrom<Transform>(this->obj, "Transform")->coordY = initialPos.y;
        }

    private:
        Object *obj;
        float speed = 200.0;
        Vector2 initialPos;

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

        void doAI()
        {
            Object* ball = my_bee.getObject("ball");

            Transform* t = getComponentFrom<Transform>(ball, "Transform");
            float thatPos = t->coordY;
            float myPos = getComponentFrom<Transform>(this->obj, "Transform")->coordY;

            Vector2 v;
            if(abs(thatPos - myPos) < 10)
            {
                v = {0.0, 0.0};
            }
            else if(thatPos < myPos)
            {
                v = {0.0, -speed};
            }
            else if(thatPos > myPos)
            {
                v = {0.0, +speed};
            }

            getComponentFrom<Physics>(this->obj, "Physics")->setVelocity(v);
        }

};

class Wall
{
    public:
        Wall(int x, int y, int width, int height)
        {
            this->obj = new Object(x, y);
            this->obj->entityName = "Wall";

            SquareCollider* sq = new SquareCollider(obj);
            sq->setSize(width, height);

            Physics* p = new Physics(obj);
            p->isFixed = true;

            obj->addComponent(sq);
            obj->addComponent(p);
        }

        void addOnCollsion(void (func)(Object*, Object*))
        {
            getComponentFrom<SquareCollider>(this->obj, "SquareCollider")->onCollisionFunction = func;
        }

        void setName(std::string name)
        {
            this->obj->entityName = name;
        }

        std::string getName()
        {
            return this->obj->entityName;
        }

    private:
        Object* obj;
};

class Ball
{
    public:
        Ball(int screenWidth, int screenHeight, const char* filename, const char* sound)
        {
            initialPos = {screenWidth/2, screenHeight/2};

            this->obj = new Object(screenWidth/2, screenHeight/2);
            this->obj->entityName = "ball";

            Sprite* s = new Sprite(this->obj);
            s->loadImage(filename, Vector3(255, 255, 255));
            this->obj->addComponent(s);

            Physics* p = new Physics(this->obj);
            float y = rand() % 400 - 200;
            Vector2 v = {speed, y};
            p->setVelocity(v);
            this->obj->addComponent(p);

            SquareCollider* sq = new SquareCollider(this->obj);
            this->obj->addComponent(sq);

            SoundEffect* se = new SoundEffect(obj);
            se->loadSound(sound);
            this->obj->addComponent(se);
        }

        void addOnCollsion(void (func)(Object*, Object*))
        {
            getComponentFrom<SquareCollider>(this->obj, "SquareCollider")->onCollisionFunction = func;
        }

        void restart()
        {
            getComponentFrom<Transform>(this->obj, "Transform")->coordX = initialPos.x;
            getComponentFrom<Transform>(this->obj, "Transform")->coordY = initialPos.y;

            float y = rand() % 400 - 200;
            getComponentFrom<Physics>(this->obj, "Physics")->setVelocity(Vector2(speed, y));
        }

    private:
        Object* obj;
        float speed = -300.0;

        Vector2 initialPos;
};

void ballCollision(Object* thisObj, Object* thatObj)
{
    if(thatObj->entityName.compare("player") == 0 || thatObj->entityName.compare("enemy") == 0)
        getComponentFrom<SoundEffect>(thisObj, "SoundEffect")->play();

    Physics* p = getComponentFrom<Physics>(thisObj, "Physics");
    Vector2 myVelocity = p->getVelocity();

    if(abs(myVelocity.x) < 500) myVelocity.x *= 1.1;
    if(abs(myVelocity.y) > 400) myVelocity.y  = 400;
    p->setVelocity(myVelocity);
}

void addPoints(Object* thisObj, Object* thatObj)
{
    if(thatObj->entityName.compare("ball") == 0 && thisObj->entityName.compare("leftWall") == 0)
    {
        addPoint = true;
        pointsE++;
    }
    if(thatObj->entityName.compare("ball") == 0 && thisObj->entityName.compare("rightWall") == 0)
    {
        addPoint = true;
        pointsP++;
    }
}

int main(int argc, char *argv[])
{
    const char* title = "Pong";
    const char* playerSprite = "resources/image/bar_player.bmp";
    const char* enemySprite = "resources/image/bar_enemy.bmp";
    const char* backgroundSprite = "resources/image/background.bmp";
    const char* ballSprite = "resources/image/ball.bmp";

    const char* ballSound = "resources/sound/ball_bar.wav";

    my_bee.createWindow(1000, 700, title);

    Object background(0, 0);
    Sprite* bg = new Sprite(&background);
    bg->loadImage(backgroundSprite, Vector3(-1));
    background.addComponent(bg);

    Bar player(0, 1000, 700, playerSprite);
    Bar enemy(1, 1000, 700, enemySprite);

    Ball ball(1000, 700, ballSprite, ballSound);
    ball.addOnCollsion(&ballCollision);

    Wall upWall1(0, -15, 1000, 20);
    Wall downWall(0, 695, 1000, 20);

    Wall leftWall(-15, 6, 20, 680);
    leftWall.addOnCollsion(&addPoints);
    leftWall.setName("leftWall");

    Wall rightWall(995, 6, 20, 680);
    rightWall.addOnCollsion(&addPoints);
    rightWall.setName("rightWall");

    while(my_bee.isKeyPressed("q") != 1)
    {
        if(addPoint == true)
        {
            addPoint = false;
            cout << "Player: " << pointsP << "\n";
            cout << "Enemy: " << pointsE << "\n";
            cout << "\n";

            ball.restart();
            player.restart();
            enemy.restart();
        }

        enemy.update();
        player.update();
        my_bee.update();
    }

    return 0;
}
