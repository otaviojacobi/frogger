#include <time.h>
#include <stdlib.h>
#include "utils.h"
#include "frog.h"
#include "car.h"
#include "game.h"

#define NONE 0
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

void init();
void update_frame(Game *game);


void init() {
    initscr();  // initialize curses, this also "clears" the screen
    cbreak();   // among other things, disable buffering
    noecho();   // disable "echo" of characters from input
    nodelay(stdscr, TRUE);
    curs_set(0);
    srand(3);

}

int main() {

    init();
    Game *game = new_game(3) ;

    while(1) update_frame(game);
}


