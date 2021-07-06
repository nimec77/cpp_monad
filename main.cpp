#include <iostream>
#include <left.h>

int main() {
    auto left_int = monad::left(1);
    std::cout << "Left Test:" << left_int.value << std::endl;

    return 0;
}
