//
// Created by Björn Pfoster on 15.12.2024.
//

#include <stddef.h>
#include <stdlib.h>
#include "room.h"

#include <stdio.h>

#include "file_parsing.h"
#include "../lib/cJSON.h"


static RoomArray rooms = {NULL, 0};
// Function to retrieve a room by its number
Room *get_room(int roomID) {
    if (roomID > 0 && roomID - 1 < rooms.size) {
        int pointer = rooms.size;
        while (pointer >= 0) {
            Room *room = &rooms.data[pointer];
            if (room && room->id == roomID) {
                return room;
            }
            pointer--;
        }
    }
    return NULL;
}

void fail_setup(const char *reason, int i) {
    fprintf(stderr, "%s", reason);

    // If something unexpected happens, cleanup and return NULL
    for (int k = 0; k < i; k++) {
        free((char *) rooms.data[k].name);
        for (int d = 0; d < sizeof(rooms.data[k].description); d++) {
            free((char *) rooms.data[k].description[d]);
        }
        for (int l = 0; l < sizeof(rooms.data[k].lookAroundText); l++) {
            free((char *) rooms.data[k].lookAroundText[l]);
        }
    }
    free(rooms.data);
    rooms.data = NULL;
    rooms.size = 0;
    reset();
}

// Helper to parse exits: returns -1 (NONE) if null, otherwise the integer value
static int parse_exit(cJSON *exits_obj, const char *direction_key) {
    cJSON *val = cJSON_GetObjectItemCaseSensitive(exits_obj, direction_key);
    if (!val || cJSON_IsNull(val)) {
        return -1;
    }
    if (cJSON_IsNumber(val)) {
        return val->valueint;
    }
    return -1; // If something unexpected, treat as NONE
}

void load_rooms_from_file(const char *path, int *roomCountOut) {
    *roomCountOut = 0;
    cJSON *root = read_file_json(path);

    cJSON *rooms_array = read_array(root, "rooms");
    if (rooms_array == NULL) {
        fprintf(stderr, "Error: Rooms not defined in %s\n", path);
        return;
    }
    int roomCount = cJSON_GetArraySize(rooms_array);

    rooms.data = calloc(roomCount, sizeof(Room));
    rooms.size = roomCount;

    for (int i = 0; i < roomCount; i++) {
        char failureReason[200];
        cJSON *room_obj = cJSON_GetArrayItem(rooms_array, i);
        if (!room_obj) {
            *roomCountOut = 0;
            sprintf(failureReason, "room[%d] failed", i);
            fail_setup(failureReason, i);
            return;
        }
        Room *room = &rooms.data[i];
        room->id = read_int(room_obj, "id");
        room->name = read_string(room_obj, "name");

        // Parse description array
        cJSON *description = read_array(room_obj, "description");
        if (description == NULL) {
            sprintf(failureReason, "room[%d].description failed\n", i);
            fail_setup(failureReason, i);
            return;
        }
        int descriptionCount = cJSON_GetArraySize(description);
        for (int d = 0; d < descriptionCount && d < MAX_DESCRIPTION_LINES; d++) {
            room->description[d] = read_array_item_string(description, d);
            if (room->description[d] == NULL) {
                break;
            }
        }

        // Parse description array
        cJSON *lookAroundText = read_array(room_obj, "look_around");
        if (lookAroundText == NULL) {
            sprintf(failureReason, "room[%d].lookAroundText failed\n", i);
            fail_setup(failureReason, i);
            return;
        }
        int lookAroundTextCount = cJSON_GetArraySize(lookAroundText);
        for (int d = 0; d < lookAroundTextCount && d < MAX_DESCRIPTION_LINES; d++) {
            room->lookAroundText[d] = read_array_item_string(lookAroundText, d);
            if (room->lookAroundText[d] == NULL) {
                break;
            }
        }

        // Parse description array
        cJSON *monsters = read_array(room_obj, "monsters");
        int monstersCount = cJSON_GetArraySize(monsters);
        for (int d = 0; d < monstersCount && d < MAX_MONSTER_COUNT; d++) {
            room->monsters[d] = read_array_item_string(monsters, d);
            if (room->monsters[d] == NULL) {
                break;
            }
        }

        room->hasMonster = (monstersCount > 0);

        // Set defaults for fields not in JSON
        room->secretPassage = read_int(room_obj, "secret_passage");
        room->monsterDefeated = false;
        room->secretPassageRevealed = false;

        // Parse exits object
        cJSON *exits_obj = cJSON_GetObjectItemCaseSensitive(room_obj, "exits");
        if (exits_obj && cJSON_IsObject(exits_obj)) {
            room->exits[NORTH] = parse_exit(exits_obj, "north");
            room->exits[EAST] = parse_exit(exits_obj, "east");
            room->exits[SOUTH] = parse_exit(exits_obj, "south");
            room->exits[WEST] = parse_exit(exits_obj, "west");
        } else {
            // If no exits object, set all to NONE
            room->exits[NORTH] = NONE;
            room->exits[EAST] = NONE;
            room->exits[SOUTH] = NONE;
            room->exits[WEST] = NONE;
        }

        // loot is not in JSON; leave as default (uninitialized)
    }

    reset();
    *roomCountOut = roomCount;
}
