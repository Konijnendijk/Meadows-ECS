
#include "World.h"

using namespace Meadows;

World::World() : nextGameObjectId(0) {}

World::~World() {
    for (Entity* object : objects) {
        delete(object);
    }
    for (Entity* object : objectsToAdd) {
        delete(object);
    }
    for (Entity* object : objectsToRemove) {
        delete(object);
    }
    for (System* s : systems) {
        delete(s);
    }
}

void World::tick(float delta) {
    // Add new objects and initialize them
    for (Entity* add : objectsToAdd) {
        objects.push_back(add);
        add->init();

        for (auto s : systems) {
            if (s->acceptsObject(add)) {
                s->registerObject(add);
            }
        }
    }
    objectsToAdd.clear();

    for (Entity* remove : objectsToRemove) {
        for (auto s : systems) {
            s->removeObject(remove);
        }

        objects.erase(std::remove_if(objects.begin(), objects.end(), [remove](Entity* object){return *object == *remove;}));

        delete(remove);
    }
    objectsToRemove.clear();

    for (System* s : systems) {
        s->tick(delta);
    }

    for (Entity* object : objects) {
        if (object->isEnabled())
            object->tick(delta);
    }
}

void World::registerSystem(System *system) {
    systems.push_back(system);
}



void World::removeObject(Entity *object) {
    objectsToRemove.push_back(object);
}

void World::registerObject(Entity *object) {
    object->setId(nextGameObjectId++);
    objectsToAdd.push_back(object);
}
