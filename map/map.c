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

    // Room 0: Tutorial Room
    setRoomExits(rooms[0], 2, NONE, NONE, NONE);
    setRoomDescriptions(rooms[0],
                        "0 description",
                        "0 lookaround text");

    // Room 2: First Room with secret passage and monster
    setRoomExits(rooms[2], 5, 3, NONE, 1);
    rooms[2]->hasSecretPassage = true;
    rooms[2]->hasMonster = true;
    setRoomDescriptions(rooms[2],
                        "2 description",
                        "2 lookaround text");

    // Room 1: Two visible exits
    setRoomExits(rooms[1], 4, 2, NONE, NONE);
    setRoomDescriptions(rooms[1],
                        "1 description",
                        "1 lookaround text");

    // Room 3: Two visible exits
    setRoomExits(rooms[3], 6, NONE, NONE, 2);
    setRoomDescriptions(rooms[3],
                        "3 description",
                        "3 lookaround text");

    // Room 5: Four exits, one hidden to Room 4
    setRoomExits(rooms[5], 8, 6, 2, 4);
    rooms[4]->hasSecretPassage = true;
    setRoomDescriptions(rooms[5],
                        "5 description",
                        "5 lookaround text");

    // Room 4: Visible and hidden exit, with a monster
    setRoomExits(rooms[4], 7, NONE, 1, NONE);
    rooms[4]->hasMonster = true;
    setRoomDescriptions(rooms[4],
                        "4 description",
                        "4 lookaround text");

    // Room 6: Visible and hidden exit, with a monster
    setRoomExits(rooms[6], 9, NONE, 3, NONE);
    rooms[6]->hasSecretPassage = true;
    rooms[6]->hasMonster = true;
    setRoomDescriptions(rooms[6],
                        "6 description",
                        "6 lookaround text");

    // Room 7: Two exits
    setRoomExits(rooms[7], NONE, 8, 4, NONE);
    setRoomDescriptions(rooms[7],
                        "7 description",
                        "7 lookaround text");

    // Room 9: Two exits
    setRoomExits(rooms[9], NONE, NONE, 6, 8);
    setRoomDescriptions(rooms[9],
                        "9 description",
                        "9 lookaround text");

    // Room 8: Visible and hidden exit, with a monster
    setRoomExits(rooms[8], 10, 9, NONE, 7);
    rooms[8]->hasSecretPassage = true;
    rooms[8]->hasMonster = true;
    setRoomDescriptions(rooms[8],
                        "8 description",
                        "8 lookaround text");

    // Boss Room (Room 10) with a monster
    setRoomExits(rooms[10], NONE, NONE, 8, NONE);
    rooms[10]->hasMonster = true;
    setRoomDescriptions(rooms[10],
                        "10 description",
                        "10 lookaround text");

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