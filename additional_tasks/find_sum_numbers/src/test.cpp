
#include <gtest/gtest.h>

#include <stack>

#include "utils.hpp"

TEST(GetNumbersOfSum, Simple) {
  ASSERT_EQ(GetNumbersOfSum(std::vector<int>{-10, -2, 0, 3, 6, 7, 11, 14}, 3),
            (std::pair<int, int>(0, 3)));
  ASSERT_ANY_THROW(GetNumbersOfSum(std::vector<int>{}, 3));
  ASSERT_EQ(GetNumbersOfSum(std::vector<int>{0}, 3),
            (std::pair<int, int>(0, 0)));
  ASSERT_EQ(GetNumbersOfSum(std::vector<int>{1, 2, 4, 4, 7}, 9),
            (std::pair<int, int>(2, 7)));
}