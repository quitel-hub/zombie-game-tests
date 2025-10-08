cmake_minimum_required(VERSION 3.30)
project(untitled23)

set(CMAKE_CXX_STANDARD 20)

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
)
