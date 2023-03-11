
#include <gtest/gtest.h>

#include <stack>

#include "utils.hpp"

TEST(DaysBeforWarmup, Empty) {
  ASSERT_EQ(CalculateDaysBeforWarmup({}), std::vector<int>{});
}

TEST(DaysBeforWarmup, Simple) {
  ASSERT_EQ(CalculateDaysBeforWarmup({1.0, 2.0, 3.0}),
            (std::vector<int>{1, 1, 0}));
  ASSERT_EQ(CalculateDaysBeforWarmup({1.0, 2.0, 1.0, 3.0}),
            (std::vector<int>{1, 2, 1, 0}));
  ASSERT_EQ(CalculateDaysBeforWarmup({5.0, 4.0, 3.0, 2.0}),
            (std::vector<int>{0, 0, 0, 0}));
}