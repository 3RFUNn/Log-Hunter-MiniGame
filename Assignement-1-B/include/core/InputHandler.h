#include <memory>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>

// forward declaration of Command
class Command;
class Game;

class InputHandler
{
public:
	InputHandler();

	std::shared_ptr<Command> handleInput();

private:
	std::shared_ptr<Command> pause;
	std::shared_ptr<Command> enter;
};

class PlayerInputHandler
{
public:
	PlayerInputHandler();

	std::vector<std::shared_ptr<Command>> handleInput();
	std::vector<std::shared_ptr<Command>> commands;

	std::map<sf::Keyboard::Key, std::shared_ptr<Command>> activeCommands;
	void updateKeys(int);

private:
	std::shared_ptr<Command> clickCommand;
	std::shared_ptr<Command> moveRightCommand;
	std::shared_ptr<Command> moveLeftCommand;
	std::shared_ptr<Command> moveUpCommand;
	std::shared_ptr<Command> moveDownCommand;
	std::shared_ptr<Command> attackCommand;
	std::shared_ptr<Command> shoutCommand;
};