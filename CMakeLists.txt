cmake_minimum_required(VERSION 3.29)
project(first C)

set(CMAKE_C_STANDARD 99)

add_executable(first main.c
        game.c
        game.h
        combat/combat.c
        combat/combat.h
        character/inventory.c
        character/inventory.h
        map/map.c
        map/map.h
        game.c
        constants.h
        utils.c
        utils.c
        character/character.c
        character/character.h)
