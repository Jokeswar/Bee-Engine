#ifndef PHYSICS_H
#define PHYSICS_H

#include "Component.h"
#include "Utility.h"

#define TIMESTEP 1.0/30.0

class Physics: public Component
{
	public:
		Physics();
		Physics(void*);
		~Physics();

		void setVelocity(Vector2);
		void setAcceleration(Vector2);
		Vector2 getVelocity();
		Vector2 getAcceleration();

		bool isFixed;
		float mass;
		float impactRetentionCoefficient;

	private:
		Vector2 velocity;
		Vector2 acceleration;
};

#endif // PHYSICS_H
