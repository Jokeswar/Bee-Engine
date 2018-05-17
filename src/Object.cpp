#include "Object.h"

#include "Bee.h"
#include "Utility.h"
#include "Component.h"

#include "Music.h"
#include "SoundEffect.h"
#include "Physics.h"
#include "Sprite.h"
#include "Transform.h"
#include "SquareCollider.h"

int Object::numberOfObjects = 0;

Object::Object(int x = 0, int y = 0)
{
    numberOfObjects++;
    Bee::gameWorld->addObject(this);

    Transform* t = new Transform;
    t->coordX = x;
    t->coordY = y;
    this->addComponent(t); /**< We need position, rotation and scale*/
}

int Object::getNumberOfObjects()
{
	return numberOfObjects;
}

Object::~Object()
{
	numberOfObjects--;

    for(unsigned int i = 0; i < components.size(); ++i)
		delete components[i];
}

void Object::update()
{
	for(unsigned int i = 0; i < components.size(); ++i)
		components[i]->update();
}

/********************************************//**
 *	Here starts the component implementation
 ***********************************************/

void Object::addComponent(Component* current)
{
 	components.push_back(current);
}

template<typename returnType>
returnType* Object::getComponent(unsigned int id)
{
 	for(unsigned int i = 0; i < components.size(); ++i)
		if(components[i]->id == id) return static_cast<returnType*>(components[i]);

	return NULL;
}

template<typename returnType>
returnType* Object::getComponent(std::string name)
{
 	for(unsigned int i = 0; i < components.size(); ++i)
		if(components[i]->name.compare(name) == 0) return static_cast<returnType*>(components[i]);

	return NULL;
}
