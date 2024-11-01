#include <stdio.h>
#include <string.h>
#include "inventory.h"

#define MAX_ITEMS 10
static char inventory[MAX_ITEMS][50];
static int itemCount = 0;

void addItem(const char* item) {
    if (itemCount < MAX_ITEMS) {
        snprintf(inventory[itemCount], 50, "%s", item);
        itemCount++;
        printf("Item %s added to inventory.\n", item);
    } else {
        printf("Inventory is full!\n");
    }
}

void useItem(const char* item) {
    for (int i = 0; i < itemCount; i++) {
        if (strcmp(inventory[i], item) == 0) {
            printf("Using item %s.\n", item);
            // Implement item effect
            return;
        }
    }
    printf("Item %s not found in inventory.\n", item);
}
