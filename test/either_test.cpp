//
// Created by comrade77 on 06.07.2021.
//

#include <either.h>
#include <gtest/gtest.h>

using namespace monad;

TEST(EitherTest, CreateEitherFromLeftTest) {
    auto left_exception = left(std::invalid_argument("Test exception"));
    auto either = Either<std::invalid_argument, int>{left_exception};
    ASSERT_FALSE(either);

    auto e = Either<std::invalid_argument, int>::LeftOf(left_exception.value);
    ASSERT_FALSE(e);
}

TEST(EitherTest, CreateEitherFromRightTest) {
    auto right_int = monad::right(6 * 7);
    auto either = Either<std::exception, int>{right_int};
    ASSERT_TRUE(either);

    auto str = std::string{"Test value"};
    auto e = Either<std::exception, std::string>::RightOf(str);
    ASSERT_TRUE(e);
}

TEST(EitherTest, EitherFoldTest) {
    auto answer = 42;
    auto either = Either<std::exception, int>::RightOf(answer);

    auto result = either.Fold(
            [](const auto l) { return -1; },
            [](const auto r) { return r; });
    ASSERT_EQ(answer, result);
}

TEST(EitherTest, EitherGetOrElseTest) {
    auto either = Either<std::exception, int>{right(42)};

    auto result = either.GetOrElse([](auto l) { return -1; });
    ASSERT_EQ(result, 42);
    result = either | -1;
    ASSERT_EQ(result, 42);

    auto str = "Test";
    auto e = Either<std::exception, const char *>::RightOf(str);

    auto result_str = e.GetOrElse([](auto l) { return "Error!"; });
    ASSERT_STREQ(result_str, str);
    result_str = e | "Error!";
    ASSERT_STREQ(result_str, str);
}

TEST(EitherTest, EitherRightMapTest) {
    auto either = Either<std::exception, int>{monad::right(6)};

    ASSERT_TRUE(either);

    auto new_either = either.RightMap([](const auto r) {
        return r * 7;
    });

    auto result = new_either | 0;
    ASSERT_EQ(result, 42);
}

TEST(EitherTest, EitherLeftMapTest) {
    const auto kMessage = "Error message!";
    const auto kNewMessage = "New error message!";
    auto error = std::runtime_error(kMessage);
    auto either = Either<std::runtime_error, int>::LeftOf(error);

    ASSERT_FALSE(either);

    auto new_either = either.LeftMap([kMessage, kNewMessage](const auto l) {
        auto msg = l.what();
        EXPECT_TRUE(strcmp(msg, kMessage) == 0);

        return std::invalid_argument(kNewMessage);
    });

    ASSERT_FALSE(new_either);

    new_either.When(
            [kNewMessage](const auto l) {
                EXPECT_EQ(typeid(l), typeid(std::invalid_argument));
                auto msg = l.what();
                EXPECT_TRUE(strcmp(msg, kNewMessage) == 0);
            },
            [](const auto r) {});
}

TEST(EitherTest, EitherRightFlatMapTest) {
    const auto kMessage = "Message";
    auto either = Either<std::exception, int>{monad::right(42)};

    ASSERT_TRUE(either);

    auto new_either = either.RightFlatMap([kMessage](const auto r) {
        EXPECT_EQ(r, 42);
        auto str = std::string(kMessage);

        return Either<std::exception, std::string>::RightOf(str);
    });

    auto result = new_either | "Error!";

    ASSERT_STREQ(result.c_str(), kMessage);
}

TEST(EitherTest, EitherLeftFlatMapTest) {
    const auto kMessage = "Error message!";
    const auto kNewMessage = "New Error message!";
    auto either = Either<std::runtime_error, std::string>{monad::left(std::runtime_error(kMessage))};

    ASSERT_FALSE(either);

    auto new_either = either.LeftFlatMap([kMessage, kNewMessage](const auto l) {
        EXPECT_EQ(typeid(l), typeid(std::runtime_error));
        auto msg = l.what();
        EXPECT_TRUE(strcmp(msg, kMessage) == 0);

        auto new_l = std::invalid_argument(kNewMessage);

        return Either<std::invalid_argument, std::string>::LeftOf(new_l);
    });

    ASSERT_FALSE(new_either);

    new_either.When(
            [kNewMessage](const auto l) {
                EXPECT_EQ(typeid(l), typeid(std::invalid_argument));
                auto msg = l.what();
                EXPECT_TRUE(strcmp(msg, kNewMessage) == 0);
                std::exit(0);
            },
            [](const auto r) {});

    FAIL();
}

TEST(EitherTest, EitherWhenLeftTest) {
    const auto kMessage = "Error message!";
    auto either = Either<std::runtime_error, std::string>{monad::left(std::runtime_error(kMessage))};

    ASSERT_FALSE(either);

    either.WhenLeft([kMessage](const auto l) {
        ASSERT_EQ(typeid(l), typeid(std::runtime_error));
        auto msg = l.what();
        ASSERT_STREQ(msg, kMessage);
        std::exit(0);
    });

    FAIL();
}

TEST(EitherTest, EitherWhenRightTest) {
    auto either = Either<std::exception, int>{monad::right(42)};

    ASSERT_TRUE(either);

    either.WhenRight([](const auto r) {
        ASSERT_EQ(r, 42);
        std::exit(0);
    });

    FAIL();
}