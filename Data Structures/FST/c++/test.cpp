#include <gtest/gtest.h>
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<vector>

#include "fst.h"

#define GTEST_COUT std::cerr << "[          ] [ INFO ]"

TEST(MyTest, Sum)
{
    auto SM = StateMachine();
    SM.add("mox", 10);
    SM.add("moxr", 5);
    SM.add("yox", 2);
    SM.add("yoxr", 8);
    SM.add("zox", 6);
    SM.add("uox", 1);

    // should return correct value
    EXPECT_EQ(SM.get("mox"), 10);
    EXPECT_EQ(SM.get("moxr"), 5);
    EXPECT_EQ(SM.get("yox"), 2);
    EXPECT_EQ(SM.get("yoxr"), 8);
    EXPECT_EQ(SM.get("zox"), 6);
    EXPECT_EQ(SM.get("uox"), 1);

    // key not exists
    // should return INT_MIN
    GTEST_COUT << SM.get("ox") << std::endl;
    EXPECT_EQ(SM.get("ox"), INT_MIN);
    EXPECT_EQ(SM.get("zo"), INT_MIN);
    EXPECT_EQ(SM.get(""), INT_MIN);

}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}