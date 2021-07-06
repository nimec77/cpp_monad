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
    auto right_int = right(6 * 7);
    ASSERT_EQ(typeid(right_int.value), typeid(int));
    ASSERT_EQ(right_int.value, 42);

    auto str = std::string{"Test value"};
    auto right_str = right(str);
    ASSERT_EQ(typeid(right_str.value), typeid(std::string));
    ASSERT_STREQ(right_str.value.c_str(), str.c_str());

    auto testClass = TestClass(40, 2);
    auto right_class = right(testClass);
    ASSERT_EQ(typeid(right_class.value), typeid(TestClass));

    ASSERT_EQ(right_class.value.add(), 42);
}