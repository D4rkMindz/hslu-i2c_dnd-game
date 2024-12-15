#include <stdio.h>

#include "game.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    char *roomsFile = NULL;
    // argc - 1 to ensure that no argv overflow is created
    for (int i = 1; i < argc - 1; i++) {
        if (equals(argv[i], "--json") || equals(argv[i], "-j")) {
            roomsFile = argv[i + 1];
        }
    }
    if (roomsFile == NULL) {
        printf("You must provide a room file name using --json or -j\n");
        return 80;
    }
    if (!setup_game(roomsFile)) {
        return 99;
    }
    initialize_game();
    run_game();
    return 0;
}
