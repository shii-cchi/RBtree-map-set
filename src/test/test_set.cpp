#include <gtest/gtest.h>

#include "../set/s21_set.h"
#include "../set/s21_set.tpp"

TEST(Set, Constructors_1) {
  s21::set<int> set_1;
  EXPECT_TRUE(set_1.size() == 0);
  EXPECT_TRUE(set_1.empty());

  s21::set<int> set_2{1, 2};
  EXPECT_TRUE(set_2.size() == 2);
  EXPECT_TRUE(set_2.contains(1));
  EXPECT_TRUE(set_2.contains(2));

  s21::set<int> set_3(set_2);
  EXPECT_TRUE(set_3.size() == 2);
  EXPECT_TRUE(set_3.contains(1));
  EXPECT_TRUE(set_3.contains(2));
  EXPECT_TRUE(set_2 == set_3);

  s21::set<int> set_4(std::move(set_2));
  EXPECT_TRUE(set_4.size() == 2);
  EXPECT_TRUE(set_4.contains(1));
  EXPECT_TRUE(set_4.contains(2));
  EXPECT_TRUE(set_2.size() == 0);
}

TEST(Set, Constructors_2) {
  s21::set<int> set_1{1, 2};

  s21::set<int> set_2;
  set_2 = set_1;
  EXPECT_TRUE(set_2.size() == 2);
  EXPECT_TRUE(set_2.contains(1));
  EXPECT_TRUE(set_2.contains(2));
  EXPECT_TRUE(set_1 == set_2);

  s21::set<int> set_3;
  set_3 = std::move(set_1);
  EXPECT_TRUE(set_3.size() == 2);
  EXPECT_TRUE(set_3.contains(1));
  EXPECT_TRUE(set_3.contains(2));
  EXPECT_TRUE(set_1.size() == 0);
}

TEST(Set, Clear) {
  s21::set<int> set{1, 2};
  EXPECT_TRUE(set.contains(1));
  EXPECT_TRUE(set.contains(2));
  set.clear();
  EXPECT_TRUE(set.size() == 0);
  EXPECT_TRUE(set.empty());
}

TEST(Set, Insert) {
  s21::set<int> set;
  EXPECT_TRUE(set.insert(1).second);
  EXPECT_TRUE(set.insert(2).second);
  EXPECT_TRUE(set.insert(3).second);
  EXPECT_FALSE(set.insert(3).second);
  EXPECT_TRUE(set.contains(1));
  EXPECT_TRUE(set.contains(2));
  EXPECT_TRUE(set.contains(3));
}

TEST(Set, Erase_1) {
  s21::set<int> set;
  EXPECT_TRUE(set.insert(1).second);
  EXPECT_TRUE(set.contains(1));
  set.erase(set.begin());
  EXPECT_TRUE(set.size() == 0);
  EXPECT_TRUE(set.empty());
}

TEST(Set, Erase_2) {
  s21::set<int> set;
  EXPECT_TRUE(set.insert(1).second);
  EXPECT_TRUE(set.insert(2).second);
  EXPECT_TRUE(set.insert(3).second);
  EXPECT_TRUE(set.contains(1));
  EXPECT_TRUE(set.contains(2));
  EXPECT_TRUE(set.contains(3));
  set.erase(set.find(1));
  EXPECT_EQ(set.find(1), set.end());
  set.erase(set.find(2));
  EXPECT_EQ(set.find(2), set.end());
  set.erase(set.find(3));
  EXPECT_EQ(set.find(3), set.end());
  EXPECT_TRUE(set.size() == 0);
}

TEST(Set, Swap) {
  s21::set<int> set_1;
  EXPECT_TRUE(set_1.insert(1).second);
  EXPECT_TRUE(set_1.insert(2).second);
  EXPECT_TRUE(set_1.insert(3).second);

  s21::set<int> set_2;
  set_2.swap(set_1);
  EXPECT_TRUE(set_2.contains(1));
  EXPECT_TRUE(set_2.contains(2));
  EXPECT_TRUE(set_2.contains(3));
  EXPECT_TRUE(set_1.size() == 0);
}

TEST(Set, Merge) {
  s21::set<int> set_1;
  EXPECT_TRUE(set_1.insert(1).second);

  s21::set<int> set_2;
  EXPECT_TRUE(set_2.insert(2).second);
  EXPECT_TRUE(set_2.insert(3).second);

  set_1.merge(set_2);
  EXPECT_TRUE(set_1.contains(1));
  EXPECT_TRUE(set_1.contains(2));
  EXPECT_TRUE(set_1.contains(3));
  EXPECT_TRUE(set_2.size() == 0);
  EXPECT_TRUE(set_2.empty());
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}