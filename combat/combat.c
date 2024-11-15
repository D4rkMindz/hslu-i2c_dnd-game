#include <stdio.h>
#include <stdlib.h>
#include "combat.h"
#include "../character/character.h"
// Curently holding off including the facy print I want to ask Björn how it works fully before using.
// #include "../utils.h"

void startCombat(Character* enemy) {
    Character* player = getPlayerCharacter();

    printf("A %s appears!\n", enemy->name);

    //Holds the various variables for the comabt encounter
    srand(time(NULL));
    int randomValue = 0;
    //This is so we don't override every enemy (of that types) health
    int enemyHealth = enemy->health;
    int action = 0;
    int playerFumble = 0;
    int enemyFumble = 0;
    int playerDefense = player->defense;
    int enemyDefense = enemy->defense;
    int playerDoubleDamage = player->attackPower * 2;
    int playerAdvantageDoubleDamage = playerDoubleDamage * 2;
    int enemyDoubleDamage = enemy->attackPower * 2;
    int enemyAdvantageDoubleDamage = enemyDoubleDamage * 2;

    while (player->health > 0 && enemyHealth > 0) {
        action = 0;

        printf("Choose your action: (1) Attack (2) Defend: ");
        scanf("%d", &action);
        while(action != 1 && action != 2){
            printf("\n");
            printf("That is not a valid input, please try again.\n");
            printf("Choose your action: (1) Attack (2) Defend: ");
            scanf("%d", &action);
            printf("\n");
        }

        //If player chooses to attack
        if (action == 1) {
            //Rolls their attack
            randomValue = ((rand() % 20) + 1);
            //If the enemys last attack was a 1 and the player rolls a 20 the enemy takes 4* the normal damage
            if (randomValue >= enemyDefense && randomValue == 20 && enemyFumble == 1) {
                printf("You struck a weak point of the %s while it was off balance and your %s delt %d damage!\n", enemy->name, player->main_weapon, playerAdvantageDoubleDamage);
                    enemyHealth -= playerAdvantageDoubleDamage;

            //If the enemy last attack was a 1 and the player rolls high enough to hit the target takes 2* the damage
            }else if (randomValue >= enemyDefense && enemyFumble == 1) {
                printf("You struck a weak point of the %s while it was off balance and your %s delt %d damage!\n", enemy->name, player->main_weapon, playerAdvantageDoubleDamage);
                    enemyHealth -= playerDoubleDamage;
            
            //The player rolls higher than the enemys AC
            }else if (randomValue >= enemyDefense) {
                //If player rolls 20 applies 2* the damage
                if(randomValue == 20){
                    printf("You struck a weak point of the %s and your %s delt %d damage!\n", enemy->name, player->main_weapon, playerDoubleDamage);
                    enemyHealth -= playerDoubleDamage;

                //If the player rolls a 1 the enemy has advantage on their next attack and the players defences is lowered for 1 round
                } else if(randomValue == 1){
                    printf("You critically missed the %s and left yourself open to attack!\n", enemy->name);
                    playerFumble = 1;
                    playerDefense -= 5;

                //If the player rolls high enough it applies the characters base damage
                } else{
                    printf("You attacked the %s successfully and your %s delt %d damage!\n", enemy->name, player->main_weapon, player->attackPower);
                    enemyHealth -= player->attackPower;
                }
            //If the player doesn't roll high enough to hit the enemy
            } else {
                printf("Your attack missed the %s!\n", enemy->name);
            }
        // If the player choses defense it improves the players AC for 1 round
        } else if (action == 2) {
            printf("You fortified yourself against the %s's next attack.\n", enemy->name);
            playerDefense += 5;
        }
        
        // Resets the enemys disadvantages before their next turn
        enemyDefense = enemy->defense;
        enemyFumble = 0;
        
        if (enemyHealth > 0) {
            //Rolls their attack
            randomValue = ((rand() % 20) + 1);
            //If the players last attack was a 1 and the enemy rolls a 20 the player takes 4* the normal damage
            if (randomValue >= playerDefense && randomValue == 20 && playerFumble == 1) {
                printf("The %s struck a weak point while you were off balance and its %s delt %d damage!\n", enemy->name, enemy->main_weapon, playerAdvantageDoubleDamage);
                    player->health -= enemyAdvantageDoubleDamage;
            
            //If the players last attack was a 1 and the enemy rolls high enough to hit the player takes 2* the damage
            }else if (randomValue >= playerDefense && playerFumble == 1) {
                printf("The %s struck your weak point while you were off balance and its %s delt %d damage!\n", enemy->name, enemy->main_weapon, enemyDoubleDamage);
                    player->health -= enemyDoubleDamage;
            
            //The enemy rolls higher than the enemys AC
            }else if (randomValue >= playerDefense) {
                //If enemy rolls 20 applies 2* the damage
                if(randomValue == 20){
                    printf("The %s struck your weak point and its %s delt %d damage!\n", enemy->name, enemy->main_weapon, enemyDoubleDamage);
                    player->health -= enemyDoubleDamage;
                
                //If the enemy rolls a 1 the player has advantage on their next attack and the enemys defences is lowered for 1 round
                } else if(randomValue == 1){
                    printf("The %s critically missed you and left itself open to attack!\n", enemy->name);
                    enemyFumble = 1;
                    enemyDefense -= 5;
                
                //If the player rolls high enough it applies the characters base damage
                } else{
                    printf("The %s successfully hit you with its %s delt %d damage!\n", enemy->name, enemy->main_weapon, enemy->attackPower);
                    player->health -= enemy->attackPower;
                }
            //If the enemy doesn't roll high enough to hit the player
            } else {
                printf("The %s attack missed you!\n", enemy->name);
            }
        }
        // Resets the players disadvantages before their next turn
        playerDefense = player->defense;
        playerFumble = 0;
    }

    if (player->health > 0) {
        printf("You defeated the enemy!\n");
        printf("As you slay the %s you feel yourself revitalized with the life essance of the creature!\n", enemy->name);
        printf("You gain %d hit points!\n\n", enemy->healthReturn);
        //Adds the health returned by killing the enemy type however if the added health is greater than max it is reset to the maximum
        player->health += enemy->healthReturn;
        if(player->health > CHARACTER_HEALTH){
            player->health = CHARACTER_HEALTH;
        }
        //When defeating the enemy it adds how valuable that enemy was (used for the highscore aspect)
        player->pointValue += enemy->pointValue;
    } else {
        printf("You have been defeated!\n");
    }
}
