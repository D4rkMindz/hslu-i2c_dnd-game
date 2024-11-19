#include "item.h"
#include "character.h"

void consumePotion(Character *character, const Potion potion) {
    character->health += potion.buff;
}

Potion createPotion(char *name, PotionSize potionSize) {
    Potion potion = {potionSize, name, potionSize};
    return potion;
}
