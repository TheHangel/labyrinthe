#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "maze.h"

#define ESCAPE_KEY 27
#define ENTER_KEY 10

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

void wait_to_press_enter() {
    printw("Press enter...");
    char c = 0;
    do {
        c = getch();
    }
    while(c != ENTER_KEY);
}

int main(void) {
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);

    timeout(100);

    srand(time(NULL));
    int l = 11;
    int w = 25;
    maze *m = new_maze(l, w);
    if (m == NULL) return EXIT_FAILURE;

    generate_maze(m);

    int player_exited = 0;

    while(1) {
        clear();
        display(*m);
        refresh();

        if(is_player_at_exit(*m)) {
            player_exited++;
            break;
        }

        char c = getch();

        if (c == ESCAPE_KEY) {
            break;
        }

        direction d = get_direction_from_input(c);

        if (d != INVALID) {
            move_player(m, d);
        }

        refresh();
    }

    if(player_exited) {
        printw("YOU WIN!\n");
        wait_to_press_enter();
    }

    endwin();
    destroy_maze(m);
    return EXIT_SUCCESS;
}
