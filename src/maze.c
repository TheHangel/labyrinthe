#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

box* wall() {
    box* b = (box*) malloc(sizeof(box));
    b->id = -1;
    b->symbol = WALL;
    return b;
}

void brick_maze(maze *m) {
    for(int i=0; i<LENGTH; i++) {
        for(int j=0; j<WIDTH; j++) {
            box* b = wall();
            m->content[i][j] = *b;
        }
    }
}

/**
 * Give maze (functionnal)
 */
maze* new_maze() {
    maze* m = (maze*) malloc(sizeof(maze));
    brick_maze(m);
    // poser
    return m;
}

void display(maze m) {
    for(int i=0; i<LENGTH; i++) {
        for(int j=0; j<WIDTH; j++) {
            printf("%c", m.content[i][j].symbol);
        }
        printf("\n");
    }
}
