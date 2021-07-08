//
// Created by comrade77 on 06.07.2021.
//
#include <gtest/gtest.h>
#include <right.h>

class TestClass {
public:
    TestClass(int a, int b) : a(a), b(b) {}

    [[nodiscard]] constexpr int add() const {
        return a + b;
    }

private:
    const int a;
    const int b;
};

TEST(RightTest, CreateRightTest) {
    const auto right_int = monad::right(6 * 7);
    ASSERT_EQ(typeid(right_int.value), typeid(int));
    ASSERT_EQ(right_int.value, 42);

    const auto str = std::string{"Test value"};
    const auto right_str = monad::right(str);
    ASSERT_EQ(typeid(right_str.value), typeid(std::string));
    ASSERT_STREQ(right_str.value.c_str(), str.c_str());

    const auto testClass = TestClass(40, 2);
    const auto right_class = monad::right(testClass);
    ASSERT_EQ(typeid(right_class.value), typeid(TestClass));
    ASSERT_EQ(right_class.value.add(), 42);

    const auto  str2 = &"Test string";
    const auto right_char = monad::right(&"Test string");
    ASSERT_EQ(typeid(right_char.value), typeid(str2));
    ASSERT_STREQ(*right_char.value, *str2);
}