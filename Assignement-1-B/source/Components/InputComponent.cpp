#include "../../include/components/InputComponent.h"
#include "../../include/core/Command.h"
#include "../../include/core/Game.h"
#include "../../include/core/InputHandler.h"

#include <memory>


PlayerInputComponent::PlayerInputComponent()
{
	playerInput = std::make_shared<PlayerInputHandler>();
}

ComponentID PlayerInputComponent::getID()
{
	return ComponentID::INPUT;
}

std::shared_ptr<PlayerInputHandler> PlayerInputComponent::getPlayerInputHander()
{
	return playerInput;
}