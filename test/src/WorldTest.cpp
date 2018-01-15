
#include "catch.hpp"
#include "TestCommons.h"

#include "World.h"

using namespace Meadows;


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
    auto isRemoveEntityDestructed = new bool(false);
    auto removeEntity = world.createEntity<TestEntity>(isRemoveEntityDestructed);
    auto checkEntity = world.createEntity<TestEntity>();
    world.tick(1.0);

    SECTION("Entity has been ticked") {
        REQUIRE(removeEntity->lastTick == 1.0);
        REQUIRE_FALSE(*isRemoveEntityDestructed);
        REQUIRE(checkEntity->lastTick == 1.0);
    }

    SECTION("Entity can be removed") {
        world.removeEntity(removeEntity);
        world.tick(2.0);

        REQUIRE(*isRemoveEntityDestructed);
        REQUIRE(checkEntity->lastTick == 2.0);
    }

    SECTION("Entity can be removed during the same tick") {
        auto isTickRemoveEntityDestructed = new bool(false);
        auto tickRemoveEntity = world.createEntity<TestEntity>(isTickRemoveEntityDestructed);

        REQUIRE(tickRemoveEntity->lastTick == -1.0);
        REQUIRE_FALSE(*isTickRemoveEntityDestructed);
        REQUIRE(checkEntity->lastTick == 1.0);

        world.removeEntity(tickRemoveEntity);
        world.tick(2.0);

        REQUIRE(*isTickRemoveEntityDestructed);
        REQUIRE(checkEntity->lastTick == 2.0);
    }
}