//
// Created by comrade77 on 06.07.2021.
//
#include <gtest/gtest.h>
#include <left.h>

TEST(LeftTest, CreateLeftTest) {
    auto left_exception = monad::left(std::invalid_argument("Test exception"));
    ASSERT_EQ(typeid(left_exception.value), typeid(std::invalid_argument));
    ASSERT_STREQ(left_exception.value.what(), "Test exception");
}