//
// Created by comrade77 on 09.07.2021.
//

#ifndef CPP_MONAD_HELP_CLASS_H
#define CPP_MONAD_HELP_CLASS_H

#include <either.h>
#include <iostream>

class HelpClass {
public:
    virtual ~HelpClass() {
        secret_value = 0;
        std::cout << "~HelpClass:" << secret_value << std::endl;
    }

    using HelpClassEither = monad::Either<std::exception, HelpClass *>;
    static HelpClassEither CreateTestClass(int secret_value);
    static HelpClassEither GetInstance();

    [[nodiscard]] int Add(int a) const {
        std::cout << "Add:" << secret_value << " + " << a << std::endl;
        return secret_value + a;
    }

    HelpClass(const HelpClass &) = delete;
    void operator=(const HelpClass &) = delete;

protected:
    int secret_value;
    explicit HelpClass(int secret_value) : secret_value(secret_value) {
        std::cout << "HelpClass:" << this->secret_value << std::endl;
    }

private:
};

HelpClass *created_test_class = nullptr;

HelpClass::HelpClassEither HelpClass::CreateTestClass(int secret_value) {
    std::cout << "CreateTestClass:" << secret_value << std::endl;
    if (created_test_class == nullptr) {
        created_test_class = new HelpClass(secret_value);
    }
    return HelpClass::HelpClassEither::RightOf(created_test_class);
}

HelpClass::HelpClassEither HelpClass::GetInstance() {
    if (created_test_class == nullptr) {
        auto exception = std::runtime_error("First you need to create an object of the class");
        return HelpClass::HelpClassEither::LeftOf(exception);
    }
    return HelpClass::HelpClassEither::RightOf(created_test_class);
}


#endif//CPP_MONAD_HELP_CLASS_H
