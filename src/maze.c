#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "maze.h"

void brick_maze(maze *m) {
    int length = m->length;
    int width = m->width;
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            m->content[i][j] = WALL;
        }
    }
}

void drill_maze(maze *m) {
    int length = m->length;
    int width = m->width;
    int id = 0;
    for (int i = 1; i < length; i += 2) {
        for (int j = 1; j < width; j += 2) {
            m->content[i][j] = id;
            id++;
        }
    }
}

void merge_paths(maze *m, int old_id, int new_id) {
    int length = m->length;
    int width = m->width;
    for (int i = 1; i < length; i++) {
        for (int j = 1; j < width; j++) {
            if (m->content[i][j] == old_id) {
                m->content[i][j] = new_id;
            }
        }
    }
}

void open_wall(maze *m, int i, int j, int di, int dj) {
    cell *current = &m->content[i][j];
    cell *next = &m->content[i + di][j + dj];

    if (*current != *next) {
        m->content[i + di / 2][j + dj / 2] = *current;
        merge_paths(m, *next, *current);
    }
}

int all_paths_connected(maze *m) {
    int length = m->length;
    int width = m->width;
    int first_id = m->content[1][1];

    for (int i = 1; i < length; i += 2) {
        for (int j = 1; j < width; j += 2) {
            if (m->content[i][j] != first_id) {
                return 0;
            }
        }
    }
    return 1;
}

void place_exit(maze *m) {
    int length = m->length;
    int width = m->width;
    m->content[length - 1][width - 2] = EXIT;
}

cell* get_random_path(maze *m) {
    int length = m->length;
    int width = m->width;
    int i = 0;
    int j = 0;
    do {
        i = rand() % length;
        j = rand() % width;
    } while (m->content[i][j] < PATH);
    return &m->content[i][j];
}

void place_key(maze *m) {
    cell *key = get_random_path(m);
    *key = KEY;
}

void place_treasures(maze *m) {
    int size = m->length * m->width;
    for (int i = 0; i < size / 50; i++) {
        cell *c = get_random_path(m);
        *c = TREASURE;
    }
}

void place_traps(maze *m) {
    int size = m->length * m->width;
    for (int i = 0; i < size / 70; i++) {
        cell *c = get_random_path(m);
        *c = TRAP;
    }
}

void remove_cell(maze *m, int x, int y) {
    m->content[x][y] = PATH;
}

void generate_maze(maze *m) {
    int length = m->length;
    int width = m->width;
    int directions[4][2] = {{0, 2}, {0, -2}, {2, 0}, {-2, 0}};

    while (!all_paths_connected(m)) {
        int i = rand() % (length / 2) * 2 + 1;
        int j = rand() % (width / 2) * 2 + 1;
        int dir = rand() % 4;

        int ni = i + directions[dir][0];
        int nj = j + directions[dir][1];

        if (ni >= 1 && ni < length - 1 && nj >= 1 && nj < width - 1) {
            open_wall(m, i, j, directions[dir][0], directions[dir][1]);
        }
    }
    place_exit(m);
    place_key(m);
    place_treasures(m);
    place_traps(m);
}

/**
 * Give maze (functionnal)
 */
maze* new_maze(int length, int width) {
    if(!(length % 2) || !(width % 2)) return NULL;
    maze* m = (maze*) malloc(sizeof(maze));
    m->length = length;
    m->width = width;
    m->content = (cell**) malloc(length * sizeof(cell*));
    for (int i = 0; i < length; i++) {
        m->content[i] = (cell*) malloc(width * sizeof(cell));
    }
    place_player(m);
    brick_maze(m);
    drill_maze(m);
    return m;
}

void destroy_maze(maze *m) {
    for (int i = 0; i < m->length; i++) {
        free(m->content[i]);
    }
    free(m->player);
    free(m->content);
    free(m);
}

void display(maze *m) {
    int length = m->length;
    int width = m->width;
    player p = *m->player;

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            if (is_player_at(p, i, j)) {
                attron(COLOR_PAIR(10));
                printw("  ");
                attroff(COLOR_PAIR(10));
                continue;
            }

            cell b = m->content[i][j];
            attron(COLOR_PAIR(-(b)));
            printw("  ");
            attroff(COLOR_PAIR(-(b)));
        }
        printw("\n");
    }

    display_player_data(m->player);
}
