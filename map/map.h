#ifndef MAP_H
#define MAP_H

#include <stdbool.h>
#include "../character/item.h"

#define MAX_DESCRIPTION_LINES 5
#define MAX_LOOK_AROUND_LINES 5

// Enum to represent directions for room exits
typedef enum {
    NONE = -1, // No exit in that direction
    NORTH,
    EAST,
    SOUTH,
    WEST
} Direction;

// Room structure to hold room details and exits
typedef struct {
    bool hasMonster;
    bool hasSecretPassage;
    bool monsterDefeated;
    bool secretPassageRevealed;
    int exits[4]; // Stores room numbers for exits in NORTH, EAST, SOUTH, WEST directions
    const char *description[MAX_DESCRIPTION_LINES]; // Array for multi-line descriptions
    const char *lookAroundText[MAX_LOOK_AROUND_LINES]; // Array for multi-line look-around texts
    int descriptionLineCount; // Number of lines in the description
    int lookAroundLineCount; // Number of lines in the look-around text
    Potion loot[5];
} Room;

// Initializes entire map and returns a list of pointers to each room
Room **initializeMap();

// Gets a specific room by its index in the array
Room *getRoom(int roomNumber);

#endif // MAP_H
