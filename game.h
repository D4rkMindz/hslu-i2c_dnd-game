#ifndef GAME_H
#define GAME_H

_Bool setup_game(char *roomsFile);

void initialize_game();

void run_game(char *highscoreFile);

typedef struct {
    int returnToPrevious;
    int fightMonsters;
    int lookAround;
    int moveNorth;
    int moveEast;
    int moveSouth;
    int moveWest;
    int moveThroughSecretPassage;
}Command;

#endif
