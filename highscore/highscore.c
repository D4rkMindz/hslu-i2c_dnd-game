#include <stdio.h>
#include <stdlib.h>

#include "highscore.h"
#include "../lib/cJSON.h"
#include "../utils.h"
#include "../map/file_parsing.h"
#include "../character/character.h"

void updateHighScore(Character *player) {
    FILE *file;
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

        fancy_print("Congratulations you've reached a new High Score: %d\n", highScore);

        // Shows the current high score
    } else {
        fancy_print("High Score remains: %d\n", highScore);
        fancy_print("Your Current Score: %d\n", player->pointValue);
    }
}

void save_highscore(int highscore, char *highscoreFile) {
    Character *player = getPlayerCharacter();

    cJSON *root = read_file_json(highscoreFile);
    cJSON *highscores;
    if (root == NULL) {
        root = cJSON_CreateObject();
        highscores = cJSON_AddArrayToObject(root, "highscores");
    } else {
        highscores = cJSON_GetObjectItem(root, "highscores");
    }

    char *type = player->type == WIZARD ? "wizard" : "barbarian";
    cJSON *currentScore = cJSON_CreateObject();
    cJSON_AddNumberToObject(currentScore, "score", highscore);
    cJSON_AddStringToObject(currentScore, "player", player->name);
    cJSON_AddStringToObject(currentScore, "type", type);
    cJSON_AddNumberToObject(currentScore, "date", (double) _microtime());
    cJSON_AddItemToArray(highscores, currentScore);

    write_file_json(highscoreFile, root);
}

int sortByScore(const void *a, const void *b) {
    return ((Score *) b)->score - ((Score *) a)->score;
}

void handle_highscore(int highscore, char *highscoreFile) {
    Character *player = getPlayerCharacter();
    fancy_print("Your player %s reached a score of %d\n", player->name, highscore);
    // save and then reload highscores to include the current users score
    save_highscore(highscore, highscoreFile);

    cJSON *root = read_file_json(highscoreFile);
    cJSON *highscores;
    if (root == NULL) {
        root = cJSON_CreateObject();
        highscores = cJSON_AddArrayToObject(root, "highscores");
    } else {
        highscores = cJSON_GetObjectItem(root, "highscores");
    }
    int scoreCount = cJSON_GetArraySize(highscores);
    Score *scores = calloc(scoreCount, sizeof(Score));
    for (int i = 0; i < scoreCount; i++) {
        cJSON *scoreData = cJSON_GetArrayItem(highscores, i);
        if (scoreData == NULL) {
            continue;
        };
        Score score = {
            read_int(scoreData, "score"),
            read_string(scoreData, "player")
        };
        scores[i] = score;
    }
    qsort(scores, scoreCount, sizeof(Score), sortByScore);


    int limit = scoreCount < 3 ? scoreCount : 3;
    fancy_print("High score list:\n");
    for (int i = 0; i < limit; i++) {
        fancy_print("%i Score: %d by %s\n", i + 1, scores[i].score, scores[i].playerName);
    }

    for (int i = 0; i < scoreCount; i++) {
        free(scores[i].playerName);
    }
    free(scores);
}
