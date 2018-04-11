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

    for(unsigned int i = 0; i < componenets.size(); ++i)
		delete componenets[i];
}

void Object::update()
{
	for(unsigned int i = 0; i < componenets.size(); ++i)
		componenets[i]->update();
}

/********************************************//**
 *	Here starts the component implementation
 ***********************************************/

void Object::addComponent(Component* current)
{
 	componenets.push_back(current);
}
///@todo The linker has a few problems, it says that the function with random type(i.e. template argument) is undefined
template<typename returnType>
returnType* Object::getComponent(unsigned int id)
{
 	for(unsigned int i = 0; i < componenets.size(); ++i)
		if(componenets[i]->id == id) return static_cast<returnType*>(componenets[i]);

	return NULL;
}

 template<typename returnType>
 returnType* Object::getComponent(std::string name)
{
 	for(unsigned int i = 0; i < componenets.size(); ++i)
		if(componenets[i]->name.compare(name) == 0) return static_cast<returnType*>(componenets[i]);

	return NULL;
}
