#ifndef MEADOWSECS_BITSETUTIL_H
#define MEADOWSECS_BITSETUTIL_H

#include <cstddef>
#include <cstdint>

namespace Meadows {

    class BitSet {

        std::size_t numBits;
        uint32_t* bits;

    public:

        /**
         * Create an empty BitSet.
         */
        BitSet();

        /**
         * Create a BitSet with at least numBits bits.
         *
         * @param numBits The minimum number of possible bits
         */
        BitSet (std::size_t numBits);

        BitSet& operator=(const BitSet& other);

        /**
         * Get the bit at index n
         * @param n
         * @return 0 if the bit is not set, not 0 if set
         */
        uint32_t operator[](std::size_t n);

        /**
         * Set the bit at index n.
         *
         * @param n Bit index
         */
        void set (std::size_t n);

        /**
         * Count the number of set bits before n.
         *
         * @param n Bit index
         * @return The number of set bits before n
         */
        std::size_t numSetBitsBefore(std::size_t n);

        ~BitSet();

    private:
        std::size_t getMemoryRequirement();

        /**
         * Count the number of set bits in a 32 bit int.
         *
         * @param num The uint32_t to count the set bits of
         * @return The number of bits set
         */
        uint32_t popCount(uint32_t num) const;

        /**
         * Do a popcount on a 32 bit value, using intrinsics if available
         *
         * @param num The uint32_t to count the set bits of
         * @return The number of bits set
         */
        uint32_t platformPopCount(uint32_t num) const;
    };

}

#endif //MEADOWSECS_BITSETUTIL_H
