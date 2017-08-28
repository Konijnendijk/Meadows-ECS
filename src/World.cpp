
#include "World.h"

using namespace Meadows;

World::World() : nextGameObjectId(0) {}

World::~World() {
    for (Entity* object : entities) {
        delete(object);
    }
    for (Entity* object : entitiesToAdd) {
        delete(object);
    }
    for (Entity* object : entitiesToRemove) {
        delete(object);
    }
    for (System* s : systems) {
        delete(s);
    }
}

void World::tick(float delta) {
    // Add new objects and initialize them
    for (Entity* add : entitiesToAdd) {
        entities.push_back(add);
        add->init();

        for (auto s : systems) {
            if (s->acceptsObject(add)) {
                s->registerEntity(add);
            }
        }
    }
    entitiesToAdd.clear();

    for (Entity* remove : entitiesToRemove) {
        for (auto s : systems) {
            s->removeEntity(remove);
        }

        entities.erase(std::remove_if(entities.begin(), entities.end(), [remove](Entity* object){return *object == *remove;}));

        delete(remove);
    }
    entitiesToRemove.clear();

    for (System* s : systems) {
        s->tick(delta);
    }

    for (Entity* object : entities) {
        if (object->isEnabled())
            object->tick(delta);
    }
}

void World::registerSystem(System *system) {
    systems.push_back(system);
}

void World::removeEntity(Entity *object) {
    entitiesToRemove.push_back(object);
}

void World::registerEntity(Entity *object) {
    object->setId(nextGameObjectId++);
    entitiesToAdd.push_back(object);
}
