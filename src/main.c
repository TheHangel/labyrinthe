#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "maze.h"

void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

direction get_direction_from_input(char key) {
    switch (key) {
        case 'z':
        case 'Z':
            return UP;
        case 's':
        case 'S':
            return DOWN;
        case 'q':
        case 'Q':
            return LEFT;
        case 'd':
        case 'D':
            return RIGHT;
        default:
            return INVALID;
    }
}

int main(void) {
    initscr();
    noecho();
    cbreak();

    srand(time(NULL));
    int l = 9;
    int w = 17;
    maze *m = new_maze(l, w);
    if (m == NULL) return EXIT_FAILURE;

    generate_maze(m);

    while(1) {
        clear();
        display(*m);
        refresh();
        printw("Direction (z/q/s/d): ");
        char c = getch();
        direction d = get_direction_from_input(c);

        if (d != INVALID) {
            move_player(m, d);
        }

        refresh();
    }

    endwin();
    destroy_maze(m);
    return 0;
}
