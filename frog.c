#include "frog.h"

Frog *new_frog(int pos_x, int pos_y) {
    Frog *frog = (Frog*)malloc(sizeof(Frog));
    Moveable *moveable = (Moveable*)malloc(sizeof(Moveable));

    moveable->pos_x = pos_x;
    moveable->pos_y = pos_y;

    frog->moveable = moveable;
    frog->spec = FROG_SPEC;

    return frog;
}

void draw_frog(Frog* frog) {
    draw(frog->spec, frog->moveable);
}

void move_frog(Frog *frog) {

    char move = tolower(getch());
    if(move == ERR) return;

    if (move == 'w') {
        frog->moveable->pos_y = MAX(frog->moveable->pos_y - 2, 0);
    } else if (move == 's') {
        frog->moveable->pos_y = MIN(frog->moveable->pos_y + 2, HEIGHT - 2);
    } else if (move == 'd') {
        frog->moveable->pos_x = MIN(frog->moveable->pos_x + 2, WIDTH - 2);
    } else if (move == 'a') {
        frog->moveable->pos_x = MAX(frog->moveable->pos_x - 2, 0);
    } 
}
