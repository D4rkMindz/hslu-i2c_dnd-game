//
// Created by Björn Pfoster on 15.12.2024.
//

#ifndef ROOM_H
#define ROOM_H
#define MAX_DESCRIPTION_LINES 5
#define MAX_LOOK_AROUND_LINES 5
#define MAX_MONSTER_COUNT 2
#include <stdbool.h>
#include "../character/item.h"

// Enum to represent directions for room exits
typedef enum {
    NONE = -1, // No exit in that direction
    NORTH,
    EAST,
    SOUTH,
    WEST,
} Direction;

// Room structure to hold room details and exits
typedef struct {
    int id;
    char *name;
    bool hasMonster;
    char *monsters[MAX_MONSTER_COUNT];
    bool monsterDefeated;
    int secretPassage;
    bool secretPassageRevealed;
    int exits[4]; // Stores room numbers for exits in NORTH, EAST, SOUTH, WEST directions
    char *description[MAX_DESCRIPTION_LINES]; // Array for multi-line descriptions
    char *lookAroundText[MAX_LOOK_AROUND_LINES]; // Array for multi-line look-around texts
    // int descriptionLineCount; // Number of lines in the description
    // int lookAroundLineCount; // Number of lines in the look-around text
    Potion loot[5];
} Room;

void load_rooms_from_file(const char *path, int *roomCountOut);

Room *get_room(int roomID);

#endif //ROOM_H
