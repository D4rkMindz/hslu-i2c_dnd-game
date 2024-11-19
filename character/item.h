#ifndef ITEM_H
#define ITEM_H
#include "character.h"

#define SMALL = 10;
#define MEDIUM = 20;
#define LARGE = 30;

typedef enum {
    POTION_SMALL = 10,
    POTION_MEDIUM = 30,
    POTION_LARGE = 50,
} PotionSize;

typedef struct {
    PotionSize size;
    char *name;
    signed int buff;
} Potion;

void consumePotion(Character *character, Potion item);

Potion createPotion(char *name, PotionSize size);
#endif //ITEM_H
