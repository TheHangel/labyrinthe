#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "maze.h"

int main(void) {
    srand(time(NULL));
    maze *m = new_maze();
    generate_maze(m);
    display(*m);
    destroy_maze(m);
    return 0;
}
