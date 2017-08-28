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

        BitSet& operator=(BitSet& other);

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

    };

}

#endif //MEADOWSECS_BITSETUTIL_H
