#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Include for atoi function

#include "game.h"
#include "utils.h"
#include "character/character.h"
#include "combat/combat.h"
#include "map/map.h"

void initializeGame()
{
    printf("\n------------------------------------------\n");
    printf("\n\nWelcome to The Temple of the Fallen King!\n\n");
    printf("\n------------------------------------------\n");
    sleep_ms(1500);
    printf("\nAvailable commands:\n");
    printf("  help - Display this help message.\n");
    printf("  exit - Exit the game.\n");
    printf("Room-specific actions are available as numbered options.\n");
    printf("\n------------------------------------------\n\n");
    createCharacter();
    Room **allRooms = initializeMap();
}

_Bool check_exit_confirmation(char command[50])
{
    fancy_print("Are you sure you want to exit? [y/n]\n");
    get_input("%s", command);
    if (command[0] == 'y')
    {
        return 1;
    }
    return 0;
}

// Display room-specific options dynamically based on room state
int displayRoomOptions(Room *room, int currentRoom, RoomStack *roomHistory)
{
    int optionCount = 1;
    printf("\n--- Room Options ---\n");

    // Add "Return to previous room" option only if not in Room 0
    if (currentRoom != 0 && currentRoom != 10 && !isEmpty(roomHistory))
    {
        fancy_print("%d) Return to previous room\n", optionCount++);
    }

    // Add "Look around" option
    fancy_print("%d) Look around\n", optionCount++);

    // Add "Fight monster" option if there is a monster in the room
    if (room->hasMonster && !room->monsterDefeated)
    {
        fancy_print("%d) Fight monster\n", optionCount++);
    }

    // Display valid exits for the room
    if (room->exits[NORTH] != NONE)
    {
        fancy_print("%d) Exit north\n", optionCount++);
    }
    if (room->exits[EAST] != NONE)
    {
        fancy_print("%d) Exit east\n", optionCount++);
    }
    if (room->exits[SOUTH] != NONE)
    {
        fancy_print("%d) Exit south\n", optionCount++);
    }
    if (room->exits[WEST] != NONE)
    {
        fancy_print("%d) Exit west\n", optionCount++);
    }

    // Add secret passage option if revealed
    if (room->secretPassageRevealed)
    {
        fancy_print("%d) Use secret passage\n", optionCount++);
    }

    return optionCount - 1; // Return the total number of options displayed
}

// Display room description
void displayRoomDescription(Room *room)
{
    printf("\n------------------------------------------\n");
    for (int i = 0; i < room->descriptionLineCount; i++)
    {
        fancy_print("%s\n", room->description[i]);
    }
    printf("------------------------------------------\n\n");
}

// Display look-around text
void displayLookAroundText(Room *room)
{
    fancy_print("\n...You look around...\n\n");
    for (int i = 0; i < room->lookAroundLineCount; i++)
    {
        fancy_print("%s\n", room->lookAroundText[i]);
    }
}

