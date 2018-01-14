
#include "BitSet.h"

#include <cstdlib>
#include <cstring>
#include <new>

#ifdef USE_MSVC_POPCOUNT
#include <intrin.h>
#endif

using namespace Meadows;

BitSet::BitSet() : numBits(0), bits{} {}

BitSet::BitSet(std::size_t numBits) : numBits(numBits) {
    size_t memoryRequirement = getMemoryRequirement();
    bits = (uint32_t*) std::malloc(memoryRequirement);
    if (bits == nullptr) {
        throw std::bad_alloc();
    }
    std::memset(bits, 0, memoryRequirement);
}

BitSet &BitSet::operator=(const BitSet& other) {
    numBits = other.numBits;
    size_t size = getMemoryRequirement();
    bits = (uint32_t*) std::realloc(bits, size);
    if (bits == nullptr) {
        throw std::bad_alloc();
    }
    std::memcpy(bits, other.bits, size);
    return *this;
}

uint32_t BitSet::operator[](std::size_t n) {
    return bits[n / 32] & (1 << (n % 32));
}

void BitSet::set(std::size_t n) {
    bits[n / 32] |= (1 << (n % 32));
}

std::size_t BitSet::numSetBitsBefore(std::size_t n) {
    std::size_t count = 0;
    // Count the bits in the uint32_t values before the (n/32)th value
    for (std::size_t i = 0; i<n/32; i++) {
        uint32_t num = bits[i];
#ifdef USE_GCC_POPCOUNT
        count += __builtin_popcount(num);
#elif USE_MSVC_POPCOUNT
        // If the popcnt instruction is not supported by the hardware, this will fail
        count += __popcnt(num);
#else
       count += popCount(num);
#endif
    }

    // Count the bits of the (n/32)th value, up to the nth bit
    for (std::size_t j = 0; j < (n % 32); j++) {
        if (bits[n / 32] & (1 << j))
            count++;
    }

    return count;
}

uint32_t BitSet::popCount(uint32_t num) const {
    // SWAR algorithm from https://www.playingwithpointers.com/swar.html
    num = num - ((num >> 1) & 0x55555555);
    num = (num & 0x33333333) + ((num >> 2) & 0x33333333);
    num = (((num + (num >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
    return num;
}

BitSet::~BitSet() {
    std::free(bits);
}

std::size_t BitSet::getMemoryRequirement() {
    return (numBits % 32 + numBits) / sizeof(uint32_t);
}
