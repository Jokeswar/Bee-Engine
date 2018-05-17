#ifndef OBJECT_H
#define OBJECT_H

#include <string>

#include "Music.h"
#include "SoundEffect.h"
#include "Physics.h"
#include "Sprite.h"
#include "Transform.h"

#include "Utility.h"
#include "Component.h"

class Object
{
    public:
        Object(int, int);
        ~Object();

        static int getNumberOfObjects();

        void addComponent(Component*);

        template<typename returnType>
        returnType* getComponent(unsigned int);

        template<typename returnType>
        returnType* getComponent(std::string);

        void update();

		std::vector<Component*> components;
		std::string entityName;

    private:
    	static int numberOfObjects;
};

/// For now it stays here until i figure the shitty function member
/// @todo the class specific function doesn't link or smth goes wrong
template<typename returnType>
returnType* getComponentFrom(Object* obj, std::string name)
{
 	for(unsigned int i = 0; i < obj->components.size(); ++i)
		if(obj->components[i]->name.compare(name) == 0) return static_cast<returnType*>(obj->components[i]);

	return NULL;
}
#endif // OBJECT_H
