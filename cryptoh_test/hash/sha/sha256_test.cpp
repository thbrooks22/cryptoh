//
// Created by Thomas Brooks on 5/28/23.
//
#include "gtest/gtest.h"
#include "../../../cryptoh_lib/hash/sha/sha256.h"

TEST(SHA256TestSuite, Example){
    sha256* hash = new sha256("");
    std::string x = hash->digest();
}