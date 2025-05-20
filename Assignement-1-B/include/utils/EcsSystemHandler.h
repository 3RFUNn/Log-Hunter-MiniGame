#pragma once
#include "ArchetypeManager.h"
#include "../../include/entities/Entity.h"
#include "PackedArrayManager.h"

class Game;

class EcsSystemHandler
{
public:
	EcsSystemHandler();
	~EcsSystemHandler();

	void populateECS(Game& game);
	void updateECS(float elapsedTime, Game& game, SystemType _systemType);

	std::vector<std::shared_ptr<System>> getLogicSystems() { return logicSystems; }
	std::shared_ptr<ArchetypeManager> getArchetypeManager() { return archetypeManager; }
	std::shared_ptr<PackedArrayManager> getPackedArrayManager() { return packedArrayManager; }


private:
	void setBigArraySystems(SystemType _systemType);
	void updateBigArray(float elapsedTime, Game& game, std::vector<std::shared_ptr<Entity>> _entities);
	void updateArchetypes(float elapsedTime, Game& game, std::vector<std::shared_ptr<Entity>> _entities, SystemType _systemType);

	std::shared_ptr<ArchetypeManager> archetypeManager = nullptr;
	std::shared_ptr<PackedArrayManager> packedArrayManager;
	std::vector<std::shared_ptr<System>> logicSystems;
	std::vector<std::shared_ptr<System>> graphicsSystems;
	std::vector<std::shared_ptr<System>> systems;
	std::vector<std::shared_ptr<System>>::iterator systemIt;
	std::vector<std::shared_ptr<Entity>>::iterator entityIt;
};