void startGame()
{
    Room **allRooms = initializeMap(); // Initialize rooms using initializeMap
    int currentRoom = 0;               // Start in Room 0 (Tutorial)
    RoomStack roomHistory;
    initStack(&roomHistory); // Initialize the stack

    Room *room = getRoom(currentRoom);
    char command[50];
    int choice;
    int lastOptionIndex;
    _Bool displayRoomDescriptionFlag = true; // Flag to control room description display

    while (1)
    {
        // Display room description only when entering a room
        if (displayRoomDescriptionFlag)
        {
            displayRoomDescription(room);
            displayRoomDescriptionFlag = false;
        }

        // Display room-specific options and get the count of options available
        lastOptionIndex = displayRoomOptions(room, currentRoom, &roomHistory);

        // Get input from the player
        printf("\nEnter a command or option number: ");
        get_input("%s", command);
        to_lower_string(command);

        // Process global commands
        if (equals(command, "help"))
        {
            fancy_print("Available commands:\n");
            fancy_print("  help - Display this help message.\n");
            fancy_print("  exit - Exit the game.\n");
            fancy_print("Room-specific actions are available as numbered options.\n\n");
            continue;
        }
        else if (equals(command, "exit"))
        {
            if (check_exit_confirmation(command))
            {
                break;
            }
            continue;
        }

        // Convert command to an integer for room-specific options
        choice = atoi(command);

        if (choice < 1 || choice > lastOptionIndex)
        {
            fancy_print("Invalid option. Please try again.\n\n");
            continue;
        }

        // Handle room-specific actions based on the chosen option
        int optionIndex = 1;

        // Option 1: Return to previous room
        if (currentRoom != 0 && currentRoom != 10 && !isEmpty(&roomHistory) && choice == optionIndex++)
        {
            int previousRoom = pop(&roomHistory); // Get the previous room from the stack
            if (previousRoom != -1)
            {
                fancy_print("Returning to the previous room...\n\n");
                currentRoom = previousRoom;
                room = getRoom(currentRoom);
                displayRoomDescriptionFlag = true; // Set flag to display description for the new room
            }
            else
            {
                fancy_print("No previous room to return to!\n\n");
            }
        }
        // Option 2: Look around
        else if (choice == optionIndex++)
        {
            displayLookAroundText(room);
            if (room->hasSecretPassage && !room->secretPassageRevealed)
            {
                fancy_print("\nYou discover a hidden passage!\n\n");
                room->secretPassageRevealed = true;
            }
        }
        // Option 3: Fight monster (if present)
        else if (room->hasMonster && !room->monsterDefeated && choice == optionIndex++)
        {
            Character monster;

            // Assign appropriate monster based on the room
            if (currentRoom == 2)
            {
                monster = getSlime();
            }
            else if (currentRoom == 4 || currentRoom == 6)
            {
                monster = getSkeleton();
            }
            else if (currentRoom == 10)
            {
                monster = getKingSkeleton();
            }

            startCombat(&monster); // Handle combat

            // End the game if in Room 10 and the monster is defeated
            if (currentRoom == 10)
            {
                fancy_print("You are finally released from the shackles of the Temple of the Forgotten King.\n\n");
                break;
            }
        }
        // Handle exits based on room-specific configuration
        else if (room->exits[NORTH] != NONE && choice == optionIndex++)
        {
            fancy_print("You sneak through the north exit.\n");
            push(&roomHistory, currentRoom); // Push current room onto stack
            currentRoom = room->exits[NORTH];
            room = getRoom(currentRoom);
            displayRoomDescriptionFlag = true; // Set flag to display description for the new room
        }
        else if (room->exits[EAST] != NONE && choice == optionIndex++)
        {
            fancy_print("You sneak through the east exit.\n");
            push(&roomHistory, currentRoom); // Push current room onto stack
            currentRoom = room->exits[EAST];
            room = getRoom(currentRoom);
            displayRoomDescriptionFlag = true;
        }
        else if (room->exits[SOUTH] != NONE && choice == optionIndex++)
        {
            fancy_print("You sneak through the south exit.\n");
            push(&roomHistory, currentRoom); // Push current room onto stack
            currentRoom = room->exits[SOUTH];
            room = getRoom(currentRoom);
            displayRoomDescriptionFlag = true;
        }
        else if (room->exits[WEST] != NONE && choice == optionIndex++)
        {
            fancy_print("You sneak through the west exit.\n");
            push(&roomHistory, currentRoom); // Push current room onto stack
            currentRoom = room->exits[WEST];
            room = getRoom(currentRoom);
            displayRoomDescriptionFlag = true;
        }
        // Secret passage if revealed
        else if (room->secretPassageRevealed && choice == optionIndex++)
        {
            fancy_print("You enter the secret passage.\n");
            push(&roomHistory, currentRoom); // Push current room onto stack
            currentRoom = 5;                 // Connect all secret passages to Room 5
            room = getRoom(currentRoom);
            displayRoomDescriptionFlag = true;
        }
        else
        {
            fancy_print("Invalid option. Please try again.\n\n");
        }
    }

    fancy_print("Thank you for playing!");
    sleep_ms(5000);
}