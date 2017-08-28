
#include "catch.hpp"

#include "BitSet.h"

using namespace Meadows;

TEST_CASE("bits can be set on a small, 8 bit BitSet", "[BitSet]") {
    BitSet bitset(8);

    SECTION ("BitSet is still empty when nothing is set") {
        for (std::size_t i = 0; i <= 8; i++) {
            REQUIRE(bitset[i] == 0);
            REQUIRE(bitset.numSetBitsBefore(i) == 0);
        }
    }

    SECTION ("bits can be set and retrieved and bits are counted correctly") {
        // The indices to set
        std::size_t indices[] = {4, 0, 5, 1, 7};
        for (std::size_t i : indices) {
            bitset.set(i);
            REQUIRE(bitset[i]);
        }

        // The expected count before each index
        std::size_t countBefore[] = {0, 1, 2, 2, 2, 3, 4, 4, 5};
        for (std::size_t i=0; i <= 8; i++) {
            REQUIRE(bitset.numSetBitsBefore(i) == countBefore[i]);
        }
    }
}
