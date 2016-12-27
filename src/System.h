#pragma once

#include <memory> // std::shared_ptr
#include "World.h"

class System {
public:
    typedef std::shared_ptr<System> Ptr;

    virtual void Update() = 0;

    virtual ~System() = default;
};