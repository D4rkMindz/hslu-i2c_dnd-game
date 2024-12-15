cmake_minimum_required(VERSION 3.29)
project(first C)

set(CMAKE_C_STANDARD 99)

add_executable(first
        main.c
        game.c
        game.h
        combat/combat.c
        combat/combat.h
        constants.h
        utils.c
        character/character.c
        character/character.h
        highscore/highscore.c
        character/item.c
        character/item.h
        map/room.c
        map/room.h
        map/file_parsing.c
        map/file_parsing.h
        lib/cJSON.c
        lib/cJSON.h
)