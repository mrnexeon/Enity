#include "../include/SystemHandler.h"

void SystemHandler::Update() {
    for (auto pair : _systemsMap) {
        pair.second->Update();
    }
}
