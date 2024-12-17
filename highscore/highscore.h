#ifndef HIGHSCORE_H
#define HIGHSCORE_H

void handle_highscore(int highscore, char *highscoreFile);

typedef struct {
    int score;
    char *playerName;
} Score;

#endif //HIGHSCORE_H
