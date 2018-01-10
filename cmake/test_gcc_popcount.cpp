/*
 * Tests the availability of __builtin_popcount. This should be present on GCC, Clang and ICC.
 */

int main() {
    __builtin_popcount(0);
}

