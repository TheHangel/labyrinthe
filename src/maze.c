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

void drill_maze(maze *m) {
    int id = 0;
    for(int i=1; i<LENGTH; i+=2) {
        for(int j=1; j<WIDTH; j+=2) {
            box* b = (box*) malloc(sizeof(box));
            b->id = id;
            b->symbol = PATH;
            m->content[i][j] = *b;
            id++;
        }
    }
}

/**
 * Give maze (functionnal)
 */
maze* new_maze() {
    maze* m = (maze*) malloc(sizeof(maze));
    brick_maze(m);
    drill_maze(m);
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
