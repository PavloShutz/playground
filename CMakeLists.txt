cmake_minimum_required(VERSION 3.28)
project(TicTacToe LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_LIST_DIR}/copy_assets.cmake
)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main 
    src/main.cpp
    src/Cell.cpp
    src/Figure.cpp
    src/Grid.cpp
)
target_link_libraries(main PRIVATE SFML::Graphics SFML::Audio)
add_dependencies(main copy_assets)
target_include_directories(main PRIVATE "include" "assets")
