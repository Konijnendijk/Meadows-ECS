
#include "ComponentSet.h"

using namespace Meadows;

ComponentSet::ComponentSet() : componentBitSet(ComponentRegistry::getNumRegisteredComponents()) {

}

ComponentSet::~ComponentSet() {
    for (Component* component : components) {
        delete(component);
    }
}
