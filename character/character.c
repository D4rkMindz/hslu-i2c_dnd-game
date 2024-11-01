#include <stdio.h>
#include "character.h"
#include "../utils.h"

#include <string.h>

Character getEnemy(char name[MAX_NAME_LEN], int health, int attackPower, int defense);

static Character player;

void createCharacter() {
    char class[10];
    printf("Select your characters class [mage,wizard]:");
    scanf("%s", class);
    printf("Enter your character's name: ");
    scanf("%s", player.name);
    int health = 100;
    int attackPower = 10;
    int defense = 5;
    if (equals(class, "mage")) {
        health = 200;
        attackPower = 20;
        defense = 5;
    }
    if (equals(class, "wizard")) {
        health = 100;
        attackPower = 50;
        defense = 20;
    }
    player.health = health;
    player.attackPower = attackPower;
    player.defense = defense;
    printf("Character %s created with %d health.\n", player.name, player.health);
}

Character getSlime() {
    return getEnemy("Slime", 10, 5, 10);
}

Character getSkeleton() {
    return getEnemy("Skeleton", 50, 10, 30);
}

Character getKingSkeleton() {
    return getEnemy("Skeleton King", 150, 50, 50);
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
