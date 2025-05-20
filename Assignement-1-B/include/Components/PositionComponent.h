#pragma once
#include "../../include/utils/Vector2.h"
#include "../../include/Components/Components.h"


class PositionComponent : public Component
{
public:
	//PositionComponent();
	const Vector2f& getPosition() const { return position; }
	void setPosition(float x, float y)
	{
		position.x = x; position.y = y;
	}

	ComponentID getID() override
	{
		return ComponentID::POSITION;
	}

private:
	Vector2f position;

};