add_library(
        Model
        src/model/model.cpp
        src/model/model.h
)

target_include_directories(Model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(Model PRIVATE DataTypes)