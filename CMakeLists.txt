cmake_minimum_required(VERSION 3.19)
project(cpp_monad)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)


include_directories(monad)

set(SRS_LIST main.cpp)

add_executable(${PROJECT_NAME} ${SRS_LIST})

enable_testing()
set(SRC_TESTS
        test/left_test.cpp
        test/right_test.cpp
        test/main_test.cpp
        )

add_executable(
        google_test
        ${SRC_MONAD}
        ${SRC_TESTS}
)

target_link_libraries(google_test gtest_main)

include(GoogleTest)
gtest_discover_tests(google_test)
