#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Include for atoi function

#include "game.h"
#include "utils.h"
#include "character/character.h"
#include "combat/combat.h"
#include "map/room.h"
RoomStack roomHistory;

_Bool setup_game(char *roomsFile) {
    int roomCount = 0;
    load_rooms_from_file(roomsFile, &roomCount);
    if (roomCount == 0) {
        printf("No rooms found\n");
        return false;
    }
    printf("loaded rooms from %s", roomsFile);
    return true;
}

void initialize_game() {
    printf("\n---------------------------------------------\n");
    printf("\n\n  Welcome to The Temple of the Fallen King!\n\n"); // spaces for centering
    printf("\n---------------------------------------------\n");
    sleep_ms(1500);
    printf("\nAvailable commands:\n");
    printf("  help - Display this help message.\n");
    printf("  exit - Exit the game.\n");
    printf("Room-specific actions are available as numbered options.\n");
    printf("\n------------------------------------------\n\n");
    createCharacter();
}

_Bool check_exit_confirmation(char command[50]) {
    fancy_print("Are you sure you want to exit? [y/n]\n");
    get_input("%s", command);
    if (command[0] == 'y') {
        return 1;
    }
    return 0;
}

// Display room-specific options dynamically based on room state
int display_room_options(Room *room, RoomStack *roomHistory) {
    int optionCount = 1;
    printf("\n--- Room Options ---\n");

    // Add "Return to previous room" option only if not in Room 0
    _Bool roomHasAnyExit = room->exits[NORTH] != NONE
                           || room->exits[EAST] != NONE
                           || room->exits[SOUTH] != NONE
                           || room->exits[WEST] != NONE;
    if (
        roomHasAnyExit &&
        !isEmpty(roomHistory)
    ) {
        fancy_print("%d) Return to previous room\n", optionCount++);
    }

    // Add "Look around" option
    fancy_print("%d) Look around\n", optionCount++);

    // Add "Fight monster" option if there is a monster in the room
    if (room->hasMonster && !room->monsterDefeated) {
        fancy_print("%d) Fight monster\n", optionCount++);
    }

    // Display valid exits for the room
    if (room->exits[NORTH] != NONE) {
        fancy_print("%d) Exit north\n", optionCount++);
    }
    if (room->exits[EAST] != NONE) {
        fancy_print("%d) Exit east\n", optionCount++);
    }
    if (room->exits[SOUTH] != NONE) {
        fancy_print("%d) Exit south\n", optionCount++);
    }
    if (room->exits[WEST] != NONE) {
        fancy_print("%d) Exit west\n", optionCount++);
    }

    // Add secret passage option if revealed
    if (room->secretPassageRevealed) {
        fancy_print("%d) Use secret passage\n", optionCount++);
    }

    return optionCount - 1; // Return the total number of options displayed
}

// Display room description
void display_room_description(Room *room) {
    printf("\n------------------------------------------\n");
    int descriptionCount = sizeof(room->description) / sizeof(room->description[0]);
    for (int i = 0; i < descriptionCount; i++) {
        if (room->description[i] != NULL) {
            fancy_print("%s\n", room->description[i]);
        } else {
            break;
        }
    }
    printf("------------------------------------------\n\n");
}

// Display look-around text
void display_look_around_text(Room *room) {
    fancy_print("\n...You look around...\n\n");
    int lookAroundTextCount = sizeof(room->lookAroundText) / sizeof(room->lookAroundText[0]);
    for (int i = 0; i < lookAroundTextCount; i++) {
        if (room->lookAroundText[i] != NULL) {
            fancy_print("%s\n", room->lookAroundText[i]);
        } else {
            break;
        }
    }
}

void look_around(Room *room) {
    display_look_around_text(room);
    if (room->hasSecretPassage && !room->secretPassageRevealed) {
        fancy_print("\nYou discover a hidden passage!\n\n");
        room->secretPassageRevealed = true;
    }
}

bool fight_monster(const Room *room) {
    _Bool gameOver = false;

    if (!room->hasMonster) {
        return gameOver;
    }
    _Bool foughtFinalBoss = false;
    int monsterCount = sizeof(room->monsters) / sizeof(room->monsters[0]);
    for (int i = 0; i < monsterCount; i++) {
        if (room->monsters[i] != NULL) {
            Character monster;
            if (equals(room->monsters[i], "Skeleton King")) {
                monster = getKingSkeleton();
                foughtFinalBoss = true;
            } else if (equals(room->monsters[i], "Skeleton")) {
                monster = getSkeleton();
            } else if (equals(room->monsters[i], "Slime")) {
                monster = getSlime();
            } else {
                monster = getSlime();
            }
            _Bool defeatedEnemy = combat(&monster); // Handle combat
            if (!defeatedEnemy) {
                gameOver = true;
                return gameOver;
            }
        }
    }

    // End the game if in Room 10 and the monster is defeated
    if (foughtFinalBoss) {
        fancy_print("You are finally released from the shackles of the Temple of the Forgotten King.\n\n");
        gameOver = true;
    }
    return gameOver;
}

