#include "../../include/core/Command.h"
#include "../../include/core/Game.h"
#include "../../include/utils/ArchetypeManager.h"
#include <iostream>
#include <cmath>


void MoveRightCommand::execute(Game& game)
{
	auto velocity = game.getPlayer()->getComponent<VelocityComponent>(ComponentID::VELOCITY);
	velocity->setVelocity(1.f, velocity->getVelocity().y);
}

void MoveLeftCommand::execute(Game& game)
{
	auto velocity = game.getPlayer()->getComponent<VelocityComponent>(ComponentID::VELOCITY);
	velocity->setVelocity(-1.f, velocity->getVelocity().y);
}

void MoveUpCommand::execute(Game& game)
{
	auto velocity = game.getPlayer()->getComponent<VelocityComponent>(ComponentID::VELOCITY);

	velocity->setVelocity(velocity->getVelocity().x, -1.f);
}

void MoveDownCommand::execute(Game& game)
{
	auto velocity = game.getPlayer()->getComponent<VelocityComponent>(ComponentID::VELOCITY);

	velocity->setVelocity(velocity->getVelocity().x, 1.f);
}

void AttackCommand::execute(Game& game)
{
	auto state = game.getPlayer()->getComponent<PlayerStateComponent>(ComponentID::STATE);

	state->setAttacking(true);
}

void ShoutCommand::execute(Game& game)
{
	auto state = game.getPlayer()->getComponent<PlayerStateComponent>(ComponentID::STATE);

	state->setShouting(true);
}