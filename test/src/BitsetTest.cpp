
#include "catch.hpp"

#include "BitSet.h"

#include <random>
#include <vector>
#include <csignal>
#include <functional>
#include <algorithm>

using namespace Meadows;

void requireBitSetEmpty(BitSet &bitset, std::size_t size) {
    for (std::size_t i = 0; i <= size; i++) {
        REQUIRE(bitset[i] == 0);
        REQUIRE(bitset.numSetBitsBefore(i) == 0);
    }
}

TEST_CASE("bits can be set on a small, 8 bit BitSet", "[BitSet]") {
    BitSet bitset(8);

    // BitSet is still empty when nothing is set
    requireBitSetEmpty(bitset, 8);

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

TEST_CASE("bits can be set on a larger, 16 bit BitSet", "[BitSet]") {
    BitSet bitset(16);

    requireBitSetEmpty(bitset, 16);

    SECTION ("bits can be set and retrieved and bits are counted correctly") {
        // The indices to set
        std::size_t indices[] = {8, 15, 6, 9, 14, 2, 13, 4, 7};
        for (std::size_t i : indices) {
            bitset.set(i);
            REQUIRE(bitset[i]);
        }

        // The expected count before each index
        std::size_t countBefore[] = {0, 0, 0, 1, 1, 2, 2, 3, 4, 5, 6, 6, 6, 6, 7, 8, 9};
        for (std::size_t i=0; i <= 16; i++) {
            REQUIRE(bitset.numSetBitsBefore(i) == countBefore[i]);
        }
    }
}

TEST_CASE("BitSet fuzzing", "[BitSet]") {

    // Keep this test deterministic by leaving the seed at the default value
    std::default_random_engine generator;
    std::uniform_int_distribution<std::size_t> bitsetSizeRandom(8, 1024);
    std::uniform_int_distribution<std::size_t> bitIndexRandom(0, 1023);

    // Create randomly sized bitsets and set random bits
    for (int i=0; i<1000; i++) {
        std::size_t size = bitsetSizeRandom(generator);
        BitSet bitset(size);

        requireBitSetEmpty(bitset, size);
        
        std::uniform_int_distribution<std::size_t> numSetRandom(1, size);

        // Set random indices and test that they are set
        std::size_t numToSet = numSetRandom(generator);
        std::vector<std::size_t> setIndices;
        setIndices.reserve(numToSet);
        for (int j=0; j < numToSet; j++) {
            std::size_t bitIndex = bitIndexRandom(generator) % size;
            bitset.set(bitIndex);
            setIndices.push_back(bitIndex);

            REQUIRE(bitset[bitIndex]);
        }

        // Test that all indices are still set
        for (std::size_t index: setIndices) {
            REQUIRE(bitset[index]);
        }

        // Test that the count of bits before an index is correct
        std::sort(setIndices.begin(), setIndices.end(), std::greater<>());
        std::size_t count = 0;

        for (int j=0; j<=size; j++) {
            REQUIRE(bitset.numSetBitsBefore(j) == count);

            if (!setIndices.empty() && setIndices.back() == j) {
                count++;
                while (!setIndices.empty() && setIndices.back() == j) {
                    setIndices.pop_back();
                }
            }
        }
    }

}
