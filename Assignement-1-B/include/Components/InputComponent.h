#pragma once

#include <memory>
#include "Components.h"

class PlayerInputHandler;

class InputComponent : public Component {
public:
    virtual ~InputComponent() = default;
    
};

class PlayerInputComponent : public InputComponent {

public:

    PlayerInputComponent();

    ComponentID getID() override;

    std::shared_ptr<PlayerInputHandler> getPlayerInputHander();

private:
    std::shared_ptr<PlayerInputHandler> playerInput;
};
