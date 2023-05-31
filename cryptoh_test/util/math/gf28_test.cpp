//
// Created by Thomas Brooks on 5/30/23.
//

#include "gtest/gtest.h"
#include "util/math/gf28.h"

TEST(GF28AddTest, Example1){
    EXPECT_EQ(gf28::add(0x6b, 0xe1), 0x8a);
}

TEST(GF28MultiplyTest, Example1){
    EXPECT_EQ(gf28::multiply(0x6b, 0xe1), 0xf6);
}