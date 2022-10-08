#include "game.h"

char line_full[(WIDTH+3) * (HEIGHT+2) + 1];

void draw_borders() {
    printw("%s", line_full);
}

Game *new_game(int lifes) {
    init_borders();

    line_full[(WIDTH+3) * (HEIGHT+2)] = '\0';

    Game *game = (Game *)malloc(sizeof(Game));

    Frog *frog = new_frog(WIDTH/2, HEIGHT-2);
    game->frog = frog;

    game->cars = generate_cars();

    game->score = 0;
    game->lifes = lifes;

    return game;
}

void reset(Game *game) {
    game->lifes-=1;

    if(game->lifes <= 0) {
        exit(0);
    }

    game->frog->moveable->pos_x = WIDTH/2;
    game->frog->moveable->pos_y = HEIGHT-2;
}

void init_borders() {
    int index = 0;
    for(int y = 0; y < HEIGHT + 2; y++) {
        for(int x = 0; x < WIDTH + 3; x++) {

            if(x == (WIDTH + 2)) {
                line_full[index] = '\n';
            } else if((y == 0 || x == 0 || x == WIDTH + 1 || y == HEIGHT + 1) ) {
                line_full[index] = '#';
            } else {
                line_full[index] = ' ';
            }
            index++;
        }
    }
}

void clearup() {
    erase();
    draw_borders();
}

int has_collision(Game *game) {
    int frog_x = game->frog->moveable->pos_x + 1;
    int frog_y = game->frog->moveable->pos_y + 1;

    int top_left = mvinch(frog_y, frog_x);
    int top_right = mvinch(frog_y, frog_x+1);
    int bottom_left = mvinch(frog_y+1, frog_x);
    int bottom_right = mvinch(frog_y+1, frog_x+1);


    if((top_left != ' ' && top_left != '@') ||
       (top_right != ' ' && top_right != '@') ||
       (bottom_left != ' ' && bottom_left != '|') ||
       (bottom_right != ' ' && bottom_right != '|' )) {
        return 1;
    }

    return 0;

}

void move_game(Game *game) {
    move_frog(game->frog);
    for(int i = 0; i < MAX_AMOUNT_CARS; i++) {
        if(game->cars[i] != NULL) {
            move_car(game->cars[i], game->clock);
        }
    }
    if(has_collision(game)) {
        reset(game);
    }
}

void draw_game(Game *game) {
    draw_frog(game->frog);
    for(int i = 0; i < MAX_AMOUNT_CARS; i++) {
        if(game->cars[i] != NULL) {
            draw_car(game->cars[i]);
        }
    }
}

void update_frame(Game *game) {
    struct timeval begin;
    struct timeval end;

    gettimeofday(&begin, NULL);
    move_game(game);
    clearup();
    draw_game(game);

    // Ensure FPS
    gettimeofday(&end, NULL);
    long int delay = MAX(MICROSECONDS_SECONDS/FPS - delta(&begin,&end), 0);
    usleep(delay);

    game->clock = (game->clock + 1) % FPS;
}

