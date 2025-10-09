cmake_minimum_required(VERSION 3.30)
project(untitled23)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SFML_DIR "C:/Users/quitel/CLionProjects/lib/sfml/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(untitled23 main.cpp
        Entity.h
        Player.h
        Zombie.h
        Boss.h
        Weapon.h
        Sword.h
        Gun.h
        Inventory.h
        Map.h
        Game.h
        Container.h
        LocalizationManager.h
        Command.h
        Game.cpp
)
target_link_libraries(untitled23 sfml-graphics sfml-window sfml-system)


#Google tests
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)


enable_testing()

add_executable(runTests tests/GameLogicTests.cpp
        tests/GameLogicTests.cpp)
target_link_libraries(runTests PRIVATE gtest_main)

include(GoogleTest)
gtest_discover_tests(runTests)