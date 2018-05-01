#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.h"

class Transform: public Component
{
	public:
		Transform();
		~Transform();

		float coordX;
		float coordY;

		float angle;

		float scaleX;
		float scaleY;
};

#endif // TRANSFORM_H
