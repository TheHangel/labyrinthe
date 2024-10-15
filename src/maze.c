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

void merge_paths(maze *m, int old_id, int new_id) {
    for (int i = 1; i < LENGTH; i += 2) {
        for (int j = 1; j < WIDTH; j += 2) {
            if (m->content[i][j].id == old_id) {
                m->content[i][j].id = new_id;
            }
        }
    }
}

void open_wall(maze *m, int i, int j, int di, int dj) {
    box *current = &m->content[i][j];
    box *next = &m->content[i + di][j + dj];

    if (current->id != next->id) {
        m->content[i + di / 2][j + dj / 2].symbol = PATH;
        m->content[i + di / 2][j + dj / 2].id = current->id;
        merge_paths(m, next->id, current->id);
    }
}

int all_paths_connected(maze *m) {
    int first_id = m->content[1][1].id;

    for (int i = 1; i < LENGTH; i += 2) {
        for (int j = 1; j < WIDTH; j += 2) {
            if (m->content[i][j].id != first_id) {
                return 0;
            }
        }
    }
    return 1;
}

void place_player(maze *m) {
    m->content[0][1].symbol = PLAYER;
}

void place_exit(maze *m) {
    m->content[LENGTH-1][WIDTH-2].symbol = EXIT;
}

void generate_maze(maze *m) {
    int directions[4][2] = {{0, 2}, {0, -2}, {2, 0}, {-2, 0}};

    while (!all_paths_connected(m)) {
        int i = rand() % (LENGTH / 2) * 2 + 1;
        int j = rand() % (WIDTH / 2) * 2 + 1;
        int dir = rand() % 4;

        int ni = i + directions[dir][0];
        int nj = j + directions[dir][1];

        if (ni >= 1 && ni < LENGTH - 1 && nj >= 1 && nj < WIDTH - 1) {
            open_wall(m, i, j, directions[dir][0], directions[dir][1]);
        }
    }
    place_player(m);
    place_exit(m);
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

void destroy_maze(maze *m) {
    free(m);
}

void display(maze m) {
    for(int i=0; i<LENGTH; i++) {
        for(int j=0; j<WIDTH; j++) {
            box b = m.content[i][j];
            printf("%c", b.symbol);
        }
        printf("\n");
    }
}

void display_debug(maze m) {
    for(int i=0; i<LENGTH; i++) {
        for(int j=0; j<WIDTH; j++) {
            box b = m.content[i][j];
            if(b.symbol == PATH) {
                printf("%d", b.id);
            }
            else {
                printf("%c", b.symbol);
            }
        }
        printf("\n");
    }
}
