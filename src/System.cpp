
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

void System::registerEntity(Entity *object) {
    toAdd.push_back(object);
}

void System::removeEntity(Entity *object) {
    toRemove.push_back(object);
}

bool System::acceptsObject(Entity *object) {
    return true;
}

void System::init() { }

void System::entityAdded(Entity *object) { }

void System::entityRemoved(Entity *object) { }

void System::doTick(float delta) { }
