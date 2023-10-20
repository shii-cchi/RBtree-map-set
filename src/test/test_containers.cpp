#include <gtest/gtest.h>

#include "../map/s21_map.h"
#include "../set/s21_set.h"

// TREE//

TEST(RedBlackTree, Constructors_1) {
  s21::RedBlackTree<int> tree_1;
  tree_1.Insert(2);
  tree_1 = tree_1;

  s21::RedBlackTree<int> tree_2;
  tree_2 = tree_1;
  EXPECT_TRUE(tree_2.GetSize() == 1);
  EXPECT_NE(tree_2.Find(2), tree_2.End());

  s21::RedBlackTree<int> tree_3;
  tree_2 = tree_3;
  EXPECT_TRUE(tree_2.GetSize() == 0);
  EXPECT_EQ(tree_2.Find(2), tree_2.End());
}

TEST(RedBlackTree, Constructors_2) {
  s21::RedBlackTree<int> tree_1;
  tree_1.Insert(2);

  s21::RedBlackTree<int> tree_2;
  tree_2 = std::move(tree_1);
  EXPECT_TRUE(tree_2.GetSize() == 1);
  EXPECT_NE(tree_2.Find(2), tree_2.End());
}

TEST(RedBlackTree, Constructors_3) {
  s21::RedBlackTree<int> tree_1;
  tree_1.Insert(2);
  tree_1.Insert(1);
  tree_1.Insert(4);
  tree_1.Insert(5);

  s21::RedBlackTree<int> tree_2 = tree_1;
  EXPECT_TRUE(tree_2.GetSize() == 4);
  EXPECT_NE(tree_2.Find(2), tree_2.End());
  EXPECT_NE(tree_2.Find(1), tree_2.End());
  EXPECT_NE(tree_2.Find(4), tree_2.End());
  EXPECT_NE(tree_2.Find(5), tree_2.End());
}

TEST(RedBlackTree, Constructors_4) {
  s21::RedBlackTree<int> tree_1;
  tree_1.Insert(2);

  s21::RedBlackTree<int> tree_2 = std::move(tree_1);

  EXPECT_TRUE(tree_2.GetSize() == 1);
  EXPECT_NE(tree_2.Find(2), tree_2.End());
}

TEST(RedBlackTree, Iterator_1) {
  s21::RedBlackTree<int> tree;
  for (int i = 5; i >= 0; --i) {
    tree.Insert(i);
  }

  int expectedValue = 0;
  for (auto it = tree.Begin(); it != tree.End(); it++) {
    EXPECT_EQ(*it, expectedValue);
    ++expectedValue;
  }

  expectedValue = 5;
  for (auto it = tree.End(); it != tree.Begin(); it--) {
    if (it != tree.End()) {
      EXPECT_EQ(*it, expectedValue);
      --expectedValue;
    }
  }
}

TEST(RedBlackTree, Iterator_2) {
  s21::RedBlackTree<int> tree;
  tree.Insert(2);
  tree.Insert(1);
  tree.Insert(4);
  tree.Insert(5);
  tree.Insert(3);
  tree.Insert(6);
  tree.Insert(7);
  tree.Insert(8);

  auto it = tree.Find(9);
  it++;
  EXPECT_EQ(*it, 1);

  it = tree.Find(4);
  it++;
  EXPECT_EQ(*it, 5);

  it = tree.Find(1);
  it--;
  EXPECT_EQ(it, tree.End());
}

TEST(RedBlackTree, IteratorConst) {
  s21::RedBlackTree<int> tree;
  for (int i = 5; i >= 0; --i) {
    tree.Insert(i);
  }

  const s21::RedBlackTree<int> &const_tree = tree;

  int expectedValue = 0;
  for (auto it = const_tree.Begin(); it != const_tree.End(); it++) {
    EXPECT_EQ(*it, expectedValue);
    ++expectedValue;
  }

  expectedValue = 5;
  for (auto it = const_tree.End(); it != const_tree.Begin(); it--) {
    if (it == const_tree.End()) {
      continue;
    } else {
      EXPECT_EQ(*it, expectedValue);
      --expectedValue;
    }
  }
}

