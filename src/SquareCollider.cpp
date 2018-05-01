#include "SquareCollider.h"

#include "Object.h"

void onCollisionFunctionStub(Object* thisObj, Object* thatObj){}    /**< So the engine's on collision call does not fail by calling a null pointer */

SquareCollider::SquareCollider()	/**< Stub function for creating component */
{
	this->id = 2;
	this->name = "SquareCollider";
	onCollisionFunction = &onCollisionFunctionStub;

	this->dx = 0;
	this->dy = 0;

    return;
}

SquareCollider::SquareCollider(void* parent)
{
	this->id = 2;
	this->name = "SquareCollider";
	this->parentObject = parent;
	this->onCollisionFunction = &onCollisionFunctionStub;
	this->dx = 0;
	this->dy = 0;

    /**<  Completing information for object */
	Object* _parentObject = static_cast<Object*>(parent);
	Transform *t = getComponentFrom<Transform>(_parentObject, "Transform");

    this->x = t->coordX;
    this->y = t->coordY;

    Sprite *s = getComponentFrom<Sprite>(_parentObject, "Sprite");
	if(s != NULL)
	{
		this->width = s->getWidth();
		this->height = s->getHeight();
	}
	else
	{
		this->width = 0;
		this->height = 0;
	}
}

void SquareCollider::move(int mx, int my)
{
	this->dx = mx;
	this->dy = my;
}

void SquareCollider::setSize(int w, int h)
{
    if(w < 0 || h < 0)  return;

	this->width = w;
	this->height = h;
}

void SquareCollider::update()
{
	Object* _parentObject = static_cast<Object*>(this->parentObject);
	Transform *t = getComponentFrom<Transform>(_parentObject, "Transform");

	this->x = t->coordX + this->dx;
    this->y = t->coordY + this->dy;
}

int SquareCollider::getX()
{
    return this->x;
}

int SquareCollider::getY()
{
    return this->y;
}

int SquareCollider::getWidth()
{
    return this->width;
}

int SquareCollider::getHeight()
{
    return this->height;
}

bool SquareCollider::collidedWith(SquareCollider* that)
{
	Point SS = {(float)this->x,(float)this->y};				/**< Upper Left */
	Point SSO = {(float)that->getX(), (float)that->getY()};

	Point DJ = {(float)(this->x + this->width), (float)(this->y + this->height)};	/**< Lower Right */
	Point DJO = {(float)(that->getX() + that->getWidth()), (float)(that->getY() + that->getHeight())};

	if(!(SS.x > DJO.x || DJ.x < SSO.x || DJ.y < SSO.y || SS.y > DJO.y))
		return true;

	return false;
}

Vector2 SquareCollider::getCollisionNormal(SquareCollider* that)
{
	int mIndex = 4;
	int dist[5];

	Point SS = {(float)this->x,(float)this->y};										/**< Upper Left */
	Point DJ = {(float)(this->x + this->width), (float)(this->y + this->height)};	/**< Lower Right */

	Point SSO = {(float)that->getX(), (float)that->getY()};
	Point DJO = {(float)(that->getX() + that->getWidth()), (float)(that->getY() + that->getHeight())};

	dist[0] = abs(SS.x - DJO.x);
	dist[1] = abs(SSO.x - DJ.x);
	dist[2] = abs(SS.y - DJO.y);
	dist[3] = abs(DJ.y - SSO.y);
	dist[4] = 2e30;	/**< Impossible value to attain, just for calculating the minimal distance */

	for(int i = 0; i <= 3; ++i)
		if(dist[i] < dist[mIndex]) mIndex = i;


	switch(mIndex)
	{
	case 0:
		return Vector2(-1, 0);
	case 1:
		return Vector2(1, 0);
	case 2:
		return Vector2(0, -1);
	case 3:
		return Vector2(0, 1);
	}

	return Vector2(0, 0);
}
