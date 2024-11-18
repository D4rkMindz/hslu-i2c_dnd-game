#include <stdio.h>
#include "character.h"
#include <ctype.h>
#include "../utils.h"
#include <string.h>

Character getEnemy(
    char name[MAX_NAME_LEN],
    int health,
    int attackPower,
    int defense,
    char main_weapon[MAX_WEAPON_NAME_LEN],
    int healthReturn,
    int pointValue
);

static Character player;

void createCharacter() {
    char class[10];
    while (!equals(class, "barbarian") && !equals(class, "wizard")) {
        fancy_print("Select your characters class [barbarian,wizard]:");
        scanf("%s", class);
    }
    fancy_print("Enter your character's name:");
    scanf("%s", player.name);
    int health = CHARACTER_HEALTH;
    int attackPower = BARBARIAN_ATTACK;
    int defense = BARBARIAN_DEFENSE;
    char playerWeapon[25];

    if (equals(class, "barbarian")) {
        health = CHARACTER_HEALTH;
        attackPower = BARBARIAN_ATTACK;
        defense = BARBARIAN_DEFENSE;
        strcpy(playerWeapon, BARBARIAN_WEAPON);
    }
    if (equals(class, "wizard")) {
        health = CHARACTER_HEALTH;
        attackPower = WIZARD_ATTACK;
        defense = WIZARD_DEFENSE;
        strcpy(playerWeapon, WIZARD_WEAPON);
    }
    player.health = health;
    player.attackPower = attackPower;
    player.defense = defense;
    strcpy(player.main_weapon, playerWeapon);
    player.healthReturn = CHARACTER_HEALTH_RETURN;
    player.pointValue = CHARACTER_POINT_VALUE;
    fancy_print("Character %s created with %d health.\n", player.name, player.health);
}

Character getSlime() {
    return getEnemy(
        "Slime",
        SLIME_HEALTH,
        SLIME_ATTACK,
        SLIME_DEFENSE,
        SLIME_WEAPON,
        SLIME_HEALTH_RETURN,
        SLIME_POINT_VALUE
    );
}

Character getSkeleton() {
    return getEnemy(
        "Skeleton",
        SKELETON_HEALTH,
        SKELETON_ATTACK,
        SKELETON_DEFENSE,
        SKELETON_WEAPON,
        SKELETON_HEALTH_RETURN,
        SKELETON_POINT_VALUE
    );
}

Character getKingSkeleton() {
    return getEnemy(
        "Skeleton King",
        ENDBOSS_HEALTH,
        ENDBOSS_ATTACK,
        ENDBOSS_DEFENSE,
        ENDBOSS_WEAPON,
        ENDBOSS_HEALTH_RETURN,
        ENDBOSS_POINT_VALUE
    );
}

Character *getPlayerCharacter() {
    return &player;
}

Character getEnemy(
    char name[MAX_NAME_LEN],
    const int health,
    const int attackPower,
    const int defense,
    char main_weapon[MAX_WEAPON_NAME_LEN],
    const int healthReturn,
    const int pointValue
) {
    Character enemy;
    strcpy(enemy.name, name);
    enemy.health = health;
    enemy.attackPower = attackPower;
    enemy.defense = defense;
    strcpy(enemy.main_weapon, main_weapon);
    enemy.healthReturn = healthReturn;
    enemy.pointValue = pointValue;

    return enemy;
}
