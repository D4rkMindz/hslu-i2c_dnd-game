#include <stdio.h>

#include "game.h"
#include "utils.h"

#include "character/character.h"
#include "combat/combat.h"
#include "map/map.h"

void initializeGame() {
    printf("Welcome to The Temple of the Fallen King!\n");
    createCharacter();
    initializeMap();
}

_Bool check_exit_confirmation(char command[50]) {
    printf("Are you sure you want to exit? [y/N]\n");
    scanf("%s", command);
    if (command[0] == 'y') {
        return 1;
    }
    return 0;
}

void startGame() {
    char command[50];
    // Game loop to explore the map and interact with enemies, NPCs, and items
    while (1) {
        printf("\nEnter a command: ");
        scanf("%s", command);
        to_lower_string(command);
        // Process command
        // available: help, exit, todo
        if (equals(command, "help")) {
            printf("HELP\n");
            // TODO
        } else if (equals(command, "move")) {
            printf("MOVE\n");
            // TODO
        } else if (equals(command, "combat")) {
            Character slime = getSlime();
            startCombat(&slime);
        } else if (equals(command, "exit")) {
            if (check_exit_confirmation(command)) break;
        } else {
            printf("Invalid Command\n");
        }
    }

    printf("Thank you for playing");
}
