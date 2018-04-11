#ifndef COMPONENT_H
#define COMPONENT_H

#include "Utility.h"


/**< @note Every user-made component must be derived from this class*/
class Component
{
	public:
		Component();
		virtual ~Component();
		virtual void update();

		Component& operator=(const Component& that);
		void* getParent();

		std::string name;
		unsigned int id;
		void* parentObject;
};

#endif // COMPONENT_H
