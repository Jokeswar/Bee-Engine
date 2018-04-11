#include "Component.h"

Component::Component()
{
	parentObject = NULL;
}

Component::~Component() {}

Component& Component::operator=(const Component& that)
{
    this->id = that.id;
    this->name = that.name;
    this->parentObject = that.parentObject;

    return *this;
}

void Component::update()
{
    return;
}

