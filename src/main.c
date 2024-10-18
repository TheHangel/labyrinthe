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
    int l = 5;
    int w = 7;
    maze *m = new_maze(l, w);
    if (m == NULL) return EXIT_FAILURE;

    generate_maze(m);

    while(1) {
        clear();
        display_debug(*m);
        show_player(*(m->player));
        refresh();

        char c = getch();
        direction d = get_direction_from_input(c);

        if (d != INVALID) {
            move_player(m, d);
        }

        if(is_player_at_exit(*m)) {
            printw("YOU WIN!");
            getch();
            break;
        }

        refresh();
    }

    endwin();
    destroy_maze(m);
    return 0;
}
