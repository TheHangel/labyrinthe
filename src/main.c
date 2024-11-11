#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <string.h>
#include "maze.h"
#include "leaderboard.h"
#include "display.h"

int height = 0;
int width  = 0;

int main(void) {
    init_curses();

    display_main_menu();

    endwin();

    return EXIT_SUCCESS;
}
