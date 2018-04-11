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

		/**< Scale is between 0 and 1, 1 - original size, 0 - doesn't appear on the screen */
		float scaleX;
		float scaleY;
};

#endif // TRANSFORM_H
