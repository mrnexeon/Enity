#pragma once

#include <memory> // std::shared_ptr

class Component {
public:
    typedef std::shared_ptr<Component> Ptr;

    virtual ~Component() = default;
};