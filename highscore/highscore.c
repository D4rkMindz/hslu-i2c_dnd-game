#include <stdio.h>
#include <stdlib.h>
#include "../character/character.h"

void updateHighScore(Character* player) {
    FILE* file;
    int highScore = 0;

    // Open the file for reading
    file = fopen("highscore.txt", "r");
    if (file != NULL) {
        // Read the high score from the file
        fscanf(file, "%d", &highScore);
        fclose(file);
    }
    // Shows the new high score
    if (player->pointValue > highScore) {
        // Open the file for writing and update the high score
        file = fopen("highscore.txt", "w");
        if (file == NULL) {
            perror("Error opening file for writing");
            return;
        }
        fprintf(file, "%d", player->pointValue);
        fclose(file);

        printf("Congratulations you've reached a new High Score: %d\n", highScore);
    
    // Shows the current high score
    } else {
        printf("High Score remains: %d\n", highScore);
        printf("Your Current Score: %d\n", player->pointValue);
    }
}
