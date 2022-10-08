#ifndef GAME_H
#define GAME_H

#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include "frog.h"
#include "car.h"
#include "config.h"
#include "utils.h"

typedef struct _Game {
    Frog *frog;
    Car **cars;

    int lifes;
    int score;

    int clock;

} Game;

Game *new_game(int lifes);
void update_frame(Game *game);
void init_borders();
int has_collision(Game *game);
void clearup();
void move_game(Game *game);
void draw_game(Game *game);

#endif