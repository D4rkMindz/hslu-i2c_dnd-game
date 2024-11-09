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
    printf("Are you sure you want to exit? [y/N]\n");
    scanf("%s", command);
    if (command[0] == 'y')
    {
        return 1;
    }
    return 0;
}

// Display room-specific options dynamically based on room state
int displayRoomOptions(Room *room)
{
    int optionCount = 1;
    printf("\n\n--- Room Options ---\n\n");
    printf("%d) Return to previous room\n", optionCount++); // Option 1

    printf("%d) Look around\n", optionCount++); // Option 2

    if (room->hasMonster && !room->monsterDefeated)
    {
        printf("%d) Fight monster\n", optionCount++); // Option 3 - if a monster is present
    }

    // Display exit options dynamically based on available exits in each direction
    if (room->exits[NORTH] != NONE)
    {
        printf("%d) Exit north\n", optionCount++);
    }
    if (room->exits[EAST] != NONE)
    {
        printf("%d) Exit east\n", optionCount++);
    }
    if (room->exits[SOUTH] != NONE)
    {
        printf("%d) Exit south\n", optionCount++);
    }
    if (room->exits[WEST] != NONE)
    {
        printf("%d) Exit west\n", optionCount++);
    }

    // Option for secret passage if revealed
    if (room->secretPassageRevealed)
    {
        printf("%d) Use secret passage\n\n", optionCount++);
    }

    return optionCount - 1; // Return the total number of options displayed
}

// display room description
void displayRoomDescription(Room *room)
{
    printf("\n--- Room Description ---\n");
    for (int i = 0; i < room->descriptionLineCount; i++)
    {
        printf("%s\n", room->description[i]);
    }
    printf("\n------------------------------------------\n");
}

// display look-around text
void displayLookAroundText(Room *room)
{
    printf("\n--- Look Around ---\n");
    for (int i = 0; i < room->lookAroundLineCount; i++)
    {
        printf("%s\n", room->lookAroundText[i]);
    }
    printf("\n------------------------------------------\n");
}

void startGame()
{
    Room **allRooms = initializeMap(); // Initialize rooms using initializeMap
    int currentRoom = 0;               // Start in Room 0 (Tutorial)
    Room *room = getRoom(currentRoom);
    char command[50];
    int choice;
    int lastOptionIndex;

    while (1)
    {
        // Display room description upon entry
        displayRoomDescription(room);

        // Display room-specific options and get the count of options available
        lastOptionIndex = displayRoomOptions(room);

        // Get input from the player
        printf("\n\n\nEnter a command or option number: ");
        scanf("%s", command);
        to_lower_string(command);

        // Process global commands
        if (equals(command, "help"))
        {
            printf("Available commands:\n");
            printf("  help - Display this help message.\n");
            printf("  exit - Exit the game.\n");
            printf("Room-specific actions are available as numbered options.\n");
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
                printf("\nInvalid option. Type 'help' for a list of available commands.\n\n\n");
                continue;
            }

            // Handle room-specific actions based on the chosen option
            int optionIndex = 1;

            // Option 1: Return to previous room
            if (choice == optionIndex++)
            {
                printf("Returning to the previous room...\n");
                currentRoom--; // Adjust for the temple structure if needed
                room = getRoom(currentRoom);
            }
            // Option 2: Look around
            else if (choice == optionIndex++)
            {
                displayLookAroundText(room);
                if (room->hasSecretPassage && !room->secretPassageRevealed)
                {
                    printf("You discover a hidden passage!\n\n");
                    room->secretPassageRevealed = true;
                }
            }
            // Option 3: Fight monster (if present)
            else if (room->hasMonster && !room->monsterDefeated && choice == optionIndex++)
            {
                Character slime = getSlime(); // Example monster, adjust as needed
                startCombat(&slime);          // Adjust for specific combat function
                room->monsterDefeated = true;
                printf("The monster has been defeated!\n\n");
            }
            // Handle exits based on room-specific configuration
            else if (room->exits[NORTH] != NONE && choice == optionIndex++)
            {
                printf("You exit north.\n\n");
                currentRoom = room->exits[NORTH];
                room = getRoom(currentRoom);
            }
            else if (room->exits[EAST] != NONE && choice == optionIndex++)
            {
                printf("You exit east.\n\n");
                currentRoom = room->exits[EAST];
                room = getRoom(currentRoom);
            }
            else if (room->exits[SOUTH] != NONE && choice == optionIndex++)
            {
                printf("You exit south.\n\n");
                currentRoom = room->exits[SOUTH];
                room = getRoom(currentRoom);
            }
            else if (room->exits[WEST] != NONE && choice == optionIndex++)
            {
                printf("You exit west.\n\n");
                currentRoom = room->exits[WEST];
                room = getRoom(currentRoom);
            }
            // Secret passage if revealed
            else if (room->secretPassageRevealed && choice == optionIndex++)
            {
                printf("You enter the secret passage.\n\n");
                currentRoom = room->exits[NORTH]; // Adjust for various passage directions if needed
                room = getRoom(currentRoom);
            }
            else
            {
                printf("Invalid option. Please try again.\n\n");
            }
        }
    }

    printf("Thank you for playing");
}
