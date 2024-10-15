#include <stdio.h>
#include "maze.h"

int main(void) {
    maze *m = new_maze();
    generate_maze(m);
    display(*m);
    destroy_maze(m);
    return 0;
}
