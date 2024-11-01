#ifndef CHARACTER_H
#define CHARACTER_H
#include "../constants.h"

typedef struct {
    char name[MAX_NAME_LEN];
    int health;
    int attackPower;
    int defense;
} Character;

void createCharacter();
Character* getPlayerCharacter();
Character getSlime();
Character getSkeleton();
Character getKingSkeleton();

#endif
