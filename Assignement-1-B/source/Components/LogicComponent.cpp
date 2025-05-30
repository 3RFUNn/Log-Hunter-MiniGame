#include "../../include/components/LogicComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/entities/Entity.h"
#include "../../include/core/Game.h"
#include "../../include/entities/Player.h"
#include "../../include/entities/Fire.h"
#include "../../include/utils/ArchetypeManager.h"
#include "../../include/utils/Locator.h"



std::shared_ptr<Fire> PlayerStateComponent::createFire(Entity* player) const
{
	auto fireEntity = std::make_shared<Fire>();

	Vector2f pos{ player->getPosition().x + player->getGraphicsComponent()->getTextureSize().x * 0.5f, player->getPosition().y + player->getGraphicsComponent()->getTextureSize().y * 0.5f };
	fireEntity->init("img/fire.png", 1.0f, std::make_shared<SpriteGraphics>());
	fireEntity->setPosition(pos.x, pos.y);
	Vector2f vel(fireSpeed, 0.f);

	auto playerGraphics = player->getComponent<GraphicsComponent>(ComponentID::GRAPHICS);
	if (playerGraphics->getSpriteDirection() == Direction::Left) vel.x = vel.x * -1.0f;

	auto velocity = fireEntity->getComponent<VelocityComponent>(ComponentID::VELOCITY);
	velocity->setVelocity(vel.x, vel.y);

	ServiceLocator::getAudioManager()->playSound("FireBall.flac");
	return fireEntity;
}

void PlayerStateComponent::update(Entity& entity, Game* game, float elapsed)
{	



	if (entity.getEntityType() == EntityType::PLAYER)
	{
	Player* player = dynamic_cast<Player*>(&entity);
	{
		// Check if attacking animation is finished
		if (attacking && player->getGraphicsComponent()->isPlaying() == false)
		{
			setAttacking(false);
			axeAudio = false;
		}
		// Check if shouting animation is finished
		if (shouting && player->getGraphicsComponent()->isPlaying() == false)
		{
			setShouting(false);
		}

		if (attacking)
		{
			player->getGraphicsComponent()->setAnimation("Attack", true, false);
			
			if (player->getGraphicsComponent()->getSpriteSheet()->getCurrentAnim()->isInAction() && axeAudio == false)
			{
				ServiceLocator::getAudioManager()->playSound("AxeSwing.wav");
				axeAudio = true;
			}
		}

		else if (shouting)
		{
			player->getGraphicsComponent()->setAnimation("Shout", true, false);
		}

		else
		{
			if (velocity->getVelocity().x > 0)
			{
				player->getGraphicsComponent()->setAnimation("Walk", true, true);
				player->getGraphicsComponent()->setSpriteDirection(Direction::Right);
			}

			else if (velocity->getVelocity().x < 0)
			{
				player->getGraphicsComponent()->setAnimation("Walk", true, true);
				player->getGraphicsComponent()->setSpriteDirection(Direction::Left);
			}

			else if (velocity->getVelocity().x == 0 && velocity->getVelocity().y == 0 && !attacking && !shouting)
			{
				player->getGraphicsComponent()->setAnimation("Idle", true, true);
			}

			else if (velocity->getVelocity().y != 0)
			{
				player->getGraphicsComponent()->setAnimation("Walk", true, true);
			}
		}

		if (shootCooldown > 0)
		{
			shootCooldown = shootCooldown - elapsed;
		}
		if (shouting && player->getGraphicsComponent()->isInAction() && wood >= player->shootingCost && shootCooldown <= 0)
		{
			player->shoutTrigger();
			game->addEntity(createFire(player));
			wood = wood - shootingCost;
			shootCooldown = shootCooldownTime;
		}

		if (attacking && player->getGraphicsComponent()->isPlaying() == false)
		{
			setAttacking(false);
			axeAudio = false;
		}
		if (shouting && player->getGraphicsComponent()->isPlaying() == false)
		{
			setShouting(false);
		}
	}
	}
		
}

void PlayerStateComponent::addWood(int w)
{
	wood += w;
	if (wood > maxWood) wood = maxWood;
	if (wood < 0) wood = 0;
	std::cout << "Collide with wood (Wood collected: " << w << ", Total Player Wood: " << wood << ")" << std::endl;
}

