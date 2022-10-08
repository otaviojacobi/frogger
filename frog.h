#ifndef FROG_H
#define FROG_H

#include <stdlib.h>
#include <ctype.h>
#include "utils.h"
#include "config.h"

#define FROG_SPEC "@@\n||"; 

typedef struct _Frog {
    Moveable* moveable;
    char* spec;
} Frog;

Frog *new_frog(int pos_x, int pos_y);
void draw_frog(Frog *frog);
void move_frog(Frog *frog);

#endif
