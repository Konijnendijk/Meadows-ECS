
#include "catch.hpp"
#include "TestCommons.h"

#include "System.h"

using namespace Meadows;

class TestSystem : public System {

public:
    int entitiesAdded;
    int entitiesRemoved;
    int entitiesDuringTick;

public:
    TestSystem() : entitiesAdded(0), entitiesRemoved(0), entitiesDuringTick(-1) {}

    ~TestSystem() override {};

protected:
    void doTick(float delta) override {
        entitiesDuringTick = static_cast<int>(entities.size());
    }

    void entityAdded(Entity *object) override {
        entitiesAdded++;
        REQUIRE(entities.size() == entitiesAdded - entitiesRemoved);
    }

    void entityRemoved(Entity *object) override {
        entitiesRemoved++;
        REQUIRE(entities.size() == entitiesAdded - entitiesRemoved);
    }
};

TEST_CASE("System Entity management", "[System]") {
    TestSystem system;
    TestEntity entity1;
    TestEntity entity2;

    system.registerEntity(&entity1);
    system.registerEntity(&entity2);

    SECTION("Entities are registered at the next tick") {
        REQUIRE(system.entitiesAdded == 0);
        REQUIRE(system.entitiesDuringTick == -1);
        REQUIRE(system.entitiesRemoved == 0);

        system.tick(1.0f);

        REQUIRE(system.entitiesAdded == 2);
        REQUIRE(system.entitiesDuringTick == 2);
        REQUIRE(system.entitiesRemoved == 0);
    }

    SECTION("Entities are removed at the next tick") {
        system.tick(1.0);

        system.removeEntity(&entity1);

        REQUIRE(system.entitiesAdded == 2);
        REQUIRE(system.entitiesDuringTick == 2);
        REQUIRE(system.entitiesRemoved == 0);

        system.tick(1.0f);

        REQUIRE(system.entitiesAdded == 2);
        REQUIRE(system.entitiesDuringTick == 1);
        REQUIRE(system.entitiesRemoved == 1);
    }

    SECTION("Entities can be added and removed during the same tick") {
        system.removeEntity(&entity1);

        REQUIRE(system.entitiesAdded == 0);
        REQUIRE(system.entitiesRemoved == 0);
        REQUIRE(system.entitiesDuringTick == -1);

        system.tick(1.0);

        REQUIRE(system.entitiesAdded == 2);
        REQUIRE(system.entitiesRemoved == 1);
        REQUIRE(system.entitiesDuringTick == 1);
    }
}

