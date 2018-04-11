#include "Utility.h"
#include "Transform.h"

Transform::Transform()
{
	this->coordX = 0.0;
	this->coordY = 0.0;
	this->angle = 0.0;
	this->scaleX = 1.0;
	this->scaleY = 1.0;

	this->id = 0;
	this->name = "Transform";
}

Transform::~Transform()
{
	//dtor
}
