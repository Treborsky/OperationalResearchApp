add_library(
        Utility
        src/utility/utility.cpp
        src/utility/utility.h
)

target_include_directories(Utility PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)