void run_game() {
    int currentRoomID = 1; // Start in Room 0 (Tutorial)

    initStack(&roomHistory); // Initialize the stack

    Room *room = get_room(currentRoomID);
    char command[50];
    int choice;
    int lastOptionIndex;
    _Bool displayRoomDescriptionFlag = true; // Flag to control room description display

    while (1) {
        // Display room description only when entering a room
        if (displayRoomDescriptionFlag) {
            display_room_description(room);
            displayRoomDescriptionFlag = false;
        }

        // Display room-specific options and get the count of options available
        lastOptionIndex = display_room_options(room, &roomHistory);

        // Get input from the player
        printf("\nEnter a command or option number: ");
        get_input("%s", command);
        to_lower_string(command);

        // Process global commands
        if (equals(command, "help")) {
            fancy_print("Available commands:\n");
            fancy_print("  help - Display this help message.\n");
            fancy_print("  exit - Exit the game.\n");
            fancy_print("Room-specific actions are available as numbered options.\n\n");
            continue;
        } else if (equals(command, "exit")) {
            if (check_exit_confirmation(command)) {
                break;
            }
            continue;
        }

        // Convert command to an integer for room-specific options
        choice = atoi(command);

        if (choice < 1 || choice > lastOptionIndex) {
            fancy_print("Invalid option. Please try again.\n\n");
            continue;
        }

        // Handle room-specific actions based on the chosen option
        int optionIndex = 1;

        // Option 1: Return to previous room
        if (currentRoomID != 0 && currentRoomID != 10 && !isEmpty(&roomHistory) && choice == optionIndex++) {
            int previousRoom = pop(&roomHistory); // Get the previous room from the stack
            if (previousRoom != -1) {
                fancy_print("Returning to the previous room...\n\n");
                currentRoomID = previousRoom;
                room = get_room(currentRoomID);
                displayRoomDescriptionFlag = true; // Set flag to display description for the new room
            } else {
                fancy_print("No previous room to return to!\n\n");
            }
        }
        // Option 2: Look around
        else if (choice == optionIndex++) {
            look_around(room);
        }
        // Option 3: Fight monster (if present)
        else if (room->hasMonster && !room->monsterDefeated && choice == optionIndex++) {
            _Bool gameOver = fight_monster(room);
            if (gameOver) break;
            room->monsterDefeated = true;
        }
        // Handle exits based on room-specific configuration
        else if (room->exits[NORTH] != NONE && choice == optionIndex++) {
            fancy_print("You sneak through the north exit.\n");
            push(&roomHistory, currentRoomID); // Push current room onto stack
            currentRoomID = room->exits[NORTH];
            room = get_room(currentRoomID);
            displayRoomDescriptionFlag = true; // Set flag to display description for the new room
        } else if (room->exits[EAST] != NONE && choice == optionIndex++) {
            fancy_print("You sneak through the east exit.\n");
            push(&roomHistory, currentRoomID); // Push current room onto stack
            currentRoomID = room->exits[EAST];
            room = get_room(currentRoomID);
            displayRoomDescriptionFlag = true;
        } else if (room->exits[SOUTH] != NONE && choice == optionIndex++) {
            fancy_print("You sneak through the south exit.\n");
            push(&roomHistory, currentRoomID); // Push current room onto stack
            currentRoomID = room->exits[SOUTH];
            room = get_room(currentRoomID);
            displayRoomDescriptionFlag = true;
        } else if (room->exits[WEST] != NONE && choice == optionIndex++) {
            fancy_print("You sneak through the west exit.\n");
            push(&roomHistory, currentRoomID); // Push current room onto stack
            currentRoomID = room->exits[WEST];
            room = get_room(currentRoomID);
            displayRoomDescriptionFlag = true;
        }
        // Secret passage if revealed
        else if (room->secretPassageRevealed && choice == optionIndex) {
            fancy_print("You enter the secret passage.\n");
            push(&roomHistory, currentRoomID); // Push current room onto stack
            currentRoomID = 5; // Connect all secret passages to Room 5
            room = get_room(currentRoomID);
            displayRoomDescriptionFlag = true;
        } else {
            fancy_print("Invalid option. Please try again.\n\n");
        }
    }

    fancy_print("Thank you for playing!");
    sleep_ms(5000);
}

void move_to_room(Room *currentRoom) {
    push(&roomHistory, currentRoom->id); // Push current room onto stack
}
