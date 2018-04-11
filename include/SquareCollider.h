#ifndef SQUARECOLLIDER_H
#define SQUARECOLLIDER_H

#include "Utility.h"
#include "Component.h"
#include "Object.h"

class SquareCollider: public Component
{
	public:
		SquareCollider();
		SquareCollider(void*);

		void update() override;
		void move(int, int);
		void setSize(int, int);

		int getX();
        int getY();
        int getWidth();
        int getHeight();

        bool collidedWith(SquareCollider*);
        Vector2 getCollisionNormal(SquareCollider*);

        void (*onCollisionFunction)(Object*);

	private:
		int x;
		int y;
		int width;
		int height;
};

#endif // SQUARECOLLIDER_H
