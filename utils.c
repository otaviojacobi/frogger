#include "utils.h"

void logmsg(char *msg) {
    FILE *out_file = fopen("leivas.log", "a");
    fprintf(out_file, "%s", msg);
    fclose(out_file);
}

long int delta(struct timeval* begin, struct timeval* end){
    long int begin_sec = begin->tv_sec;
    long int begin_usec = begin->tv_usec;

    long int end_sec = end->tv_sec;
    long int end_usec = end->tv_usec;

    return ((end_sec - begin_sec) * MICROSECONDS_SECONDS) + end_usec - begin_usec;
}

void draw(char *spec, Moveable *moveable) {
    int x_delta = 0;
    int y_delta = 0;

    for(int i = 0; i < strlen(spec); i++) {
        if(spec[i] == '\n') {
            y_delta += 1;
            x_delta = 0;

        } else {
            int pos_y = moveable->pos_y + y_delta + 1;
            int pos_x = ((moveable->pos_x + x_delta) % WIDTH) + 1;
            
            mvaddch(pos_y, pos_x, spec[i]);
            x_delta += 1;
        }
    }
}