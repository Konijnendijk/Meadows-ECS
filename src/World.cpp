
#include "World.h"

using namespace Meadows;

SystemAlreadyRegisteredException::SystemAlreadyRegisteredException(const std::string what) : runtime_error(what) {}

World::World() : nextGameObjectId(0) {}

World::~World() {
    for (GameObject* object : objects) {
        delete(object);
    }
    for (GameObject* object : objectsToAdd) {
        delete(object);
    }
    for (GameObject* object : objectsToRemove) {
        delete(object);
    }
    for (auto system : systems) {
        delete(system.second);
    }
}

void World::tick(float delta) {
    // Add new objects and initialize them
    for (GameObject* add : objectsToAdd) {
        objects.push_back(add);
        add->init();

        for (auto s : systems) {
            if (s.second->acceptsObject(add)) {
                s.second->registerObject(add);
            }
        }
    }
    objectsToAdd.clear();

    for (GameObject* remove : objectsToRemove) {
        for (auto s : systems) {
            s.second->removeObject(remove);
        }

        objects.erase(std::remove_if(objects.begin(), objects.end(), [remove](GameObject* object){return *object == *remove;}));

        delete(remove);
    }
    objectsToRemove.clear();

    for (auto& system : systems) {
        system.second->tick(delta);
    }

    for (GameObject* object : objects) {
        if (object->isEnabled())
            object->tick(delta);
    }
}

void World::registerSystem(std::string name, System *system) {
    if (systems.find(name) != systems.end()) {
        throw SystemAlreadyRegisteredException("System with name [" + name + "] was already registered");
    }
    systems.insert(std::make_pair(name, system));
}

void World::removeObject(GameObject *object) {
    objectsToRemove.push_back(object);
}

void World::registerObject(GameObject *object) {
    object->setId(nextGameObjectId++);
    objectsToAdd.push_back(object);
}
