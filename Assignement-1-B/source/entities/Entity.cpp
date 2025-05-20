#include "../../include/entities/Entity.h"
#include "../../include/graphics/Window.h"
#include "../../include/core/Game.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/utils/ArchetypeManager.h"
#include <iostream>


Entity::Entity() :
	id(0),
	type(EntityType::UNDEFINED),
	componentSet(0),
	deleted(false),
	isSpriteSheet(true)
{
	addComponent(std::make_shared<PositionComponent>());
}


Entity::Entity(EntityType et) :
	id(0),
	type(et),
	componentSet(0),
	deleted(false),
	isSpriteSheet(true)
{
	addComponent(std::make_shared<PositionComponent>());
}


Entity::~Entity()
{
}

void Entity::init(const std::string& textureFile, float scale, std::shared_ptr<GraphicsComponent> _graphicsPointer)
{
	addComponent(_graphicsPointer);
	auto graphics = getComponent<GraphicsComponent>(ComponentID::GRAPHICS);
	if (graphics) {
		graphics->init(textureFile, scale);
	}


}

void Entity::initSpriteSheet(const std::string& spriteSheetFile)
{
	auto graphics = getComponent<GraphicsComponent>(ComponentID::GRAPHICS);
	if (graphics) {
		graphics->initSpriteSheet(spriteSheetFile);
		Vector2f bboxSize = Vector2f(
			graphics->getSpriteSize().x * graphics->getSpriteScale().x,
			graphics->getSpriteSize().y * graphics->getSpriteScale().y);
		auto collider = std::make_shared<ColliderComponent>();
		collider->setBboxSize(bboxSize);
		addComponent(collider);
	}

}

Vector2f Entity::getPosition()
{
	auto pos = getComponent<PositionComponent>(ComponentID::POSITION);
	if (pos) return pos->getPosition();
	return Vector2f(0, 0);
}


void Entity::setPosition(float x, float y)
{
	auto pos = getComponent<PositionComponent>(ComponentID::POSITION);
	if (pos) {
		pos->setPosition(x, y);
	}
	auto graphics = getComponent<GraphicsComponent>(ComponentID::GRAPHICS);
	if (graphics) {
		graphics->setPosition(Vector2f(x, y));
	}
}


void Entity::addComponent(std::shared_ptr<Component> c)
{
	mapComponent.insert({ c->getID(), c });
	componentSet.turnOnBit(static_cast<unsigned int>(c->getID()));
}

std::shared_ptr<ColliderComponent> Entity::getColliderComponent()
{
	return getComponent<ColliderComponent>(ComponentID::COLLIDER);
}

void Entity::setArchetypeID(ArchetypeID _archetypeID)
{
	archetypeID = _archetypeID;
}

ArchetypeID Entity::getArchetypeID() const
{
	return archetypeID;
}


