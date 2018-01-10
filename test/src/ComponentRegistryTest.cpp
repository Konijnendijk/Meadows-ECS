
#include "catch.hpp"

#include "ComponentRegistry.h"

using namespace Meadows;

class TestComponent1 : public Component {};
class TestComponent2 : public Component {};
class TestComponent3 : public Component {};
class TestComponent4 : public Component {};


TEST_CASE("Components are indexed correctly", "[ComponentRegistry]") {
    ComponentRegistry* registry = ComponentRegistry::getInstance();

    std::size_t index1 = registry->getComponentIndex<TestComponent1>();
    std::size_t index2 = registry->getComponentIndex<TestComponent2>();
    std::size_t index3 =registry->getComponentIndex<TestComponent3>();

    REQUIRE_FALSE(index1 == index2);
    REQUIRE_FALSE(index1 == index3);
    REQUIRE_FALSE(index2 == index3);


    std::size_t index4 = registry->getComponentIndex<TestComponent4>();
    std::size_t newIndex1 = registry->getComponentIndex<TestComponent1>();
    std::size_t newIndex2 = registry->getComponentIndex<TestComponent2>();
    std::size_t newIndex3 =registry->getComponentIndex<TestComponent3>();

    REQUIRE_FALSE(index1 == index2);
    REQUIRE_FALSE(index1 == index3);
    REQUIRE_FALSE(index1 == index4);
    REQUIRE_FALSE(index2 == index3);
    REQUIRE_FALSE(index2 == index4);
    REQUIRE_FALSE(index3 == index4);

    REQUIRE(index1 == newIndex1);
    REQUIRE(index2 == newIndex2);
    REQUIRE(index3 == newIndex3);
}