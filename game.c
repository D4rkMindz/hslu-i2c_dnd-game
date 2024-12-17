#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Include for atoi function

#include "game.h"
#include "utils.h"
#include "character/character.h"
#include "combat/combat.h"
#include "map/file_parsing.h"
#include "map/room.h"
#include "highscore/highscore.h"
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
Command display_available_commands(const Room *room, RoomStack *roomHistory) {
    Command commands = {-1, -1, -1, -1, -1, -1, -1, -1};
    int optionCount = 1;
    printf("\n--- Room Options ---\n");

    // Add "Return to previous room" option only if not in Room 0
    _Bool roomHasAnyExit = room->exits[NORTH] != NONE
                           || room->exits[EAST] != NONE
                           || room->exits[SOUTH] != NONE
                           || room->exits[WEST] != NONE;
    // Option 1: return to previous room
    if (roomHasAnyExit && !isEmpty(roomHistory)) {
        commands.returnToPrevious = optionCount;
        fancy_print("%d) Return to previous room\n", optionCount++);
    }

    // Option 2: Add "Fight monster" option if there is a monster in the room
    if (room->hasMonster && !room->monsterDefeated) {
        commands.fightMonsters = optionCount;
        fancy_print("%d) Fight monster\n", optionCount);

        return commands;
    }

    // Option 3: Add "Look around" option
    commands.lookAround = optionCount;
    fancy_print("%d) Look around\n", optionCount++);

    // Option 4: Display valid exits for the room
    if (room->exits[NORTH] != NONE) {
        commands.moveNorth = optionCount;
        fancy_print("%d) Exit north\n", optionCount++);
    }
    if (room->exits[EAST] != NONE) {
        commands.moveEast = optionCount;
        fancy_print("%d) Exit east\n", optionCount++);
    }
    if (room->exits[SOUTH] != NONE) {
        commands.moveSouth = optionCount;
        fancy_print("%d) Exit south\n", optionCount++);
    }
    if (room->exits[WEST] != NONE) {
        commands.moveWest = optionCount;
        fancy_print("%d) Exit west\n", optionCount++);
    }

    // Option 5: Add secret passage option if revealed
    if (room->secretPassageRevealed) {
        commands.moveThroughSecretPassage = optionCount;
        fancy_print("%d) Use secret passage\n", optionCount);
    }

    return commands;
}

// Display room description
void display_room_description(Room *room) {
    printf("\n------------------------------------------\n");
    if (DEBUG) {
        printf("DEBUG: room id=%i name=%s\n", room->id, room->name);
    }
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

Room *move_to_room(Room *currentRoom, Direction direction) {
    char *directionalWord = "your chosen"; // fallback that still would make sense
    if (direction == NORTH) {
        directionalWord = "north";
    } else if (direction == EAST) {
        directionalWord = "east";
    } else if (direction == SOUTH) {
        directionalWord = "south";
    } else if (direction == WEST) {
        directionalWord = "west";
    }
    fancy_print("You sneak through the %s exit.\n", directionalWord);
    push(&roomHistory, currentRoom->id); // Push current room onto stack
    int roomID = currentRoom->exits[direction];
    if (roomID == NONE) {
        pop(&roomHistory);
        return currentRoom;
    }

    Room *room = get_room(roomID);

    if (!room) {
        return currentRoom;
    }

    return room;
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
    if (room->secretPassage > 0 && !room->secretPassageRevealed) {
        fancy_print("\nYou discover a hidden passage!\n\n");
        room->secretPassageRevealed = true;
    }
}

_Bool fight_monster(const Room *room, int *highscore) {
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
            (*highscore) += monster.pointValue;
        }
    }

    // End the game if in Room 10 and the monster is defeated
    if (foughtFinalBoss) {
        fancy_print("You are finally released from the shackles of the Temple of the Forgotten King.\n\n");
        gameOver = true;
    }
    return gameOver;
}

char *getCommand(Command commands, const int command) {
    if (commands.returnToPrevious == command) {
        return "returnToPrevious";
    }
    if (commands.fightMonsters == command) {
        return "fightMonsters";
    }
    if (commands.lookAround == command) {
        return "lookAround";
    }
    if (commands.moveNorth == command) {
        return "moveNorth";
    }
    if (commands.moveEast == command) {
        return "moveEast";
    }
    if (commands.moveSouth == command) {
        return "moveSouth";
    }
    if (commands.moveWest == command) {
        return "moveWest";
    }
    if (commands.moveThroughSecretPassage == command) {
        return "moveThroughSecretPassage";
    }
    return "invalidCommand";
}

void run_game(char *highscoreFile) {
    int highscore = 0;
    int currentRoomID = 1; // Start in Room 0 (Tutorial)

    initStack(&roomHistory); // Initialize the stack

    Room *room = get_room(currentRoomID);
    _Bool displayRoomDescriptionFlag = true; // Flag to control room description display

    while (1) {
        char command[50];
        // Display room description only when entering a room
        if (displayRoomDescriptionFlag) {
            display_room_description(room);
            displayRoomDescriptionFlag = false;
        }

        // Display room-specific options and get the count of options available
        Command commands = display_available_commands(room, &roomHistory);

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
        }
        if (equals(command, "exit")) {
            if (check_exit_confirmation(command)) {
                break;
            }
            continue;
        }

        // Convert command to an integer for room-specific options
        int choice = atoi(command);

        if (choice <= 0 || choice >= 10) {
            fancy_print("Invalid option. Please try again.\n\n");
            continue;
        }

        // Option 1: Return to previous room
        if (commands.returnToPrevious == choice) {
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
        // Option 2: Fight monster (if present)
        if (commands.fightMonsters == choice) {
            _Bool gameOver = fight_monster(room, &highscore);
            if (gameOver) break;
            room->monsterDefeated = true;
        }
        // Option 2: Look around
        if (commands.lookAround == choice) {
            look_around(room);
        }
        // Handle exits based on room-specific configuration
        if (commands.moveNorth == choice) {
            room = move_to_room(room, NORTH);
            displayRoomDescriptionFlag = true; // Set flag to display description for the new room
        }
        if (commands.moveEast == choice) {
            room = move_to_room(room, EAST);
            displayRoomDescriptionFlag = true;
        }
        if (commands.moveSouth == choice) {
            room = move_to_room(room, SOUTH);
            displayRoomDescriptionFlag = true;
        }
        if (commands.moveWest == choice) {
            room = move_to_room(room, WEST);
            displayRoomDescriptionFlag = true;
        }
        // Secret passage if revealed
        if (commands.moveThroughSecretPassage == choice) {
            fancy_print("You enter the secret passage.\n");
            push(&roomHistory, currentRoomID); // Push current room onto stack
            currentRoomID = room->secretPassage; // Connect all secret passages to Room 5
            room = get_room(currentRoomID); // this room MIGHT be empty, accept it for now
            displayRoomDescriptionFlag = true;
        }
    }

    fancy_print("\nThank you for playing!\n");

    handle_highscore(highscore, highscoreFile);

    sleep_ms(5000);
}
