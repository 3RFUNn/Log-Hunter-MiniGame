#pragma once
#include "Entity.h"
#include "../components/HealthComponent.h"
#include "../components/VelocityComponent.h"
#include "../components/LogicComponent.h"
#include "../../include/systems/Subject.h"

class Fire;
class InputComponent;
class LogicComponent;

// VI.A (2/2): Add a forward declaration to the class PlayerInputHandler
class PlayerInputHandler;

class Player :  public Entity
{
public:

	const float playerSpeed = 100.f;
	const int startingHealth = 60;
	const int maxHealth = 100;
	const int maxWood = 100;
	const int shootingCost = 20;
	const float fireSpeed = 200.f;
	const float shootCooldownTime = 3.f; //in seconds

	Player();
	~Player();

	std::shared_ptr<InputComponent> getInputComponent() 
	{
		return playerInput;
	}


	std::shared_ptr<HealthComponent> getHealthComp() { return healthComponent; }


	bool hasSpriteSheet() const { return isSpriteSheet; }

	void positionSprite(int row, int col, int spriteWH, float tileScale);

	void setGraphicsPointer(std::shared_ptr<GraphicsComponent> _graphics) { 
		addComponent(_graphics);
	}

	bool intersects(Entity& other);

	Subject& getPotionCollected() { return potionCollected; }
	Subject& getShoutTriggered() { return shoutTriggered; }
	void collectPotion();
	void shoutTrigger();

	void handlePotionCollision(std::shared_ptr<Entity> _entity);
	void handleLogCollision(std::shared_ptr<Entity> _entity);

private:

	// VI.A (1/2): Declare a unique pointer to a player input handler.
	
	std::shared_ptr<InputComponent> playerInput;
	std::shared_ptr<HealthComponent> healthComponent;
	std::shared_ptr<VelocityComponent> velocity;
	std::shared_ptr<PlayerStateComponent> state;

	Subject potionCollected;
	Subject shoutTriggered;

};

