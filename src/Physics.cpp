#include "Physics.h"
#include "Object.h"
#include "Transform.h"

Physics::Physics()
{
	this->name = "Physics";
	this->id = 5;

	this->velocity = {0.0, 0.0};
	this->acceleration = {0.0, 0.0};
	this->isFixed = false;
	this->mass = 1.0;
	return;
}

Physics::Physics(void* parent)
{
	this->name = "Physics";
	this->id = 5;
	this->parentObject = parent;

	this->velocity = {0.0, 0.0};
	this->acceleration = {0.0, 0.0};
	this->isFixed = false;
	this->mass = 1.0;
	return;
}

Physics::~Physics()
{
	//dtor
}

void Physics::setVelocity(Vector2 vel)
{
	velocity = vel;
	velocity.y = -velocity.y;	/**< SDL display coordinate is down-right based, for positive y, image goes down instead of up*/
}

Vector2 Physics::getVelocity()
{
	return velocity;
}

void Physics::setAcceleration(Vector2 acc)
{
	acceleration = acc;
	acceleration.y = -acceleration.y;	/**< SDL display coordinate is down-right based, for positive y, image goes down instead of up*/
}

Vector2 Physics::getAcceleration()
{
	return acceleration;
}
