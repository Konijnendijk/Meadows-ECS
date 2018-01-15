
#ifndef MEADOWSECS_COMMONS_H
#define MEADOWSECS_COMMONS_H

#include "Entity.h"

class TestEntity : public Meadows::Entity {

public:
    bool isInitialized;
    float lastTick;
    bool* isDestructed;

public:
    TestEntity(bool* isDestructed) : isInitialized(false), lastTick(-1.0f), isDestructed(isDestructed) {}

    TestEntity () : TestEntity(new bool) {

    }

    ~TestEntity() override {
        *isDestructed = true;
    }

    void init() override {
        isInitialized = true;
    }

protected:
    void tick(float delta) override {
        lastTick = delta;
    }
};

#endif //MEADOWSECS_COMMONS_H
