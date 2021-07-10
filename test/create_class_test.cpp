//
// Created by comrade77 on 09.07.2021.
//
#include "helpers/help_class.h"
#include <either.h>
#include <gtest/gtest.h>

class CreateClassTest : public ::testing::Test {
public:
    static void SetUpTestSuite() {
        std::cout << "SetUpTestSuite" << std::endl;
        HelpClass::CreateTestClass(40);
    }

    static void TearDownTestSuite() {
        std::cout << "TearDownTestSuite" << std::endl;
        auto instance = HelpClass::GetInstance();
        instance.WhenRight([](const auto help_class) {
            help_class->~HelpClass();
        });
    }


protected:
    void SetUp() override {
        std::cout << "SetUp" << std::endl;
    }

    void TearDown() override {
        std::cout << "TearDown" << std::endl;
    }

private:
};

TEST_F(CreateClassTest, GetInstanceTest) {
    auto instance = HelpClass::GetInstance();
    ASSERT_TRUE(instance);

    ASSERT_EQ(typeid(instance), typeid(HelpClass::CreateHelpClassType));

    instance.WhenRight([](const auto help_class) {
        ASSERT_EQ(typeid(help_class), typeid(HelpClass *));
        auto result = help_class->Add(2);
        ASSERT_EQ(result, 42);
    });
    SUCCEED();
}
