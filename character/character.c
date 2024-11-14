#include <stdio.h>
#include "character.h"
#include "../utils.h"

#include <string.h>

Character getEnemy(char name[MAX_NAME_LEN], int health, int attackPower, int defense);

static Character player;

void createCharacter() {
    char class[10];
    fancy_print("Select your characters class [mage,wizard]:");
    scanf("%s", class);
    fancy_print("Enter your character's name:");
    scanf("%s", player.name);
    int health = 100;
    int attackPower = 10;
    int defense = 5;
    if (equals(class, "barbarian")) {
        health = CHARACTER_HEALTH;
        attackPower = BARBARIAN_ATTACK;
        defense = BARBARIAN_DEFENSE;
    }
    if (equals(class, "wizard")) {
        health = CHARACTER_HEALTH;
        attackPower = WIZARD_ATTACK;
        defense = WIZARD_DEFENSE;
    }
    player.health = health;
    player.attackPower = attackPower;
    player.defense = defense;
    printf("Character %s created with %d health.\n", player.name, player.health);
}

Character getSlime() {
    return getEnemy("Slime", SLIME_HEALTH, SLIME_ATTACK, SLIME_DEFENSE);
}

Character getSkeleton() {
    return getEnemy("Skeleton", SKELETON_HEALTH, SKELETON_ATTACK, SKELETON_DEFENSE);
}

Character getKingSkeleton() {
    return getEnemy("Skeleton King", ENDBOSS_HEALTH, ENDBOSS_ATTACK, ENDBOSS_DEFENSE);
}

Character *getPlayerCharacter() {
    return &player;
}

Character getEnemy(char name[MAX_NAME_LEN], const int health, const int attackPower, const int defense) {
    Character enemy;
    strcpy(enemy.name, name);
    enemy.health = health;
    enemy.attackPower = attackPower;
    enemy.defense = defense;

    return enemy;
}
