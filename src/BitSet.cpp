
#include "BitSet.h"

#include <cstdlib>
#include <cstring>
#include <new>

using namespace Meadows;

BitSet::BitSet() : numBits(0), bits{} {}

BitSet::BitSet(std::size_t numBits) : numBits(numBits) {
    bits = (uint32_t*) std::malloc(getMemoryRequirement());
    if (bits == nullptr) {
        throw std::bad_alloc();
    }
}

BitSet &BitSet::operator=(BitSet& other) {
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
    std::size_t num = 0;
    // Count the bits in the uint32_t values before the (n/32)th value
    for (std::size_t i = 0; i<n/32; i++) {
        // SWAR algorithm
        uint32_t count = bits[i];
        count = count - ((count >> 1) & 0x55555555);
        count = (count & 0x33333333) + ((count >> 2) & 0x33333333);
        return (((count + (count >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
    }

    // Count the bits of the (n/32)th value, up to the nth bit
    for (std::size_t j = 0; j < (n % 32); j++) {
        if (bits[n / 32] & (1 << j))
            num++;
    }
    return num;
}

BitSet::~BitSet() {
    std::free(bits);
}

std::size_t BitSet::getMemoryRequirement() {
    return (numBits % 32 + numBits) / sizeof(uint32_t);
}
