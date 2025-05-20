#include "../graphics/Window.h"
#include "../core/Board.h"
#include "../entities/Player.h"
#include <memory>
#include "../../include/systems/Systems.h"
#include "../../include/utils/EcsSystemHandler.h"
#include <functional>
#include <map>

class GraphicsComponent;
class InputHandler;
class System;


enum class ArchetypeID;
enum ControlType
{
	UNDEFINED = -1,
	WASD = 0,
	ARROWS = 1,
};

enum EcsMethod
{
	bigArray = 0,
	archetypes = 1,
	packedArray = 2
};


class Game
{
public:

	const int spriteWH = 50;
	const float tileScale = 2.0f;
	const float itemScale = 1.0f;

	Game();
	~Game();

	void init(std::vector<std::string> lines);
	void addEntity(std::shared_ptr<Entity> newEntity);

	void buildBoard(size_t width, size_t height);
	void initWindow(size_t width, size_t height);

	void handleInput();
	void update(float elapsed);
	void render(float elapsed);
	Window* getWindow() { return &window; }

	sf::Time getElapsed() const { return gameClock.getElapsedTime(); };
	void setFPS(int FPS);
	void togglePause()
	{
		paused = !paused;
	}
	void toggleControl();

	std::shared_ptr<InputSystem> system;

	bool isPaused() const { return paused; }

	EcsMethod getEcsMethod() { return ecsMethod; }

	int getCurrentControl() { return currentControl; }

	EcsSystemHandler getEcsManager() { return ecsManager; }

	std::shared_ptr<PackedArrayManager> getPackedArrayManager() { return ecsManager.getPackedArrayManager(); }


	std::vector<std::shared_ptr<Entity>> getEntities() { return entities; }
	bool getDrawDebug() { return drawDebug; }

	//  IV.A (2/2) Write a function that returns the shared pointer of the player of the game.
	std::shared_ptr<Player> getPlayer() { return player; }

	EntityID getIDCounter();
	std::shared_ptr<Entity> getEntity(unsigned int idx);

	template <typename T>
	std::shared_ptr<T> buildEntityAt(const std::string& filename, int col, int row, std::shared_ptr<GraphicsComponent> graphicsComponentPointer);


private:

	Window window;
	bool paused;
	sf::Clock gameClock;
	sf::Time elapsed;

	std::unique_ptr<Board> board;

	std::vector<std::shared_ptr<Entity>> entities;

	EntityID id;

	std::shared_ptr<Player> player;

	std::unique_ptr<InputHandler> inputHandler;


	bool drawDebug;


	ControlType currentControl;

	EcsSystemHandler ecsManager;
	AchievementManager achievementManager;

	EcsMethod ecsMethod;

	std::unordered_map<EntityType, std::function<void(std::shared_ptr<Entity>)>> collisionCallbacks;
};

