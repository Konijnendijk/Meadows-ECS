
#include "BitSet.h"

#include <cstdlib>
#include <cstring>
#include <new>
#include <limits>
#include <bitset>
#include <iostream>

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
    size_t numWholeValues = n / 32;
    for (std::size_t i = 0; i < numWholeValues; i++) {
        uint32_t num = bits[i];
        count += platformPopCount(num);
    }

    // For the last value, mask the bits after the nth one
    size_t remainingBits = n % 32;
    if (remainingBits > 0) {
        uint32_t num = bits[numWholeValues];
        uint32_t lastMask = ~(std::numeric_limits<uint32_t>::max() << remainingBits);
        num &= lastMask;
        count += platformPopCount(num);
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

uint32_t BitSet::platformPopCount(uint32_t num) const {
#ifdef USE_GCC_POPCOUNT
    return __builtin_popcount(num);
#elif USE_MSVC_POPCOUNT
    // If the popcnt instruction is not supported by the hardware, this will fail
    return __popcnt(num);
#else
   return popCount(num);
#endif
}

BitSet::~BitSet() {
    std::free(bits);
}

std::size_t BitSet::getMemoryRequirement() {
    return (numBits % 32 + numBits) / sizeof(uint32_t);
}
