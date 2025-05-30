#pragma once
#include "../utils/Vector2.h"
#include "../entities/Entity.h"
#include "Components.h"

class PositionComponent;

class VelocityComponent : public Component
{

public:
	VelocityComponent() : speed{ 1.f } {}
	VelocityComponent(float _speed) : speed{ _speed } {}
	
	void setVelocity(float x, float y) 
	{
		velocityDirection.x = x; 
		velocityDirection.y = y;
	}
	const Vector2f& getVelocity() const { return velocityDirection; }


	

	ComponentID getID() override { return ComponentID::VELOCITY; }

	float getSpeed() { return speed; }

private:
	Vector2f velocityDirection;
	float speed;

};