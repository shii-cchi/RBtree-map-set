#include <gtest/gtest.h>

#include "../red_black_tree/red_black_tree.h"
#include "../red_black_tree/red_black_tree.tpp"

TEST(RedBlackTree, isEmpty) {
    s21::RedBlackTree<int> tree;
    EXPECT_TRUE(tree.isEmpty());
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
