//
// Created by Thomas Brooks on 5/30/23.
//

#include "gf28.h"

uint8_t gf28::add(uint8_t a, uint8_t b) {
    return a ^ b;
}

uint8_t gf28::multiply(uint8_t a, uint8_t b) {
    uint8_t p = 0;

    for (uint8_t i = 0; i < 8; i++) {
        if (b % 2 != 0) {
            p ^= a;
        }

        b >>= 1;
        bool carry = a >= 0x80;
        a <<= 1;

        if (carry) {
            a ^= 0x1b;
        }
    }

    return p;
}