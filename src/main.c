#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "maze.h"

int main(void) {
    init_labyrinthe();
    time_t seed = time(NULL);
    srand(seed);
    int l = 17;
    int w = 35;
    maze *m = new_maze(l, w);
    if (m == NULL) return exit_labyrinthe(EXIT_FAILURE);

    generate_maze(m);

    while(1) {
        clear();
        printw("Seed: %ld\n", seed);
        display(m);
        refresh();

        if(check_player_pos(m)) break;

        char c = getch();

        if (c == ESCAPE_KEY) {
            break;
        }

        direction d = get_direction_from_input(c);

        if (d != INVALID) {
            move_player(m, d);
        }
    }

    if(m->player->exited) {
        printw("YOU WIN!\n");
        wait_to_press_enter();
    }

    return exit_labyrinthe(EXIT_SUCCESS);
}
