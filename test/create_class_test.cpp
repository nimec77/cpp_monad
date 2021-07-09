//
// Created by comrade77 on 09.07.2021.
//
#include "helpers/help_class.h"
#include <either.h>
#include <gtest/gtest.h>

HelpClass*  help_class_ptr = nullptr;

class CreateClassTest : public ::testing::Test {
public:
    static CreateClassTest *class_test;

    static void SetUpTestSuite() {
        std::cout << "SetUpTestSuite" << std::endl;
        auto either = HelpClass::CreateTestClass(40);
        either.WhenRight([](auto help_class) {
           help_class_ptr = &help_class;
        });
    }

    static void TearDownTestSuite() {
        std::cout << "TearDownTestSuite" << std::endl;
        help_class_ptr = nullptr;
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

TEST_F(CreateClassTest, Test1) {
    if (help_class_ptr == nullptr) {
        FAIL();
    }
    std::cout << help_class_ptr->add(2) << std::endl;
    SUCCEED();
}

TEST_F(CreateClassTest, Test2) {
    SUCCEED();
}