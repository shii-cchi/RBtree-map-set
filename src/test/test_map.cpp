#include <gtest/gtest.h>

#include "../map/s21_map.h"
#include "../map/s21_map.tpp"

TEST(Map, Constructors_1) {
  s21::map<int, std::string> map_1;
  EXPECT_TRUE(map_1.size() == 0);
  EXPECT_TRUE(map_1.empty());

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

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}