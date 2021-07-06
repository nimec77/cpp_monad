//
// Created by comrade77 on 06.07.2021.
//

#include <either.h>
#include <gtest/gtest.h>

using namespace monad;

TEST(EitherTest, CreateEitherFromLeftTest) {
    auto left_exception = left(std::invalid_argument("Test exception"));
    auto either = Either<std::invalid_argument, int>{left_exception};
    ASSERT_TRUE(either.isLeft);

    auto e = Either<std::invalid_argument, int>::LeftOf(left_exception.value);
    ASSERT_TRUE(e.isLeft);
}

TEST(EitherTest, CreateEitherFromRightTest) {
    auto right_int = monad::right(6 * 7);
    auto either = Either<std::exception, int>{right_int};
    ASSERT_FALSE(either.isLeft);

    auto str = std::string{"Test value"};
    auto e = Either<std::exception, std::string>::RightOf(str);
    ASSERT_FALSE(e.isLeft);
}

TEST(EitherTest, EitherFoldTest) {
    auto answer = 42;
    auto either = Either<std::exception, int>::RightOf(answer);

    auto result = either.Fold(
            [](auto l) { return -1; },
            [](auto r) { return r; });
    ASSERT_EQ(42, result);
}

TEST(EitherTest, EitherGetOrElseTest) {
    auto answer = 42;
    auto either = Either<std::exception, int>::RightOf(answer);

    auto result = either.GetOrElse([](auto l) { return -1;});
    ASSERT_EQ(result, 42);
    result = either.GetOrDefault(-1);
    ASSERT_EQ(result, 42);

    auto str = "Test";
    auto e = Either<std::exception, const char*>::RightOf(str);

    auto result_str = e.GetOrElse([](auto l) { return "Error!";});
    ASSERT_STREQ(result_str, str);
    result_str = e.GetOrDefault("Error!");
    ASSERT_STREQ(result_str, str);
}