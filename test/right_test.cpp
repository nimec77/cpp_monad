//
// Created by comrade77 on 06.07.2021.
//
#include <gtest/gtest.h>
#include <right.h>

class TestClass {
public:
    TestClass(int a, int b) : a(a), b(b) {}

    [[nodiscard]] int add() const {
        return a + b;
    }

private:
    int a;
    int b;
};

TEST(RightTest, CreateRightTest) {
    auto right_int = monad::right(6 * 7);
    ASSERT_EQ(typeid(right_int.value), typeid(int));
    ASSERT_EQ(right_int.value, 42);

    auto str = std::string{"Test value"};
    auto right_str = monad::right(str);
    ASSERT_EQ(typeid(right_str.value), typeid(std::string));
    ASSERT_STREQ(right_str.value.c_str(), str.c_str());

    auto testClass = TestClass(40, 2);
    auto right_class = monad::right(testClass);
    ASSERT_EQ(typeid(right_class.value), typeid(TestClass));
    ASSERT_EQ(right_class.value.add(), 42);

    auto  chars = &"Test string";
    auto right_char = monad::right(&"Test string");
    ASSERT_EQ(typeid(right_char.value), typeid(chars));
    ASSERT_STREQ(*right_char.value, *chars);

    auto str2 = "Test string2";
    auto right_str2 = monad::right(std::string{"Test string2"});
    ASSERT_EQ(typeid(right_str2.value), typeid(std::string));
    ASSERT_STREQ(right_str2.value.c_str(), str2);
}