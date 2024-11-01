#include <stdio.h>
#include "combat.h"
#include "../character/character.h"

void startCombat(Character* enemy) {
    Character* player = getPlayerCharacter();
    int enemyHealth = 50;

    printf("A %s appears!\n", enemy->name);

    while (player->health > 0 && enemyHealth > 0) {
        printf("Choose your action: (1) Attack (2) Defend: ");
        int action;
        scanf("%d", &action);

        if (action == 1) {
            printf("You attack the enemy!\n");
            enemyHealth -= 10;
        } else if (action == 2) {
            printf("You defend yourself.\n");
            player->defense += 5;
        }

        if (enemyHealth > 0) {
            printf("Enemy attacks you!\n");
            player->health -= 5;
        }
    }

    if (player->health > 0) {
        printf("You defeated the enemy!\n");
    } else {
        printf("You have been defeated!\n");
    }
}
