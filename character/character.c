#include <stdio.h>
#include "character.h"
#include "../utils.h"

#include <string.h>

Character getEnemy(char name[MAX_NAME_LEN], int health, int attackPower, int defense, char main_weapon[MAX_WEAPON_NAME_LEN], int healthReturn, int pointValue);

static Character player;

void createCharacter() {
    char class[10];
    fancy_print("Select your characters class [barbarian,wizard]:");
    scanf("%s", class);
    fancy_print("Enter your character's name:");
    scanf("%s", player.name);
    int health = 100;
    int attackPower = 10;
    int defense = 5;
    int healthReturn = CHARACTER_HEALTH_RETURN;
    int pointValue = CHARACTER_POINT_VALUE;
    
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
    player.healthReturn = healthReturn;
    player.pointValue = pointValue;
    printf("Character %s created with %d health.\n", player.name, player.health);
}

Character getSlime() {
    return getEnemy("Slime", SLIME_HEALTH, SLIME_ATTACK, SLIME_DEFENSE, SLIME_WEAPON, SLIME_HEALTH_RETURN, SLIME_POINT_VALUE);
}

Character getSkeleton() {
    return getEnemy("Skeleton", SKELETON_HEALTH, SKELETON_ATTACK, SKELETON_DEFENSE, SKELETON_WEAPON, SKELETON_HEALTH_RETURN, SKELETON_POINT_VALUE);
}

Character getKingSkeleton() {
    return getEnemy("Skeleton King", ENDBOSS_HEALTH, ENDBOSS_ATTACK, ENDBOSS_DEFENSE, ENDBOSS_WEAPON, ENDBOSS_HEALTH_RETURN, ENDBOSS_POINT_VALUE);
}

Character *getPlayerCharacter() {
    return &player;
}

Character getEnemy(char name[MAX_NAME_LEN], const int health, const int attackPower, const int defense, char main_weapon[MAX_WEAPON_NAME_LEN], const int healthReturn, const int pointValue) {
    Character enemy;
    strcpy(enemy.name, name);
    enemy.health = health;
    enemy.attackPower = attackPower;
    enemy.defense = defense;
    strcpy(enemy.main_weapon, main_weapon[]);
    enemy.healthReturn = healthReturn;
    enemy.pointValue = pointValue;
    
    return enemy;
}
