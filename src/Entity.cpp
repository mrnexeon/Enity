#include "../include/Entity.h"

Entity::Ptr Entity::Create() {
    return std::make_shared<Entity>();
}

void Entity::Attach(Entity::Ptr child) {
    _children.push_back(child);
}

void Entity::Detach(Entity::Ptr child) {
    _children.remove(child);
}

std::list<Entity::Ptr> Entity::GetChildren() {
    return _children;
}

