#include <stdio.h>
#include "map.h"
#include <stdlib.h>

// Define the number of rooms
#define TOTAL_ROOMS 11

// Static array of Room pointers
static Room *rooms[TOTAL_ROOMS];

// Helper function to set room exits
void setRoomExits(Room *room, int north, int east, int south, int west)
{
    room->exits[NORTH] = north;
    room->exits[EAST] = east;
    room->exits[SOUTH] = south;
    room->exits[WEST] = west;
}

// Helper function to set descriptions for a room
void setRoomDescriptions(Room *room, const char *description, const char *lookAroundText)
{
    room->description = description;
    room->lookAroundText = lookAroundText;
}

// Initialize each room with specific exits, features, monsters, and descriptions
Room **initializeMap()
{
    // Allocate and initialize each room
    for (int i = 0; i < TOTAL_ROOMS; i++)
    {
        rooms[i] = (Room *)malloc(sizeof(Room));
        rooms[i]->hasMonster = false;
        rooms[i]->hasSecretPassage = false;
        rooms[i]->monsterDefeated = false;
        rooms[i]->secretPassageRevealed = false;
        setRoomExits(rooms[i], NONE, NONE, NONE, NONE); // Initialize exits to NONE
        rooms[i]->description = "";
        rooms[i]->lookAroundText = "";
    }

    // Room 1: Tutorial Room
    setRoomExits(rooms[1], 3, NONE, NONE, NONE);
    setRoomDescriptions(rooms[1],
                        "1 description",
                        "1 lookaround text");

    // Room 3: First Room with secret passage and monster
    setRoomExits(rooms[3], 6, 4, NONE, 2);
    rooms[3]->hasSecretPassage = true;
    rooms[3]->hasMonster = true;
    setRoomDescriptions(rooms[3],
                        "3 description",
                        "3 lookaround text");

    // Room 2: Two visible exits
    setRoomExits(rooms[2], 5, 3, NONE, NONE);
    setRoomDescriptions(rooms[2],
                        "2 description",
                        "2 lookaround text");

    // Room 4: Two visible exits
    setRoomExits(rooms[4], 7, NONE, NONE, 3);
    setRoomDescriptions(rooms[4],
                        "4 description",
                        "4 lookaround text");

    // Room 6: Four exits, one hidden to Room 5
    setRoomExits(rooms[6], 9, 7, 3, 5);
    rooms[5]->hasSecretPassage = true;
    setRoomDescriptions(rooms[6],
                        "6 description",
                        "6 lookaround text");

    // Room 5: Visible and hidden exit, with a monster
    setRoomExits(rooms[5], 8, NONE, 2, NONE);
    rooms[5]->hasMonster = true;
    setRoomDescriptions(rooms[5],
                        "5 description",
                        "5 lookaround text");

    // Room 7: Visible and hidden exit, with a monster
    setRoomExits(rooms[7], 10, NONE, 4, NONE);
    rooms[7]->hasSecretPassage = true;
    rooms[7]->hasMonster = true;
    setRoomDescriptions(rooms[7],
                        "7 description",
                        "7 lookaround text");

    // Room 8: Two exits
    setRoomExits(rooms[8], NONE, 9, 5, NONE);
    setRoomDescriptions(rooms[8],
                        "8 description",
                        "8 lookaround text");

    // Room 10: Two exits
    setRoomExits(rooms[10], NONE, NONE, 7, 9);
    setRoomDescriptions(rooms[10],
                        "10 description",
                        "10 lookaround text");

    // Room 9: Visible and hidden exit, with a monster
    setRoomExits(rooms[9], 11, 10, NONE, 8);
    rooms[9]->hasSecretPassage = true;
    rooms[9]->hasMonster = true;
    setRoomDescriptions(rooms[9],
                        "9 description",
                        "9 lookaround text");

    // Boss Room (Room 11) with a monster
    setRoomExits(rooms[11], NONE, NONE, 9, NONE);
    rooms[11]->hasMonster = true;
    setRoomDescriptions(rooms[11],
                        "11 description",
                        "11 lookaround text");

    return rooms;
}

// Function to retrieve a room by its number
Room *getRoom(int roomNumber)
{
    if (roomNumber >= 0 && roomNumber < TOTAL_ROOMS)
    {
        return rooms[roomNumber];
    }
    return NULL; // Return NULL if room number is out of bounds
}
