#include "../../include/core/InputHandler.h"
#include "../../include/core/Command.h"
#include <iostream>

InputHandler::InputHandler()
{
	pause = std::make_shared<PauseCommand>();
    enter = std::make_shared<SwitchCommand>();
}

PlayerInputHandler::PlayerInputHandler()
{
    moveRightCommand = std::make_shared<MoveRightCommand>();
    moveLeftCommand = std::make_shared<MoveLeftCommand>();
    moveUpCommand = std::make_shared<MoveUpCommand>();
    moveDownCommand = std::make_shared<MoveDownCommand>();
    attackCommand = std::make_shared<AttackCommand>();
    shoutCommand = std::make_shared<ShoutCommand>();

    activeCommands.insert(std::make_pair(sf::Keyboard::W, moveUpCommand));
    activeCommands.insert(std::make_pair(sf::Keyboard::A, moveLeftCommand));
    activeCommands.insert(std::make_pair(sf::Keyboard::S, moveDownCommand));
    activeCommands.insert(std::make_pair(sf::Keyboard::D, moveRightCommand));
}

std::shared_ptr<Command> InputHandler::handleInput()
{
    static bool isEscapePressed = false;
    static bool isEnterPressed = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        if (!isEscapePressed)
        {
            isEscapePressed = true;
            return pause;
        }
    }
    else
    {
        isEscapePressed = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        if (!isEnterPressed)
        {
            isEnterPressed = true;
            return enter;
        }
    }
    else
    {
        isEnterPressed = false;
    }


    return nullptr;
}

std::vector <std::shared_ptr<Command>> PlayerInputHandler::handleInput()
{
    commands.clear();

    for (auto const& command : activeCommands)
    {
        if (sf::Keyboard::isKeyPressed(command.first))
        {
            commands.push_back(command.second);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        commands.push_back(attackCommand);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        commands.push_back(shoutCommand);
    }
    return commands;
}

void PlayerInputHandler::updateKeys(int currentControl)
{
    activeCommands.clear();
    if (currentControl == 0)
    {
        activeCommands.insert(std::make_pair(sf::Keyboard::W, moveUpCommand));
        activeCommands.insert(std::make_pair(sf::Keyboard::A, moveLeftCommand));
        activeCommands.insert(std::make_pair(sf::Keyboard::S, moveDownCommand));
        activeCommands.insert(std::make_pair(sf::Keyboard::D, moveRightCommand));
    }
    else if (currentControl == 1)
    {
        activeCommands.insert(std::make_pair(sf::Keyboard::Up, moveUpCommand));
        activeCommands.insert(std::make_pair(sf::Keyboard::Left, moveLeftCommand));
        activeCommands.insert(std::make_pair(sf::Keyboard::Down, moveDownCommand));
        activeCommands.insert(std::make_pair(sf::Keyboard::Right, moveRightCommand));
    }
    
}