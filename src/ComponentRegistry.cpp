
#include "ComponentRegistry.h"

using namespace Meadows;

std::size_t ComponentRegistry::numRegisteredComponents = 0;

ComponentRegistry* ComponentRegistry::instance = nullptr;

std::size_t ComponentRegistry::getNumRegisteredComponents() {
    return numRegisteredComponents;
}

ComponentRegistry *ComponentRegistry::getInstance() {
    if (instance == nullptr) {
        instance = new ComponentRegistry();
    }
    return instance;
}
