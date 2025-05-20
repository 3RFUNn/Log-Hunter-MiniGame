#include "../../include/utils/PackedArrayManager.h"

void PackedArrayManager::addEntity(std::shared_ptr<Entity> entity) {
    EntityID id = entity->getID();
    sparseArray[id] = denseArray.size();
    denseArray.push_back(entity);
}

void PackedArrayManager::removeEntity(EntityID id) {
    auto it = sparseArray.find(id);
    if (it == sparseArray.end()) return;

    size_t index = it->second;
    size_t last = denseArray.size() - 1;

    // Swap and pop
    denseArray[index] = denseArray[last];
    sparseArray[denseArray[index]->getID()] = index;

    denseArray.pop_back();
    sparseArray.erase(id);
}

std::shared_ptr<Entity> PackedArrayManager::getEntity(EntityID id) {
    auto it = sparseArray.find(id);
    if (it != sparseArray.end()) {
        return denseArray[it->second];
    }
    return nullptr;
}

std::vector<std::shared_ptr<Entity>>& PackedArrayManager::getEntities() {
    return denseArray;
}
