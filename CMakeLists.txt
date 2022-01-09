cmake_minimum_required(VERSION 3.20)
project(OperationalResearchApp)
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
## For Windows: Prevent overriding the parent project's compiler/linker settings
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(src)
add_executable(App main.cpp src/model.cpp src/utility.cpp)

target_compile_features(App PUBLIC cxx_std_20)

enable_testing()

add_executable(
        UnitTests
        test/basic_test.cpp
)
target_link_libraries(
        UnitTests
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(UnitTests)