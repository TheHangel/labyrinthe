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
    //time_t seed = time(NULL);
    //srand(seed);
    //int l = 17;
    //int w = 35;
    //maze *m = load_maze_from_file("data/maze.cfg");
    //if (m == NULL) return EXIT_FAILURE;

    //display_game(m);

    display_main_menu();

    //destroy_maze(m);
    destroy_curses();

    return EXIT_SUCCESS;
}
