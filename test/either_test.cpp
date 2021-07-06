//
// Created by comrade77 on 06.07.2021.
//

#include <either.h>
#include <gtest/gtest.h>

using namespace monad;

TEST(EitherTest, CreateEitherFromLeftTest) {
    auto left_exception = left(std::invalid_argument("Test exception"));
    auto either = Either<std::invalid_argument, int>(left_exception);
    ASSERT_TRUE(either.isLeft);
    ASSERT_EQ(typeid(either.left_value), typeid(std::invalid_argument));
    ASSERT_STREQ(either.left_value.what(), "Test exception");
    ASSERT_EQ(typeid(either.right_value), typeid(int));
}
