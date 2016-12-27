#pragma once

#include <typeindex> // std::type_index

template <typename T> std::type_index GetIndex() {
    return std::type_index{typeid(T)};
}