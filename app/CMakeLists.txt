add_executable(
        App
        main.cpp
)

target_link_libraries(App PRIVATE Model DataTypes Utility)