/*
 * Tests the availability of __popcnt. This should be present on MSVC.
 */

#include <intrin.h>

int main() {
    __popcnt(0);
}

