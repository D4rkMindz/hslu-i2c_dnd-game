#include <stdio.h>

#include "game.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    char *roomsFile = NULL;
    // char *highscoreFile = NULL;
    // argc - 1 to ensure that no argv overflow is created
    for (int i = 1; i < argc - 1; i++) {
        if (equals(argv[i], "--rooms") || equals(argv[i], "-r")) {
            roomsFile = argv[i + 1];
        }
        // if (equals(argv[i], "--highscore") || equals(argv[i], "-h")) {
        //     highscoreFile = argv[i + 1];
        // }
    }
    // if (highscoreFile == NULL) {
    //     highscoreFile = "highscores.json";
    //     printf("No high scores file defined. Using default!\n");
    // }
    if (roomsFile == NULL) {
        printf("You must provide a room file name using --rooms or -r\n");
        return 80;
    }
    if (!setup_game(roomsFile)) {
        return 99;
    }
    initialize_game();
    run_game();
    return 0;
}
