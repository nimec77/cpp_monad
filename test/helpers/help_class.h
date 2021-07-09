//
// Created by comrade77 on 09.07.2021.
//

#ifndef CPP_MONAD_HELP_CLASS_H
#define CPP_MONAD_HELP_CLASS_H

#include <either.h>

class HelpClass {
public:
    virtual ~HelpClass() {
        secret_value = 0;
    }
    using CreateHelpClassTyp = monad::Either<std::exception, HelpClass>;
    static CreateHelpClassTyp CreateTestClass(int secret_value) {
        auto testClass = HelpClass(secret_value);
        return HelpClass::CreateHelpClassTyp::RightOf(testClass);
    }
    static CreateHelpClassTyp CreateException(const std::exception& exception) {
        return HelpClass::CreateHelpClassTyp::LeftOf(exception);
    }

    [[nodiscard]] int add(int a) const {
        return secret_value + a;
    }
private:
    int& secret_value;
    explicit HelpClass(int &secret_value) : secret_value(secret_value) {}
};



#endif//CPP_MONAD_HELP_CLASS_H
