//
// Created by Thomas Brooks on 5/30/23.
//

#ifndef CRYPTOH_PROJECT_GF28_H
#define CRYPTOH_PROJECT_GF28_H

#include <cstdint>

class gf28 {
public:
    static uint8_t add(uint8_t a, uint8_t b);
    static uint8_t multiply(uint8_t a, uint8_t b);
};

#endif //CRYPTOH_PROJECT_GF28_H
