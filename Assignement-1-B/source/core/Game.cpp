#include "../../include/core/Game.h"
#include "../../include/entities/Fire.h"
#include "../../include/entities/StaticEntities.h"
#include "../../include/core/InputHandler.h"
#include "../../include/core/Command.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/LogicComponent.h"
#include "../../include/systems/Systems.h"
#include "../../include/systems/Observer.h"
#include "../../include/components/InputComponent.h"
#include "../../include/utils/Locator.h"
#include <iostream>

Game::Game() : paused(false), drawDebug(true), ecsMethod(EcsMethod::bigArray)
{
	inputHandler = std::make_unique<InputHandler>();
	ecsManager.populateECS(*this);
	std::cout << "WASD  Control" << std::endl;
	ServiceLocator::ServiceLocator();
}

Game::~Game()
{
}

void Game::toggleControl()
{
	switch (currentControl)
	{
	case WASD:
		currentControl = ARROWS;
		std::cout << "Switched to ARROWS Control" << std::endl;
		break;

	case ARROWS:
		currentControl = WASD;
		std::cout << "Switched to WASD Control" << std::endl;
		break;
	}

	auto inputComponent = std::dynamic_pointer_cast<PlayerInputComponent>(getPlayer()->getInputComponent());
	if (inputComponent)
	{
		inputComponent->getPlayerInputHander()->updateKeys(currentControl);
	}
	else
	{
		std::cerr << "Warning: Player has no PlayerInputComponent!" << std::endl;
	}
}


template <typename T>
std::shared_ptr<T> Game::buildEntityAt(const std::string& filename, int col, int row, std::shared_ptr<GraphicsComponent> graphicsComponentPointer)
{
	auto ent = std::make_shared<T>();
	float x = col * spriteWH * tileScale;
	float y = row * spriteWH * tileScale;
	float cntrFactor = (tileScale - itemScale) * spriteWH * 0.5f;

	ent->init(filename, itemScale, graphicsComponentPointer);
	ent->setPosition(x + cntrFactor, y + cntrFactor);
	
	return ent;
}

void Game::buildBoard(size_t width, size_t height)
{
	board = std::make_unique<Board>(width, height);
}

void Game::initWindow(size_t width, size_t height)
{
	int wdt = static_cast<int>(width * spriteWH * tileScale);
	int hgt = static_cast<int>(height * spriteWH * tileScale);
	window.setSize(sf::Vector2u(wdt, hgt));
	window.redraw();
}

void Game::init(std::vector<std::string> lines)
{
	size_t h = lines.size() - 1;
	if (h < 0)
		throw std::exception("No data in level file");
	size_t w = -1;

	// Load the font for the window and set its title
	window.loadFont("font/AmaticSC-Regular.ttf");
	window.setTitle("Mini-Game");
	
	auto it = lines.cbegin();
	int row = 0;
	while (it != lines.cend())
	{
		int col = 0;

		if(w == -1)
		{
			w = it->size();
			buildBoard(w, h);
			initWindow(w, h);		
		}
		
		std::string::const_iterator is = it->cbegin();
		while (is != it->cend())
		{
			switch (*is)
			{
			case '.':
			{
				board->addTile(col, row, tileScale, TileType::CORRIDOR);

				break;
			}
			case 'w':
			{
				board->addTile(col, row, tileScale, TileType::WALL);
				break;
			}
			case 'x':
			{
				auto logEntity = buildEntityAt<Log>("./img/log.png", col, row, std::make_shared<SpriteGraphics>());
				addEntity(logEntity);			
				board->addTile(col, row, tileScale, TileType::CORRIDOR);
				break;
			}
			case 'p':
			{
				auto potionEntity = buildEntityAt<Potion>("./img/potion.png", col, row, std::make_shared<SpriteGraphics>());
				addEntity(potionEntity);			

				board->addTile(col, row, tileScale, TileType::CORRIDOR);
				break;
			}
			case '*':
				{
				player = std::make_shared<Player>();

				achievementManager.init(player);
				
				
				player->setGraphicsPointer(std::make_shared<SpriteSheetGraphics>());
				player->initSpriteSheet("./img/DwarfSpriteSheet_data.txt");


				player->positionSprite(row,col,spriteWH,tileScale);

				addEntity(player);

				collisionCallbacks[EntityType::POTION] = std::bind(&Player::handlePotionCollision, player.get(), std::placeholders::_1);
				collisionCallbacks[EntityType::LOG] = std::bind(&Player::handleLogCollision, player.get(), std::placeholders::_1);

				board->addTile(col, row, tileScale, TileType::CORRIDOR);
				break;
				}
			}

			col++; is++;
		}
		row++; it++;
	}
}

void Game::addEntity(std::shared_ptr<Entity> newEntity)
{
	id++;
	newEntity->setID(id);

	if (ecsMethod == EcsMethod::packedArray)
		ecsManager.getPackedArrayManager()->addEntity(newEntity);
	else
		entities.push_back(newEntity);
}

void Game::handleInput()
{
	auto command = inputHandler->handleInput();
	if (command) {
		command->execute(*this);
	}
}


void Game::update(float elapsed)
{
	if (!isPaused())
	{
		ecsManager.updateECS(elapsed, *this, SystemType::Logic);

		std::vector<std::shared_ptr<Entity>>* currentEntities;

		if (ecsMethod == EcsMethod::packedArray)
			currentEntities = &ecsManager.getPackedArrayManager()->getEntities();
		else
			currentEntities = &entities;

		auto it = currentEntities->begin();
		while (it != currentEntities->end())
		{
			if ((*it) != player) {
				auto entType = (*it)->getEntityType();
				if (entType != EntityType::FIRE)
				{
					if (player->intersects(**it))
					{
						if (collisionCallbacks.count(entType) > 0)
						{
							collisionCallbacks[entType](*it);
						}
					}
				}
			}
			++it;
		}

		it = currentEntities->begin();
		while (it != currentEntities->end())
		{
			if ((*it)->isDeleted())
			{
				it = currentEntities->erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	window.update();
}


void Game::render(float elapsed)
{
	//Empty the screen
	window.beginDraw();

	board->draw(&window);

	float clampedElapsed = isPaused() ? 0.0f : elapsed;

	ecsManager.updateECS(clampedElapsed, *this, SystemType::Graphics);
	

	//Draw FPS
	window.drawGUI(*this);

	//Close up for this frame.
	window.endDraw();
}


void Game::setFPS(int FPS)
{
	std::string text("FPS: " + std::to_string(FPS));
	window.getFPSText().setString(text);
}

EntityID Game::getIDCounter()
{
	return id; 
}

std::shared_ptr<Entity> Game::getEntity(unsigned int idx)
{

	if (idx < 0 || idx >= entities.size()) {
		throw std::out_of_range("Index is out of bounds.");
	}
	return entities[idx];
}
