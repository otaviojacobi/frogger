#ifndef UTILS_H
#define UTILS_H

#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <curses.h>
#include "config.h"

#define MICROSECONDS_SECONDS 1000000
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

typedef struct _Moveable {
    int pos_y;
    int pos_x;
    int speed;
} Moveable;

void logmsg(char *msg);
long int delta(struct timeval* begin, struct timeval* end);
void draw(char *spec, Moveable *moveable);

#endif
