#ifndef CHARACTER_H
#define CHARACTER_H
#include "../constants.h"

typedef enum { WIZARD, BARBARIAN } CharacterType;

typedef struct {
    char name[MAX_NAME_LEN];
    int health;
    int attackPower;
    int defense;
    char main_weapon[MAX_WEAPON_NAME_LEN];
    int healthReturn;
    int pointValue;
    CharacterType type;
} Character;

void createCharacter();

Character *getPlayerCharacter();

Character getSlime();

Character getSkeleton();

Character getKingSkeleton();

void addPoints(Character *character, signed int points);

void addHealth(Character *character, signed int health);

void addDamage(Character *character, signed int health);

_Bool isHealthy(Character *character);

#endif
