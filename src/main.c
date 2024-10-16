#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
    srand(time(NULL));
    int l = 9;
    int w = 17;
    maze *m = new_maze(l, w);
    if(m == NULL) return EXIT_FAILURE;
    generate_maze(m);
    display(*m);
    while(1) {
        printf("direction:");
        char c = getchar();
        direction d = get_direction_from_input(c);
        printf("char: %c\n", c);
        printf("dir: %c\n", (int)d);
        move_player(m, d);
        display(*m);
        clear_buffer();
    }
    //show_player(m->player);
    //display_debug(*m);
    destroy_maze(m);
    return 0;
}
