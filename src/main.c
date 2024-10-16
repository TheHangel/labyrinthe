#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "maze.h"

int main(void) {
    //srand(time(NULL));
    maze *m = new_maze(LENGTH, WIDTH);
    generate_maze(m);
    //int t = move_player(m, );
    int t = move_player(m, DOWN);
    t = move_player(m, RIGHT);
    t = move_player(m, RIGHT);
    t = move_player(m, DOWN);
    printf("result move: %d\n", t);
    display(*m);
    //show_player(m->player);
    //display_debug(*m);
    destroy_maze(m);
    return 0;
}
