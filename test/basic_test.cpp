//
// Created by trebor on 05.01.2022.
//

#include <gtest/gtest.h>

// Demonstrate some basic assertions.
TEST(UnitTest, BasicAssertions) {
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);

    ASSERT_EQ(1, 1.0) << "int and double are the same";
}