
#include <gtest/gtest.h>

#include <vector>

#include "tree.hpp"

TEST(Tree, Simple) {
  Tree tree;
  ASSERT_EQ(tree.Insert(1, 2), true);   // 1: 2
  ASSERT_EQ(tree.Insert(1, 2), false);  // 1: 2
}