TEST(RedBlackTree, isEmpty_GetSize) {
  s21::RedBlackTree<int> tree;
  EXPECT_TRUE(tree.isEmpty());
  EXPECT_TRUE(tree.GetSize() == 0);
  tree.Insert(2);
  EXPECT_FALSE(tree.isEmpty());
  EXPECT_TRUE(tree.GetSize() == 1);
}

TEST(RedBlackTree, Insert_Find_1) {
  s21::RedBlackTree<int> tree;
  tree.Insert(2);
  tree.Insert(5);
  tree.Insert(3);
  tree.Insert(5);
  EXPECT_TRUE(tree.GetSize() == 3);
  tree.Insert(1);
  tree.Insert(6);
  EXPECT_FALSE(tree.isEmpty());
  EXPECT_TRUE(tree.GetSize() == 5);
  EXPECT_NE(tree.Find(3), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
  EXPECT_NE(tree.Find(5), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
  EXPECT_EQ(tree.Find(7), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
}

TEST(RedBlackTree, Insert_Find_2) {
  s21::RedBlackTree<int> tree;
  tree.Insert(7);
  tree.Insert(2);
  tree.Insert(3);
  tree.Insert(1);
  EXPECT_NE(tree.Find(7), tree.End());
  EXPECT_NE(tree.Find(2), tree.End());
  EXPECT_NE(tree.Find(3), tree.End());
  EXPECT_NE(tree.Find(1), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
}

TEST(RedBlackTree, Insert_Find_3) {
  s21::RedBlackTree<int> tree;
  tree.Insert(9);
  tree.Insert(8);
  tree.Insert(1);
  tree.Insert(4);
  tree.Insert(2);
  tree.Insert(3);
  tree.Insert(10);
  tree.Insert(11);
  tree.Insert(18);
  tree.Insert(19);
  tree.Insert(14);
  tree.Insert(12);
  tree.Insert(13);
  EXPECT_NE(tree.Find(13), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
}

TEST(RedBlackTree, Insert_Many) {
  s21::RedBlackTree<int> tree;
  tree.Insert_many(1, 7, 4, 5, 5, 3, 9);
  EXPECT_EQ(tree.GetSize(), 6);
  EXPECT_NE(tree.Find(1), tree.End());
  EXPECT_NE(tree.Find(7), tree.End());
  EXPECT_NE(tree.Find(4), tree.End());
  EXPECT_NE(tree.Find(5), tree.End());
  EXPECT_NE(tree.Find(3), tree.End());
  EXPECT_NE(tree.Find(9), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
}

TEST(RedBlackTree, Merge_1) {
  s21::RedBlackTree<int> tree_1;
  tree_1.Insert(2);
  tree_1.Insert(5);
  s21::RedBlackTree<int> tree_2;
  tree_2.Insert(2);
  tree_2.Insert(5);
  tree_1.Merge(tree_2);
  EXPECT_EQ(tree_1.GetSize(), 2);
  EXPECT_EQ(tree_2.GetSize(), 2);
  EXPECT_NE(tree_1.Find(2), tree_1.End());
  EXPECT_NE(tree_1.Find(5), tree_1.End());
  EXPECT_NE(tree_2.Find(2), tree_2.End());
  EXPECT_NE(tree_2.Find(5), tree_2.End());
  EXPECT_EQ(tree_1.CheckTree(), true);
  EXPECT_EQ(tree_2.CheckTree(), true);
}

TEST(RedBlackTree, Merge_2) {
  s21::RedBlackTree<int> tree_1;
  tree_1.Insert(2);
  tree_1.Insert(5);
  s21::RedBlackTree<int> tree_2;
  tree_2.Insert(1);
  tree_2.Insert(4);
  tree_1.Merge(tree_2);
  EXPECT_EQ(tree_1.GetSize(), 4);
  EXPECT_EQ(tree_2.GetSize(), 0);
  EXPECT_NE(tree_1.Find(1), tree_1.End());
  EXPECT_NE(tree_1.Find(2), tree_1.End());
  EXPECT_NE(tree_1.Find(4), tree_1.End());
  EXPECT_NE(tree_1.Find(5), tree_1.End());
  EXPECT_EQ(tree_2.Find(1), tree_2.End());
  EXPECT_EQ(tree_2.Find(4), tree_2.End());
  EXPECT_EQ(tree_1.CheckTree(), true);
  EXPECT_EQ(tree_2.CheckTree(), true);
}

TEST(RedBlackTree, Erase_1) {
  s21::RedBlackTree<int> tree;
  tree.Insert(2);
  tree.Insert(5);
  tree.Erase(tree.Find(3));
  tree.Erase(tree.Find(2));
  EXPECT_EQ(tree.Find(2), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
}

TEST(RedBlackTree, Erase_2) {
  s21::RedBlackTree<int> tree;
  tree.Insert(2);
  tree.Insert(5);
  tree.Insert(1);
  tree.Insert(4);
  tree.Insert(3);
  tree.Insert(7);
  tree.Erase(tree.Find(3));
  EXPECT_EQ(tree.Find(3), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
  tree.Erase(tree.Find(4));
  EXPECT_EQ(tree.Find(4), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
  tree.Erase(tree.Find(7));
  EXPECT_EQ(tree.Find(7), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
  tree.Erase(tree.Find(1));
  EXPECT_EQ(tree.Find(1), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
}

TEST(RedBlackTree, Erase_3) {
  s21::RedBlackTree<int> tree;
  tree.Insert(1);
  tree.Insert(9);
  tree.Insert(7);
  tree.Insert(4);
  tree.Insert(3);
  tree.Insert(5);
  tree.Insert(6);
  tree.Insert(8);
  tree.Erase(tree.Find(3));
  EXPECT_EQ(tree.Find(3), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
  tree.Erase(tree.Find(4));
  EXPECT_EQ(tree.Find(4), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
  tree.Erase(tree.Find(7));
  EXPECT_EQ(tree.Find(7), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
  tree.Erase(tree.Find(1));
  EXPECT_EQ(tree.Find(1), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
  tree.Erase(tree.Find(8));
  EXPECT_EQ(tree.Find(8), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
  tree.Erase(tree.Find(9));
  EXPECT_EQ(tree.Find(9), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
  tree.Erase(tree.Find(5));
  EXPECT_EQ(tree.Find(5), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
  tree.Erase(tree.Find(6));
  EXPECT_EQ(tree.Find(6), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
}

TEST(RedBlackTree, Erase_4) {
  s21::RedBlackTree<int> tree;
  tree.Insert(10);
  tree.Insert(2);
  tree.Insert(3);
  tree.Insert(9);
  tree.Insert(5);
  tree.Insert(1);
  tree.Insert(7);
  tree.Insert(4);
  tree.Erase(tree.Find(7));
  EXPECT_EQ(tree.Find(7), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
  tree.Erase(tree.Find(3));
  EXPECT_EQ(tree.Find(3), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
  tree.Erase(tree.Find(2));
  EXPECT_EQ(tree.Find(2), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
  tree.Erase(tree.Find(10));
  EXPECT_EQ(tree.Find(10), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
  tree.Erase(tree.Find(9));
  EXPECT_EQ(tree.Find(9), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
  tree.Erase(tree.Find(1));
  EXPECT_EQ(tree.Find(1), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
  tree.Erase(tree.Find(4));
  EXPECT_EQ(tree.Find(4), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
  tree.Erase(tree.Find(5));
  EXPECT_EQ(tree.Find(5), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
}

TEST(RedBlackTree, Erase_5) {
  s21::RedBlackTree<int> tree;
  tree.Insert(1);
  tree.Insert(2);
  tree.Insert(3);
  tree.Insert(4);
  tree.Insert(5);
  tree.Insert(6);
  tree.Erase(tree.Find(1));
  EXPECT_EQ(tree.Find(1), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
  tree.Erase(tree.Find(2));
  EXPECT_EQ(tree.Find(2), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
  tree.Erase(tree.Find(3));
  EXPECT_EQ(tree.Find(3), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
  tree.Erase(tree.Find(4));
  EXPECT_EQ(tree.Find(4), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
  tree.Erase(tree.Find(5));
  EXPECT_EQ(tree.Find(5), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
  tree.Erase(tree.Find(6));
  EXPECT_EQ(tree.Find(6), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
}

TEST(RedBlackTree, Erase_6) {
  s21::RedBlackTree<int> tree;
  tree.Insert(9);
  tree.Insert(1);
  tree.Insert(3);
  tree.Insert(7);
  tree.Insert(11);
  tree.Insert(5);
  tree.Insert(6);
  tree.Insert(2);
  tree.Insert(4);
  tree.Insert(8);
  tree.Insert(12);
  tree.Insert(13);
  tree.Erase(tree.Find(12));
  EXPECT_EQ(tree.Find(12), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
  tree.Erase(tree.Find(5));
  EXPECT_EQ(tree.Find(5), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
  tree.Erase(tree.Find(8));
  EXPECT_EQ(tree.Find(8), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
  tree.Erase(tree.Find(7));
  EXPECT_EQ(tree.Find(7), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
  tree.Erase(tree.Find(11));
  EXPECT_EQ(tree.Find(11), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
  tree.Erase(tree.Find(9));
  EXPECT_EQ(tree.Find(9), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
  tree.Erase(tree.Find(6));
  EXPECT_EQ(tree.Find(6), tree.End());
  EXPECT_EQ(tree.CheckTree(), true);
}

// MAP//

TEST(Map, Constructors_1) {
  s21::map<int, std::string> map_1;
  EXPECT_TRUE(map_1.size() == 0);
  EXPECT_TRUE(map_1.empty());
  map_1.max_size();

  s21::map<int, std::string> map_2{{1, "1"}, {2, "2"}};
  EXPECT_TRUE(map_2.size() == 2);
  EXPECT_TRUE(map_2.contains(1));
  EXPECT_TRUE(map_2.contains(2));

  s21::map<int, std::string> map_3(map_2);
  EXPECT_TRUE(map_3.size() == 2);
  EXPECT_TRUE(map_3.contains(1));
  EXPECT_TRUE(map_3.contains(2));
  EXPECT_TRUE(map_2 == map_3);

  s21::map<int, std::string> map_4(std::move(map_2));
  EXPECT_TRUE(map_4.size() == 2);
  EXPECT_TRUE(map_4.contains(1));
  EXPECT_TRUE(map_4.contains(2));
  EXPECT_TRUE(map_2.size() == 0);
}

TEST(Map, Constructors_2) {
  s21::map<int, std::string> map_1{{1, "1"}, {2, "2"}};

  s21::map<int, std::string> map_2;
  map_2 = map_1;
  EXPECT_TRUE(map_2.size() == 2);
  EXPECT_TRUE(map_2.contains(1));
  EXPECT_TRUE(map_2.contains(2));
  EXPECT_TRUE(map_1 == map_2);

  s21::map<int, std::string> map_3;
  map_3 = std::move(map_1);
  EXPECT_TRUE(map_3.size() == 2);
  EXPECT_TRUE(map_3.contains(1));
  EXPECT_TRUE(map_3.contains(2));
  EXPECT_TRUE(map_1.size() == 0);
}

TEST(Map, At) {
  s21::map<int, std::string> map{{1, "1"}, {2, "2"}};
  EXPECT_TRUE(map.at(1) == "1");
  EXPECT_TRUE(map.at(2) == "2");
  EXPECT_THROW(map.at(3), std::out_of_range);

  const s21::map<int, std::string> map_1{{1, "1"}, {2, "2"}};
  EXPECT_TRUE(map_1.at(1) == "1");
  EXPECT_TRUE(map_1.at(2) == "2");
  EXPECT_THROW(map_1.at(3), std::out_of_range);
}

TEST(Map, Brackets) {
  s21::map<int, std::string> map{{1, "1"}, {2, "2"}};
  EXPECT_TRUE(map[1] == "1");
  EXPECT_TRUE(map[2] == "2");
  EXPECT_TRUE(map[3] == "");

  map.clear();
  EXPECT_TRUE(map.size() == 0);
  EXPECT_TRUE(map.empty());
}

TEST(Map, Insert) {
  s21::map<int, std::string> map;
  EXPECT_TRUE(map.insert(1, "1").second);
  EXPECT_TRUE(map.insert(2, "2").second);
  EXPECT_TRUE(map.insert(3, "3").second);
  EXPECT_FALSE(map.insert(3, "4").second);
  EXPECT_TRUE(map[1] == "1");
  EXPECT_TRUE(map[2] == "2");
  EXPECT_TRUE(map[3] == "3");
  EXPECT_TRUE(map.size() == 3);
}

TEST(Map, Insert_Many) {
  s21::map<int, std::string> map;
  map.insert_many(std::make_pair(1, "1"), std::make_pair(2, "2"),
                  std::make_pair(3, "3"));
  EXPECT_TRUE(map[1] == "1");
  EXPECT_TRUE(map[2] == "2");
  EXPECT_TRUE(map[3] == "3");
  EXPECT_TRUE(map.size() == 3);
}

TEST(Map, InsertOrAssign) {
  s21::map<int, std::string> map;
  EXPECT_TRUE(map.insert_or_assign(1, "1").second);
  EXPECT_TRUE(map.insert_or_assign(2, "2").second);
  EXPECT_TRUE(map.insert_or_assign(3, "3").second);
  EXPECT_FALSE(map.insert_or_assign(3, "4").second);
  EXPECT_TRUE(map[1] == "1");
  EXPECT_TRUE(map[2] == "2");
  EXPECT_TRUE(map[3] == "4");
}

TEST(Map, Erase_1) {
  s21::map<int, std::string> map;
  EXPECT_TRUE(map.insert(1, "1").second);
  EXPECT_TRUE(map[1] == "1");
  map.erase(map.begin());
  EXPECT_TRUE(map.size() == 0);
  EXPECT_TRUE(map.empty());
}

TEST(Map, Erase_2) {
  s21::map<int, std::string> map;
  EXPECT_TRUE(map.insert(1, "1").second);
  EXPECT_TRUE(map.insert(2, "2").second);
  EXPECT_TRUE(map.insert(3, "3").second);
  EXPECT_TRUE(map[1] == "1");
  EXPECT_TRUE(map[2] == "2");
  EXPECT_TRUE(map[3] == "3");
  map.erase(map.insert_or_assign(1, "1").first);
  map.erase(map.insert_or_assign(2, "2").first);
  map.erase(map.insert_or_assign(3, "3").first);
  EXPECT_TRUE(map.size() == 0);
}

TEST(Map, Swap) {
  s21::map<int, std::string> map_1;
  EXPECT_TRUE(map_1.insert(1, "1").second);
  EXPECT_TRUE(map_1.insert(2, "2").second);
  EXPECT_TRUE(map_1.insert(3, "3").second);

  s21::map<int, std::string> map_2;
  map_2.swap(map_1);

  EXPECT_TRUE(map_2[1] == "1");
  EXPECT_TRUE(map_2[2] == "2");
  EXPECT_TRUE(map_2[3] == "3");
  EXPECT_TRUE(map_1.size() == 0);
}

TEST(Map, Merge) {
  s21::map<int, std::string> map_1;
  EXPECT_TRUE(map_1.insert(1, "1").second);

  s21::map<int, std::string> map_2;
  EXPECT_TRUE(map_2.insert(2, "2").second);
  EXPECT_TRUE(map_2.insert(3, "3").second);

  map_1.merge(map_2);
  EXPECT_TRUE(map_1[1] == "1");
  EXPECT_TRUE(map_1[2] == "2");
  EXPECT_TRUE(map_1[3] == "3");
  EXPECT_TRUE(map_2.size() == 0);
  EXPECT_TRUE(map_2.empty());
}

// SET//

TEST(Set, Constructors_1) {
  s21::set<int> set_1;
  set_1.max_size();
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
  EXPECT_TRUE(set.size() == 3);
}

TEST(Set, Insert_Many) {
  s21::set<int> set;
  set.insert_many(1, 2, 3);
  EXPECT_TRUE(set.size() == 3);
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