#include "../../include/systems/Systems.h"
#include "../../include/core/Game.h"
#include "../../include/entities/Player.h"
#include "../../include/components/InputComponent.h"
#include "../../include/core/InputHandler.h"
#include "../../include/core/Command.h"
#include <stdexcept>
#include <iostream>
#include <cmath>

void TTLSystem::update(Entity* entity, Game* game, float elapsedTime)
{
	if (entity->getComponent<TTLComponent>(ComponentID::TTL))
	{
		std::shared_ptr<TTLComponent> ttl = entity->getComponent<TTLComponent>(ComponentID::TTL);

		ttl->decrementTTL();
		if (ttl->getTTL() <= 0)
		{
			entity->markDeleted();
		}
	}
	
}

void InputSystem::update(Entity* entity, Game* game, float elapsedTime)
{	
	if (entity->getComponent<InputComponent>(ComponentID::INPUT))
	{
		auto velocity = entity->getComponent<VelocityComponent>(ComponentID::VELOCITY);
		auto inputBase = entity->getComponent<InputComponent>(ComponentID::INPUT);

		// Cast to PlayerInputComponent
		auto playerInput = std::dynamic_pointer_cast<PlayerInputComponent>(inputBase);
		if (playerInput)
		{
			if (velocity) {
				velocity->setVelocity(0.f, 0.f);
			}

			for (auto& command : playerInput->getPlayerInputHander()->handleInput())
			{
				command->execute(*game); 
			}
		}
	}
}

void MovementSystem::update(Entity* entity, Game* game, float elapsedTime)
{
	std::shared_ptr<VelocityComponent> velocity = entity->getComponent<VelocityComponent>(ComponentID::VELOCITY);
	std::shared_ptr<PositionComponent> position = entity->getComponent<PositionComponent>(ComponentID::POSITION);

	if (entity->getEntityType() == EntityType::FIRE)
	{
		position->setPosition(
			position->getPosition().x + (velocity->getVelocity().x * velocity->getSpeed() * elapsedTime),
			position->getPosition().y + (velocity->getVelocity().y * velocity->getSpeed() * elapsedTime)
		);
	}
	else
	{
		if (entity->getEntityType() == EntityType::FIRE)
		{
			if ((movement_x != 0 || movement_y != 0))
			{
				int positionIntX = static_cast<int>(position->getPosition().x);
				int positionIntY = static_cast<int>(position->getPosition().y);

				if (positionIntX == (int)target_x || positionIntY == (int)target_y)
				{
					movement_x = 0;
					movement_y = 0;
					return;
				}

				float magnitude = (float)sqrt(pow(movement_x, 2) + pow(movement_y, 2));
				float normalised_x = movement_x / magnitude;
				float normalised_y = movement_y / magnitude;

				velocity->setVelocity(normalised_x, normalised_y);
				position->setPosition(
					position->getPosition().x + (velocity->getVelocity().x * velocity->getSpeed() * elapsedTime),
					position->getPosition().y + (velocity->getVelocity().y * velocity->getSpeed() * elapsedTime)
				);
			}
		}
		else
		{
			if (velocity)
			{
				position->setPosition(
					position->getPosition().x + (velocity->getVelocity().x * velocity->getSpeed() * elapsedTime),
					position->getPosition().y + (velocity->getVelocity().y * velocity->getSpeed() * elapsedTime)
				);
			}
		}
	}
	
}

void GraphicsSystem::update(Entity* entity, Game* game, float elapsedTime)
{
	std::shared_ptr<GraphicsComponent> graphics = entity->getComponent<GraphicsComponent>(ComponentID::GRAPHICS);
	std::shared_ptr<PositionComponent> position = entity->getComponent<PositionComponent>(ComponentID::POSITION);
	
	graphics->update(game, elapsedTime, position->getPosition());
	graphics->draw(game->getWindow());
}

void ColliderSystem::update(Entity* entity, Game* game, float elapsedTime)
{
	std::shared_ptr<ColliderComponent> collider = entity->getComponent<ColliderComponent>(ComponentID::COLLIDER);
	

	collider->getBoundingBox().setTopLeft(entity->getPosition());
	collider->getBoundingBox().setBottomRight(Vector2f((entity->getPosition().x + collider->getBboxSize().x), (entity->getPosition().y + collider->getBboxSize().y)));
}

void PrintDebugSystem::update(Entity* entity, Game* game, float elapsedTime)
{
	std::shared_ptr<ColliderComponent> collider = entity->getComponent<ColliderComponent>(ComponentID::COLLIDER);
	collider->draw(game->getWindow());
}

void GameplaySystem::update(Entity* entity, Game* game, float elapsedTime)
{
	std::shared_ptr<PlayerStateComponent> state = entity->getComponent<PlayerStateComponent>(ComponentID::STATE);

	state->update(*entity, game, elapsedTime);
}
