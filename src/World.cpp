#include "../include/World.h"

World::Ptr World::_current = std::shared_ptr<World>(); // Initializing static member

Entity::Ptr World::CreateEntity(std::string name) {
    return _entitiesMap.emplace(std::move(name), std::make_shared<Entity>()).first->second;
}

Entity::Ptr World::GetEntity(std::string name) {
    auto result = _entitiesMap.find(name);

    if (result != _entitiesMap.end()) {
        return result->second;
    }
    else {
        return std::shared_ptr<Entity>();
    }
}

void World::RemoveEntity(std::string name) {
    _entitiesMap.erase(name);
}

World::Ptr World::Create() {
    return std::make_shared<World>();
}

void World::Clear() {
    _entitiesMap.clear();
}

World::Ptr World::GetCurrent() {
    return _current;
}

void World::SetCurrent(World::Ptr world) {
    _current = world;
}
