#pragma once
#include "../graphics/Window.h"
#include "../utils/Rectangle.h"
#include "../../include/components/GraphicsComponent.h"
#include "../components/ColliderComponent.h"
#include "../utils/Bitmask.h"
#include "../components/TTLComponent.h"
#include <memory>

class PositionComponent;
class InputComponent;
class VelocityComponent;
class PlayerStateComponent;

enum class ArchetypeID;

using EntityID = unsigned int;
enum class EntityType
{
	UNDEFINED = -1,
	PLAYER = 0,
	POTION = 1,
	LOG = 2,
	FIRE = 3
};

class Game; //forward declaration

class Entity
{
public:

	//Constructors and Desctrutors
	Entity();
	Entity(EntityType et);
	~Entity();

	//Init and update functions
	virtual void init(const std::string& textureFile, float scale, std::shared_ptr<GraphicsComponent> _graphics);
	void initSpriteSheet(const std::string& spriteSheetFile);
	void addComponent(std::shared_ptr<Component> c);
	template <typename T>
	std::shared_ptr<T> getComponent(ComponentID id) {
		auto it = mapComponent.find(id);
		if (it != mapComponent.end()) {
			return std::dynamic_pointer_cast<T>(it->second);
		}
		return nullptr;
	}
	void setID(EntityID entId) { id = entId; }
	EntityID getID() const { return id; }
	void setPosition(float x, float y) ;
	Vector2f getPosition();
	EntityType getEntityType() const { return type; }
	Bitmask getComponentSet() { return componentSet; }

	std::shared_ptr<PositionComponent> getPositionComponent() { 
		auto position = getComponent<PositionComponent>(ComponentID::POSITION);
		return position;
	}
	std::shared_ptr<GraphicsComponent> getGraphicsComponent() { 
		auto graphics = getComponent<GraphicsComponent>(ComponentID::GRAPHICS);
		return graphics;
	}
	bool isDeleted() const { return deleted; }
	bool hasComponent(Bitmask mask) const { return componentSet.contains(mask); }
	void markDeleted() { deleted = true; }


	virtual std::shared_ptr<ColliderComponent> getColliderComponent();

	void setArchetypeID(ArchetypeID _archetypeID);
	ArchetypeID getArchetypeID() const;


protected:

	EntityType type;
	EntityID id;

	Bitmask componentSet;
	bool isSpriteSheet;

	// X.A Add a bool member variable "deleted" to this class.
	bool deleted;
	std::map<ComponentID, std::shared_ptr<Component>> mapComponent;


	ArchetypeID archetypeID;
};