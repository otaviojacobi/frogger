#ifndef CAR_H
#define CAR_H

#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "utils.h"
#include "config.h"

#define CAR_SPEC_LEFT " __/=|_ \n/_o__o_\\"
#define CAR_SPEC_RIGHT " _|=\\__ \n/_o__o_\\"

typedef struct _Car {
    Moveable* moveable;
    int speed;
    int direction_x;
    char* spec;
} Car;

Car *new_car(int pos_x, int pos_y, int speed);
void draw_car(Car *car);
void move_car(Car *car, int tick);
Car** generate_cars();

#endif
