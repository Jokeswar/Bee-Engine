#include "SquareCollider.h"

#include "Object.h"

void onCollisionFunctionStub(Object* that){}    /**< So the engine's on collision call does not fail by calling a null pointer */

SquareCollider::SquareCollider()	/**< Stub function for creating component */
{
	this->id = 2;
	this->name = "SquareCollider";
	onCollisionFunction = &onCollisionFunctionStub;

    return;
}

SquareCollider::SquareCollider(void* parent)
{
	this->id = 2;
	this->name = "SquareCollider";
	this->parentObject = parent;
	this->onCollisionFunction = &onCollisionFunctionStub;

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
	this->x = mx;
	this->y = my;
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

	this->x = t->coordX;
    this->y = t->coordY;
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

	if(SS.x <= DJO.x && SS.y <= DJO.y &&	/**< Upper left corner */
	   DJ.x >= SSO.x && SS.y <= DJO.y)		/**< Lower right corner */
		return true;

	return false;
}

Vector2 SquareCollider::getCollisionNormal(SquareCollider* that)
{
	Point SS = {(float)this->x,(float)this->y};										/**< Upper Left */
	Point DJ = {(float)(this->x + this->width), (float)(this->y + this->height)};	/**< Lower Right */
	Point CenterOfGravity = {(SS.x + DJ.x)/2, (SS.y + DJ.y)/2};

	Point SSO = {(float)that->getX(), (float)that->getY()};
	Point DJO = {(float)(that->getX() + that->getWidth()), (float)(that->getY() + that->getHeight())};

	Point UpperFace = {(SSO.x + DJO.x)/2, SSO.y};
	Point RightFace = {DJO.x, (SSO.y + DJO.y)/2};
	Point LowerFace = {(SSO.x + DJO.x)/2, DJO.y};
	Point LeftFace = {DJO.x, (SSO.y + DJO.y)/2};

	float dist[4];
	int mIndex = 0;

	dist[0] = CenterOfGravity.distanceTo(UpperFace);
	dist[1] = CenterOfGravity.distanceTo(RightFace);
	dist[2] = CenterOfGravity.distanceTo(LowerFace);
	dist[3] = CenterOfGravity.distanceTo(LeftFace);

	for(int i = 0; i < 4; ++i)
		if(dist[i] < dist[mIndex]) mIndex = i;

	switch(mIndex)
	{
	case 0:
		return Vector2{0, 1};
	case 1:
		return Vector2{1, 0};
	case 2:
		return Vector2{0, -1};
	case 3:
		return Vector2{-1, 0};
	}

	return Vector2(0, 0);
}
