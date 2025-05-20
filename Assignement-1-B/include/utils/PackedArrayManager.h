#pragma once
#include "../entities/Entity.h"
#include <unordered_map>
#include <vector>

class PackedArrayManager {
public:
    void addEntity(std::shared_ptr<Entity> entity);
    void removeEntity(EntityID id);
    std::shared_ptr<Entity> getEntity(EntityID id);
    std::vector<std::shared_ptr<Entity>>& getEntities();

private:
    std::vector<std::shared_ptr<Entity>> denseArray;
    std::unordered_map<EntityID, size_t> sparseArray;
};
