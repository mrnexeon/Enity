#pragma once

#include "System.h" // System
#include "Utility.h" // GetIndex()
#include <unordered_map> // std::unordered_map
#include <iostream> // std::cerr

class SystemHandler {
public:
    template <typename TSystem, typename ... Args> bool Add(Args&& ... args); // Add system
    template <typename TSystem> System::Ptr Get(); // Get pointer to system
    template <typename TSystem> void Remove(); // Remove system

    void Update(); // Update systems

private:
    std::unordered_map<std::type_index, System::Ptr> _systemsMap;
};

void SystemHandler::Update() {
    for (auto pair : _systemsMap) {
        pair.second->Update();
    }
}

template<typename TSystem, typename ... Args>
bool SystemHandler::Add(Args &&... args) {
    static_assert(std::is_base_of<System, TSystem>::value, "Your Own System must inherit from System class");

    std::type_index index = GetIndex<TSystem>();

    auto result = _systemsMap.find(index);

    if (result != _systemsMap.end()) {
        std::cerr << "This system already exists" << std::endl;
        return false;
    }
    else {
        _systemsMap.emplace(index, std::make_shared<TSystem>(args...));
        return true;
    }
}

template<typename TSystem>
System::Ptr SystemHandler::Get() {
    static_assert(std::is_base_of<System, TSystem>::value, "Your Own System must inherit from System class");

    auto result = _systemsMap.find(GetIndex<TSystem>());

    if (result != _systemsMap.end()) {
        return std::dynamic_pointer_cast<TSystem>(result->second);
    }
    else {
        return std::shared_ptr<TSystem>();
    }
}

template<typename TSystem>
void SystemHandler::Remove() {
    static_assert(std::is_base_of<System, TSystem>::value, "Your Own System must inherit from System class");

    _systemsMap.erase(GetIndex<TSystem>());
}

