#include <stdio.h>
#include <stdlib.h>
#include "combat.h"
#include <time.h>

#include "../utils.h"
#include "../character/character.h"
// Curently holding off including the facy print I want to ask Björn how it works fully before using.

void startCombat(Character *enemy) {
    Character *player = getPlayerCharacter();

    fancy_print("A %s appears!\n", enemy->name);

    //Holds the various variables for the comabt encounter
    srand(time(NULL));
    int randomValue = 0;
    //This is so we don't override every enemy (of that types) health
    int action = 0;
    int playerFumble = 0;
    int enemyFumble = 0;
    int playerDefense = player->defense;
    int enemyDefense = enemy->defense;
    int playerDoubleDamage = player->attackPower * 2;
    int playerAdvantageDoubleDamage = playerDoubleDamage * 2;
    int enemyDoubleDamage = enemy->attackPower * 2;
    int enemyAdvantageDoubleDamage = enemyDoubleDamage * 2;

    while (isHealthy(player) && isHealthy(enemy)) {
        action = 0;

        fancy_print("Choose your action: (1) Attack (2) Defend: ");
        get_input("%d", &action);
        while (action != 1 && action != 2) {
            fancy_print("That is not a valid input, please try again.\n");
            fancy_print("Choose your action: (1) Attack (2) Defend: ");
            get_input("%d", &action);
            printf("\n");
        }

        //If player chooses to attack
        if (action == 1) {
            //Rolls their attack
            randomValue = ((rand() % 20) + 1);
            //If the enemys last attack was a 1 and the player rolls a 20 the enemy takes 4* the normal damage
            if (randomValue >= enemyDefense && randomValue == 20 && enemyFumble == 1) {
                fancy_print(
                    "You struck a weak point of the %s while it was off balance and your %s delt %d damage!\n",
                    enemy->name,
                    player->main_weapon,
                    playerAdvantageDoubleDamage
                );
                addDamage(enemy, playerAdvantageDoubleDamage);

                //If the enemy last attack was a 1 and the player rolls high enough to hit the target takes 2* the damage
            } else if (randomValue >= enemyDefense && enemyFumble == 1) {
                fancy_print(
                    "You struck a weak point of the %s while it was off balance and your %s delt %d damage!\n",
                    enemy->name,
                    player->main_weapon,
                    playerAdvantageDoubleDamage
                );
                addDamage(enemy, playerDoubleDamage);

                //The player rolls higher than the enemys AC
            } else if (randomValue >= enemyDefense) {
                //If player rolls 20 applies 2* the damage
                if (randomValue == 20) {
                    fancy_print(
                        "You struck a weak point of the %s and your %s delt %d damage!\n",
                        enemy->name,
                        player->main_weapon,
                        playerDoubleDamage
                    );
                    addDamage(enemy, playerDoubleDamage);

                    //If the player rolls a 1 the enemy has advantage on their next attack and the players defences is lowered for 1 round
                } else if (randomValue == 1) {
                    fancy_print("You critically missed the %s and left yourself open to attack!\n", enemy->name);
                    playerFumble = 1;
                    playerDefense -= 5;

                    //If the player rolls high enough it applies the characters base damage
                } else {
                    fancy_print(
                        "You attacked the %s successfully and your %s delt %d damage!\n",
                        enemy->name,
                        player->main_weapon,
                        player->attackPower
                    );
                    addDamage(enemy, player->attackPower);
                }
                //If the player doesn't roll high enough to hit the enemy
            } else {
                fancy_print("Your attack missed the %s!\n", enemy->name);
            }
            // If the player choses defense it improves the players AC for 1 round
        } else if (action == 2) {
            fancy_print("You fortified yourself against the %s's next attack.\n", enemy->name);
            playerDefense += 5;
        }

        // Resets the enemys disadvantages before their next turn
        enemyDefense = enemy->defense;
        enemyFumble = 0;

        if (isHealthy(enemy)) {
            //Rolls their attack
            randomValue = ((rand() % 20) + 1);
            //If the players last attack was a 1 and the enemy rolls a 20 the player takes 4* the normal damage
            if (randomValue >= playerDefense && randomValue == 20 && playerFumble == 1) {
                fancy_print(
                    "The %s struck a weak point while you were off balance and its %s delt %d damage!\n",
                    enemy->name,
                    enemy->main_weapon,
                    playerAdvantageDoubleDamage
                );
                addDamage(player, enemyAdvantageDoubleDamage);

                //If the players last attack was a 1 and the enemy rolls high enough to hit the player takes 2* the damage
            } else if (randomValue >= playerDefense && playerFumble == 1) {
                fancy_print(
                    "The %s struck your weak point while you were off balance and its %s delt %d damage!\n",
                    enemy->name,
                    enemy->main_weapon,
                    enemyDoubleDamage
                );
                addDamage(player, enemyDoubleDamage);

                //The enemy rolls higher than the enemys AC
            } else if (randomValue >= playerDefense) {
                //If enemy rolls 20 applies 2* the damage
                if (randomValue == 20) {
                    fancy_print(
                        "The %s struck your weak point and its %s delt %d damage!\n",
                        enemy->name,
                        enemy->main_weapon,
                        enemyDoubleDamage
                    );
                    addDamage(player, enemyDoubleDamage);

                    //If the enemy rolls a 1 the player has advantage on their next attack and the enemys defences is lowered for 1 round
                } else if (randomValue == 1) {
                    fancy_print("The %s critically missed you and left itself open to attack!\n", enemy->name);
                    enemyFumble = 1;
                    enemyDefense -= 5;

                    //If the player rolls high enough it applies the characters base damage
                } else {
                    fancy_print(
                        "The %s successfully hit you with its %s delt %d damage!\n",
                        enemy->name,
                        enemy->main_weapon,
                        enemy->attackPower
                    );
                    addDamage(player, enemy->attackPower);
                }
                //If the enemy doesn't roll high enough to hit the player
            } else {
                fancy_print("The %s attack missed you!\n", enemy->name);
            }
        }
        // Resets the players disadvantages before their next turn
        playerDefense = player->defense;
        playerFumble = 0;
    }

    if (isHealthy(player)) {
        fancy_print("You defeated the enemy!\n");
        fancy_print(
            "As you slay the %s you feel yourself revitalized with the life essance of the creature!\n",
            enemy->name
        );
        fancy_print("You gain %d hit points!\n", enemy->healthReturn);
        //Adds the health returned by killing the enemy type however if the added health is greater than max it is reset to the maximum
        addHealth(player, enemy->healthReturn);
        //When defeating the enemy it adds how valuable that enemy was (used for the highscore aspect)
        addPoints(player, enemy->pointValue);
    } else {
        fancy_print("You have been defeated!\n");
    }
}
