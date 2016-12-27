#pragma once

#include <memory> // std::shared_ptr
#include <unordered_map> // std::unordered_map
#include <list> // std::list
#include "Entity.h"

class World {
public:
    typedef std::shared_ptr<World> Ptr;
    static Ptr Create(); // Create Smart-pointer

    static World::Ptr GetCurrent();
    static void SetCurrent(World::Ptr world);

    Entity::Ptr CreateEntity(std::string name); // Add entity to the world
    void RemoveEntity(std::string name); // Remove entity from the world
    Entity::Ptr GetEntity(std::string name); // Get pointer to entity
    template <typename ... TsComponents> std::list<Entity::Ptr> GetGroup(); // Get entity group with any of component in list
    void Clear(); // Remove all entities from the world

private:
    static World::Ptr _current;
    std::unordered_map<std::string, Entity::Ptr> _entitiesMap;
};

template<typename ... TsComponents>
std::list<Entity::Ptr> World::GetGroup() {
    std::list<Entity::Ptr> group;

    for (auto pair : _entitiesMap) {
        if (pair.second->Match<TsComponents...>()) group.push_back(pair.second);
    }

    return group;
}