
#include "catch.hpp"

#include "World.h"

using namespace Meadows;

class TestEntity : public Entity {

public:
    bool isInitialized;
    float lastTick;

public:
    TestEntity() : isInitialized(false), lastTick(-1) {}

    void init() override {
        isInitialized = true;
    }

protected:
    void tick(float delta) override {
        lastTick = delta;
    }
};

TEST_CASE("Creating entities", "[World][integration]") {

    World world;
    auto entity = world.createEntity<TestEntity>();

    SECTION("Entity is not initialised") {
        REQUIRE_FALSE(entity->isInitialized);
    }

    SECTION("Entity is initialised after first tick") {
        world.tick(1.0);

        REQUIRE(entity->isInitialized);
        REQUIRE(entity->lastTick == 1.0);
    }
}


TEST_CASE("Removing entities", "[World][integration]") {
    World world;
    auto dummyEntity1 = world.createEntity<Entity>();
    auto dummyEntity2 = world.createEntity<Entity>();
    auto removeEntity = world.createEntity<TestEntity>();
    auto checkEntity = world.createEntity<TestEntity>();
    world.tick(1.0);

    SECTION("Entity has been ticked") {
        REQUIRE(removeEntity->lastTick == 1.0);
        REQUIRE(checkEntity->lastTick == 1.0);
    }

    SECTION("Entity can be removed") {
        world.removeEntity(removeEntity);
        world.tick(2.0);

        REQUIRE(removeEntity->lastTick == 1.0);
        REQUIRE(checkEntity->lastTick == 2.0);
    }

    SECTION("Entity can be removed during the same tick") {
        auto tickRemoveEntity = world.createEntity<TestEntity>();

        REQUIRE(tickRemoveEntity->lastTick == -1.0);
        REQUIRE(checkEntity->lastTick == 1.0);

        world.removeEntity(tickRemoveEntity);
        world.tick(2.0);

        REQUIRE(tickRemoveEntity->lastTick == -1.0);
        REQUIRE(checkEntity->lastTick == 2.0);
    }
}