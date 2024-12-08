#include <stdio.h>
#include <stdlib.h>
#include "combat.h"
#include <time.h>

#include "../utils.h"
#include "../character/character.h"

void startCombat(Character *enemy)
{
    Character *player = getPlayerCharacter();

    fancy_print("\nA %s appears!\n", enemy->name);

    srand(time(NULL));
    int randomValue = 0;
    signed int action = 0;
    int playerFumble = 0;
    int enemyFumble = 0;
    int playerDefense = player->defense;
    int enemyDefense = enemy->defense;
    int playerDoubleDamage = player->attackPower * 2;
    int playerAdvantageDoubleDamage = playerDoubleDamage * 2;
    int enemyDoubleDamage = enemy->attackPower * 2;
    int enemyAdvantageDoubleDamage = enemyDoubleDamage * 2;

    while (isHealthy(player) && isHealthy(enemy))
    {
        action = 0;

        while (action != 1 && action != 2)
        {
            if (action >= 2)
            {
                fancy_print("That is not a valid input, please try again.\n");
            }
            fancy_print("Choose your action: (1) Attack (2) Defend: ");
            get_input("%d", &action);

            if (action == 0)
            {
                action = 99;
            }
            printf("\n");
        }

        if (action == 1)
        { // Attack
            randomValue = ((rand() % 20) + 1);

            if (randomValue >= enemyDefense && randomValue == 20 && enemyFumble == 1)
            {
                fancy_print(
                    "You struck a weak point of the %s while it was off balance and your %s dealt %d damage!\n",
                    enemy->name,
                    player->main_weapon,
                    playerAdvantageDoubleDamage);
                addDamage(enemy, playerAdvantageDoubleDamage);
            }
            else if (randomValue >= enemyDefense && enemyFumble == 1)
            {
                fancy_print(
                    "You struck a weak point of the %s while it was off balance and your %s dealt %d damage!\n",
                    enemy->name,
                    player->main_weapon,
                    playerDoubleDamage);
                addDamage(enemy, playerDoubleDamage);
            }
            else if (randomValue >= enemyDefense)
            {
                if (randomValue == 20)
                {
                    fancy_print(
                        "You struck a weak point of the %s and your %s dealt %d damage!\n",
                        enemy->name,
                        player->main_weapon,
                        playerDoubleDamage);
                    addDamage(enemy, playerDoubleDamage);
                }
                else if (randomValue == 1)
                {
                    fancy_print("You critically missed the %s and left yourself open to attack!\n", enemy->name);
                    playerFumble = 1;
                    playerDefense -= 5;
                }
                else
                {
                    fancy_print(
                        "You attacked the %s successfully and your %s dealt %d damage!\n",
                        enemy->name,
                        player->main_weapon,
                        player->attackPower);
                    addDamage(enemy, player->attackPower);
                }
            }
            else
            {
                fancy_print("Your attack missed the %s!\n", enemy->name);
            }
        }
        else if (action == 2)
        { // Defend
            fancy_print("You fortified yourself against the %s's next attack.\n", enemy->name);
            playerDefense += 5;
        }

        enemyDefense = enemy->defense;
        enemyFumble = 0;

        if (isHealthy(enemy))
        {
            randomValue = ((rand() % 20) + 1);

            if (randomValue >= playerDefense && randomValue == 20 && playerFumble == 1)
            {
                fancy_print(
                    "The %s struck a weak point while you were off balance and its %s dealt %d damage!\n",
                    enemy->name,
                    enemy->main_weapon,
                    enemyAdvantageDoubleDamage);
                addDamage(player, enemyAdvantageDoubleDamage);
            }
            else if (randomValue >= playerDefense && playerFumble == 1)
            {
                fancy_print(
                    "The %s struck your weak point while you were off balance and its %s dealt %d damage!\n",
                    enemy->name,
                    enemy->main_weapon,
                    enemyDoubleDamage);
                addDamage(player, enemyDoubleDamage);
            }
            else if (randomValue >= playerDefense)
            {
                if (randomValue == 20)
                {
                    fancy_print(
                        "The %s struck your weak point and its %s dealt %d damage!\n",
                        enemy->name,
                        enemy->main_weapon,
                        enemyDoubleDamage);
                    addDamage(player, enemyDoubleDamage);
                }
                else if (randomValue == 1)
                {
                    fancy_print("The %s critically missed you and left itself open to attack!\n", enemy->name);
                    enemyFumble = 1;
                    enemyDefense -= 5;
                }
                else
                {
                    fancy_print(
                        "The %s successfully hit you with its %s and dealt %d damage!\n",
                        enemy->name,
                        enemy->main_weapon,
                        enemy->attackPower);
                    addDamage(player, enemy->attackPower);
                }
            }
            else
            {
                fancy_print("The %s attack missed you!\n", enemy->name);
            }
        }

        playerDefense = player->defense;
        playerFumble = 0;

        // Display current health points for both player and enemy
        fancy_print("\n--- Current Health Points ---\n");
        fancy_print("Your Health: %d HP\n", player->health);
        fancy_print("Enemy's Health (%s): %d HP\n", enemy->name, enemy->health);
        fancy_print("----------------------\n\n");
    }

    if (isHealthy(player))
    {
        fancy_print("\nYou defeated the enemy!\n");
        fancy_print("As you slay the %s, you feel revitalized!\n", enemy->name);
        fancy_print("You regain %d Health Points!\n", enemy->healthReturn);
        addHealth(player, enemy->healthReturn);
        addPoints(player, enemy->pointValue);
    }
    else
    {
        fancy_print("\nYou have been defeated!\n");
        fancy_print("\nYour vision goes dark...\n");
    }
}
