#pragma once

#include "Component.h"
#include "Utility.h" // GetIndex()
#include <memory> // std::shared_ptr
#include <unordered_map> // std::unordered_map
#include <type_traits> // std::enable_if
#include <iostream> // std::cerr
#include <list> // std::list

class Entity {
public:
    typedef std::shared_ptr<Entity> Ptr;
    static Ptr Create(); // Create Smart-pointer

    template <typename TComponent, typename ... Args> bool Add(Args&& ... args); // Add component
    template <typename TComponent, typename ... Args> void Replace(Args&& ... args); // Replace the exist component by a new
    template <typename TComponent> std::shared_ptr<TComponent> Get(); // Get pointer to component
    template <typename ... TsComponents> bool Match(); // Return true only if any of component is exist
    template <typename TComponent> void Remove(); // Remove component

    void Attach(Entity::Ptr child); // Attach child to this entity
    void Detach(Entity::Ptr child); // Detach child to this entity
    std::list<Entity::Ptr> GetChildren(); // Get children of entity

private:
    template <typename T, typename ... Ts> bool Match_impl();
    template <typename ... Ts> typename std::enable_if<sizeof...(Ts) == 0, bool>::type Match_impl();

    std::unordered_map<std::type_index, Component::Ptr> _componentsMap;

    std::list<Entity::Ptr> _children;
};

template<typename TComponent, typename ... Args>
bool Entity::Add(Args &&... args) {
    static_assert(std::is_base_of<Component, TComponent>::value, "Your Own Component must inherit from Component class");

    std::type_index index = GetIndex<TComponent>();

    auto result = _componentsMap.find(index);

    if (result != _componentsMap.end()) {
        std::cerr << "This component already exists" << std::endl;
        return false;
    }
    else {
        _componentsMap.emplace(index, std::make_shared<TComponent>(args...));
        return true;
    }
}

template<typename TComponent, typename ... Args>
void Entity::Replace(Args &&... args) {
    static_assert(std::is_base_of<Component, TComponent>::value, "Your Own Component must inherit from Component class");

    std::type_index index = GetIndex<TComponent>();

    auto result = _componentsMap.find(index);

    if (result != _componentsMap.end()) {
        _componentsMap.erase(result);
        _componentsMap.emplace(index, std::make_shared<TComponent>(args...));
    }
}

template<typename TComponent>
void Entity::Remove() {
    static_assert(std::is_base_of<Component, TComponent>::value, "Your Own Component must inherit from Component class");

    _componentsMap.erase(GetIndex<TComponent>());
}

template<typename TComponent>
std::shared_ptr<TComponent> Entity::Get() {
    static_assert(std::is_base_of<Component, TComponent>::value, "Your Own Component must inherit from Component class");

    auto result = _componentsMap.find(GetIndex<TComponent>());

    if (result != _componentsMap.end()) {
        return std::dynamic_pointer_cast<TComponent>(result->second);
    }
    else {
        return std::shared_ptr<TComponent>();
    }
}

template<typename ... TsComponents>
bool Entity::Match() {
    return Match_impl<TsComponents...>();
}

template<typename T, typename ... Ts>
bool Entity::Match_impl() {
    static_assert(std::is_base_of<Component, T>::value, "Your Own Component must inherit from Component class");

    auto result = _componentsMap.find(GetIndex<T>());

    return result != _componentsMap.end() || Match_impl<Ts...>();
}

template <typename ... Ts>
typename std::enable_if<sizeof...(Ts) == 0, bool>::type Entity::Match_impl() {
    return false;
};