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
    printf("Welcome to The Temple of the Fallen King!\n");
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
    printf("--- Room Options ---\n");

    // Only display "Return to Previous Room" if not in Room 0 or Room 10 and history exists
    if (currentRoom != 0 && currentRoom != 10 && !isEmpty(roomHistory))
    {
        fancy_print("%d) Return to previous room\n", optionCount++); // Option 1
    }

    fancy_print("%d) Look around\n", optionCount++); // Option 2

    if (room->hasMonster && !room->monsterDefeated)
    {
        fancy_print("%d) Fight monster\n", optionCount++); // Option 3 - if a monster is present
    }

    // Display exit options dynamically based on available exits in each direction
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

    // Option for secret passage if revealed
    if (room->secretPassageRevealed)
    {
        fancy_print("%d) Use secret passage\n", optionCount++);
    }

    return optionCount - 1; // Return the total number of options displayed
}

// display room description
void displayRoomDescription(Room *room)
{
    printf("\n------------------------------------------\n");
    for (int i = 0; i < room->descriptionLineCount; i++)
    {
        fancy_print("%s\n", room->description[i]);
    }
    printf("------------------------------------------\n");
}

// display look-around text
void displayLookAroundText(Room *room)
{
    fancy_print("\n...You look around...\n");
    for (int i = 0; i < room->lookAroundLineCount; i++)
    {
        fancy_print("%s\n", room->lookAroundText[i]);
    }
}

void startGame()
{
    Room **allRooms = initializeMap(); // Initialize rooms
    int currentRoom = 0;               // Start in Room 0
    RoomStack roomHistory;
    initStack(&roomHistory); // Initialize the stack

    Room *room = getRoom(currentRoom);
    char command[50];
    int choice;
    int lastOptionIndex;

    while (1)
    {
        // Display room description upon entry
        displayRoomDescription(room);

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
            fancy_print("Room-specific actions are available as numbered options.\n");
        }
        else if (equals(command, "exit"))
        {
            if (check_exit_confirmation(command))
            {
                break;
            }
        }
        else
        {
            // Convert command to an integer for room-specific options
            choice = atoi(command);

            if (choice < 1 || choice > lastOptionIndex)
            {
                fancy_print("Invalid option. Type 'help' for a list of available commands.\n");
                continue;
            }

            int optionIndex = 1;

            // Option 1: Return to previous room
            if (currentRoom != 0 && currentRoom != 10 && choice == optionIndex++)
            {
                int previousRoom = pop(&roomHistory); // Get the previous room from the stack
                if (previousRoom != -1)
                {
                    fancy_print("Returning to the previous room...\n");
                    currentRoom = previousRoom;
                    room = getRoom(currentRoom);
                }
                else
                {
                    fancy_print("No previous room to return to!\n");
                }
            }
            // Option 2: Look around
            else if (choice == optionIndex++)
            {
                displayLookAroundText(room);
                if (room->hasSecretPassage && !room->secretPassageRevealed)
                {
                    fancy_print("You discover a hidden passage!\n\n");
                    room->secretPassageRevealed = true;
                }
            }
            // Option 3: Fight monster (if present)
            else if (room->hasMonster && !room->monsterDefeated && choice == optionIndex++)
            {
                Character slime = getSlime(); // Example monster
                startCombat(&slime);          // Handle combat
                room->monsterDefeated = true;
                fancy_print("The monster has been defeated!\n\n");
            }
            // Handle exits based on room-specific configuration
            else if (room->exits[NORTH] != NONE && choice == optionIndex++)
            {
                fancy_print("You exit north.\n");
                push(&roomHistory, currentRoom); // Push current room onto stack
                currentRoom = room->exits[NORTH];
                room = getRoom(currentRoom);
            }
            else if (room->exits[EAST] != NONE && choice == optionIndex++)
            {
                fancy_print("You exit east.\n");
                push(&roomHistory, currentRoom); // Push current room onto stack
                currentRoom = room->exits[EAST];
                room = getRoom(currentRoom);
            }
            else if (room->exits[SOUTH] != NONE && choice == optionIndex++)
            {
                fancy_print("You exit south.\n");
                push(&roomHistory, currentRoom); // Push current room onto stack
                currentRoom = room->exits[SOUTH];
                room = getRoom(currentRoom);
            }
            else if (room->exits[WEST] != NONE && choice == optionIndex++)
            {
                fancy_print("You exit west.\n");
                push(&roomHistory, currentRoom); // Push current room onto stack
                currentRoom = room->exits[WEST];
                room = getRoom(currentRoom);
            }
            // Secret passage if revealed
            else if (room->secretPassageRevealed && choice == optionIndex++)
            {
                fancy_print("You enter the secret passage.\n");
                push(&roomHistory, currentRoom);  // Push current room onto stack
                currentRoom = room->exits[NORTH]; // Adjust for direction
                room = getRoom(currentRoom);
            }
            else
            {
                fancy_print("Invalid option. Please try again.\n");
            }
        }
    }

    fancy_print("Thank you for playing");
}
