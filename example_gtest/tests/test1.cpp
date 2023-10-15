#include <gtest/gtest.h>
#include "lib.h"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);

  EXPECT_EQ(lib::sum(2, 3), 1);

  EXPECT_EQ(lib::sum(2, 3), 5);
  EXPECT_EQ(lib::sum(2, 3), 5);
  EXPECT_EQ(lib::sum(2, 3), 2);

}