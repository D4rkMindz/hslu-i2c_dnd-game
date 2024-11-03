#ifndef MAP_H
#define MAP_H

#include <stdbool.h>

// Enum to represent directions for room exits
typedef enum
{
    NONE = -1, // No exit in that direction
    NORTH,
    EAST,
    SOUTH,
    WEST
} Direction;

// Room structure to hold room details and exits
typedef struct
{
    bool hasMonster;
    bool hasSecretPassage;
    bool monsterDefeated;
    bool secretPassageRevealed;
    int exits[4];               // Stores room numbers for exits in NORTH, EAST, SOUTH, WEST directions
    const char *description;    // Short description shown upon entering the room
    const char *lookAroundText; // Detailed text shown when looking around
} Room;

// Initializes entire map and returns a list of pointers to each room
Room **initializeMap();

// Gets a specific room by its index in the array
Room *getRoom(int roomNumber);

#endif // MAP_H