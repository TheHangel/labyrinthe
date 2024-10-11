#include <stdio.h>
#include "maze.h"

int main(void) {
    maze *m = new_maze();
    display(*m);
    return 0;
}
