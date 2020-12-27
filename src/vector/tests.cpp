// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <gtest/gtest.h>
#include "vector/my_vector.h"


TEST(constr, default){
    my_vector<int> v;
    EXPECT_EQ(v.size(), 0);
    EXPECT_TRUE(v.is_empty());
    EXPECT_EQ(v.capacity(), 2);
}

TEST(constr, size){
    my_vector<int> v(5);
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.capacity(), 5);
    EXPECT_TRUE(v.is_empty());
}

TEST(constr, size_value){
    my_vector<int> v(5, 1);
    EXPECT_EQ(v.size(), 5);
    EXPECT_TRUE(!v.is_empty());
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 1);
    EXPECT_EQ(v[2], 1);
    EXPECT_EQ(v[3], 1);
    EXPECT_EQ(v[4], 1);
}

TEST(constr, copy){
    const my_vector<int> v(5, 1);
    my_vector<int> v_copy(v);
    EXPECT_EQ(v_copy.size(), v.size());
    EXPECT_EQ(v_copy[0], v[0]);
}

TEST(constr, init_list){
    my_vector<int> v{1, 2, 3};
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
}

TEST(operator, assign){
    const my_vector<int> v(5, 1);
    my_vector<int> v_copy = v;
    EXPECT_EQ(v_copy.size(), v.size());
    EXPECT_EQ(v_copy[0], v[0]);
}

TEST(func, at){
    my_vector<int> v(10);
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.capacity(), 10);
    EXPECT_THROW(v.at(5),  std::runtime_error);
    EXPECT_THROW(v.at(100),  std::runtime_error);
}

TEST(func, front_end){
    my_vector<int> v{1, 2};
    EXPECT_TRUE(v.front() == 1);
    EXPECT_TRUE(v.back() == 2);
}

TEST(func, clear){
    my_vector<int> v{1, 2};
    v.clear();
    EXPECT_TRUE(v.is_empty());
    EXPECT_EQ(v.capacity(), 4);
}

TEST(func, reserve){
    my_vector<int> v;
    v.reserve(4);
    EXPECT_EQ(v.capacity(), 4);
    EXPECT_EQ(v.size(), 0);
}

TEST(func, shrink){
    my_vector<int> v{1, 2, 3};
    EXPECT_TRUE(v.size() != v.capacity());
    v.shrink_to_fit();
    EXPECT_TRUE(v.size() == v.capacity());
}


TEST(func, resize){
    my_vector<int> v;
    v.resize(10);
    EXPECT_EQ(v.size(), 10);
    EXPECT_TRUE(v.capacity() >= 10);
}

TEST(func, swap){
    my_vector<int> v1{1, 2, 3};
    my_vector<int> v2;
    v2.swap(v1);
    EXPECT_EQ(v2.size(), 3);
    EXPECT_EQ(v1.size(), 0);

    EXPECT_EQ(v2.capacity(), 6);
    EXPECT_EQ(v1.capacity(), 2);

    EXPECT_EQ(v2[0], 1);
    EXPECT_EQ(v2[1], 2);
    EXPECT_EQ(v2[2], 3);
}

TEST(func, push_back){
    my_vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(v[3], 4);
    EXPECT_EQ(v[4], 5);
    EXPECT_EQ(v[5], 6);
    EXPECT_EQ(v.size(), 6);
}

TEST(func, pop_back){
    my_vector<int> v{1, 2, 3};
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v.back(), 3);
    v.pop_back();

    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v.back(), 2);
    v.pop_back();

    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v.back(), 1);
    v.pop_back();

    EXPECT_TRUE(v.is_empty());
}

TEST(func, emplace_back){
    my_vector<int> v;
    v.emplace_back(1);
    EXPECT_EQ(v[0], 1);

    my_vector<std::pair<int, int>> v1;
    v1.emplace_back(std::make_pair(1, 2));
    EXPECT_EQ(v1[0], std::make_pair(1, 2));
}

TEST(func, insert){
    my_vector<int> v;
    size_t amount = 2;
    int val = 25;
    int* iter = v.insert(v.begin(), amount, val);
    EXPECT_EQ(iter[0], 25);
    EXPECT_EQ(iter[1], 25);
    EXPECT_EQ(v[0], 25);
    EXPECT_EQ(v[1], 25);
    EXPECT_EQ(v.size(), 2);

    my_vector<int> v2{1, 2, 3}, v3{2};

    v3.insert(v3.begin() + 1, v2.begin(), v2.end());

    EXPECT_EQ(v3.size(), 4);
    EXPECT_EQ(v3[0], 2);
    EXPECT_EQ(v3[1], 1);
    EXPECT_EQ(v3[2], 2);
    EXPECT_EQ(v3[3], 3);
}

TEST(func, erase){
    my_vector<int> v{1, 2, 3};
    v.erase(v.cbegin());
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[0], 2);
    EXPECT_EQ(v[1], 3);

    v = {1, 2, 3, 4, 5};
    v.erase(v.begin() + 1, v.begin() + 3);
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 4);
    EXPECT_EQ(v[2], 5);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}