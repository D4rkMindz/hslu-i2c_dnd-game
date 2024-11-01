#include <stdio.h>
#include "map.h"

void initializeMap() {
    printf("You are standing at the entrance of the temple.\n");
}

void navigateMap(const char* direction) {
    printf("You move %s.\n", direction);
    // Update player position and describe the new room
}
