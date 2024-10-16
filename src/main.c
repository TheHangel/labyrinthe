#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "maze.h"

int main(void) {
    //srand(time(NULL));
    maze *m = new_maze();
    generate_maze(m);
    //int t = move_player(m, );
    int t = move_player(m, 1);
    t = move_player(m, 3);
    t = move_player(m, 3);
    t = move_player(m, 1);
    printf("result move: %d\n", t);
    display(*m);
    show_player(m->player);
    //display_debug(*m);
    destroy_maze(m);
    return 0;
}
