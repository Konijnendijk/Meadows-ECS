
#include "System.h"

using namespace Meadows;

void System::tick(float delta) {
    for (Entity* add : toAdd) {
        entities.push_back(add);
        entityAdded(add);
    }
    toAdd.clear();

    // Remove objects set to be removed
    for (Entity* remove : toRemove) {
        entities.erase(std::remove_if(entities.begin(), entities.end(),
                                     [&](Entity* obj) {
                                         return obj == remove;
                                     }), entities.end());
        entityRemoved(remove);
    }
    toRemove.clear();

    doTick(delta);
}

void System::registerEntity(Meadows::Entity *object) {
    toAdd.push_back(object);
}

void System::removeEntity(Meadows::Entity *object) {
    toRemove.push_back(object);
}

bool System::acceptsObject(Meadows::Entity *object) {
    return true;
}
