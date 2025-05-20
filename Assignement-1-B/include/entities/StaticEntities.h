#pragma once
#include "Entity.h"
#include "../../include/components/PositionComponent.h"

class GameComponent;
class GraphicsComponent;

class Potion : public Entity
{
public:
	Potion() : Entity(EntityType::POTION) {}
	~Potion() {}

	void init(const std::string& textureFile, float scale, std::shared_ptr<GraphicsComponent> _graphicsPointer) override
	{

		Entity::init(textureFile, scale, _graphicsPointer);
		archetypeID = ArchetypeID::StaticEntity;
		auto graphics = getComponent<GraphicsComponent>(ComponentID::GRAPHICS);
		Vector2f bboxSize = Vector2f(
			graphics->getTextureSize().x * graphics->getScale().x,
			graphics->getTextureSize().y * graphics->getScale().y);
		auto collider = std::make_shared<ColliderComponent>();
		addComponent(collider);
		collider->setBboxSize(bboxSize);
		
		
		if (!getColliderComponent()) return;
		getColliderComponent()->setBoundingBoxLocation(getPosition());
	}

	int getHealth() const { return potionHealth; }

protected:
	const int potionHealth = 10;
};


class Log : public Entity
{
public:
	Log() : Entity(EntityType::LOG) {}
	~Log() {}

	void init(const std::string& textureFile, float scale, std::shared_ptr<GraphicsComponent> _graphicsPointer) override
	{

		Entity::init(textureFile, scale, _graphicsPointer);
		archetypeID = ArchetypeID::StaticEntity;

		auto graphics = getComponent<GraphicsComponent>(ComponentID::GRAPHICS);
		Vector2f bboxSize = Vector2f(
			graphics->getTextureSize().x * graphics->getScale().x,
			graphics->getTextureSize().y * graphics->getScale().y);
		auto collider = std::make_shared<ColliderComponent>();
		addComponent(collider);
		collider->setBboxSize(bboxSize);


		if (!getColliderComponent()) return;
		getColliderComponent()->setBoundingBoxLocation(getPosition());
	}

	int getWood() const { return woodAdded; }


protected:
	const int woodAdded = 15;
};