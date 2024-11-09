#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <string.h>
#include "maze.h"
#include "leaderboard.h"
#include "display.h"

int main(void) {
    init_curses();

    display_main_menu();

    destroy_curses();

    return EXIT_SUCCESS;
}
