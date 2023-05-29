//
// Created by Thomas Brooks on 5/28/23.
//
#include "gtest/gtest.h"
#include "hash/sha/sha256.h"

class SHA256Test : public ::testing::Test {
protected:
    sha256* sha;

    void SetUp() override {
        sha = new sha256();
    }

    void TearDown() override {
        delete sha;
    }
};

TEST_F(SHA256Test, EmptyString){
    sha->consume("");
    EXPECT_EQ(sha->digest(), "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
}

TEST_F(SHA256Test, ShortString){
    sha->consume("Hello, world!");
    EXPECT_EQ(sha->digest(), "315f5bdb76d078c43b8ac0064e4a0164612b1fce77c869345bfc94c75894edd3");
}

// TODO: Look into why this is failing
TEST_F(SHA256Test, LongString){
    sha->consume(
            "Quamquam te, Marce fili, annum iam audientem Cratippum idque Athenis abundare oportet "
            "praeceptis institutisque philosophiae propter summam et doctoris auctoritatem et urbis, quorum "
            "alter te scientia augere potest, altera exemplis, tamen, ut ipse ad meam utilitatem semper cum "
            "Graecis Latina coniunxi neque id in philosophia solum, sed etiam in dicendi exercitatione feci, "
            "idem tibi censeo faciendum, ut par sis in utriusque orationis facultate. Quam quidem ad rem nos, "
            "ut videmur, magnum attulimus adiumentum hominibus nostris, ut non modo Graecarum litterarum rudes, "
            "sed etiam docti aliquantum se arbitrentur adeptos et ad dicendum et ad iudicandum."
    );
    EXPECT_EQ(sha->digest(), "60bb112e589a93278160b2ff2ce1e28f11b4c188257e92c30d4a54aa3e9e2b30");
}