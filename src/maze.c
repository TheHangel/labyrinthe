#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "maze.h"

cell* wall() {
    cell* b = (cell*) malloc(sizeof(cell));
    b->id = -1;
    b->symbol = WALL;
    return b;
}

void brick_maze(maze *m) {
    int length = m->length;
    int width = m->width;
    for(int i=0; i<length; i++) {
        for(int j=0; j<width; j++) {
            cell* b = wall();
            m->content[i][j] = *b;
        }
    }
}

void drill_maze(maze *m) {
    int length = m->length;
    int width = m->width;
    int id = 0;
    for(int i=1; i<length; i+=2) {
        for(int j=1; j<width; j+=2) {
            cell* b = (cell*) malloc(sizeof(cell));
            b->id = id;
            b->symbol = PATH;
            m->content[i][j] = *b;
            id++;
        }
    }
}

void merge_paths(maze *m, int old_id, int new_id) {
    int length = m->length;
    int width = m->width;
    for (int i = 1; i < length; i++) {
        for (int j = 1; j < width; j++) {
            if (m->content[i][j].id == old_id) {
                m->content[i][j].id = new_id;
            }
        }
    }
}

void open_wall(maze *m, int i, int j, int di, int dj) {
    cell *current = &m->content[i][j];
    cell *next = &m->content[i + di][j + dj];

    if (current->id != next->id) {
        m->content[i + di / 2][j + dj / 2].symbol = PATH;
        m->content[i + di / 2][j + dj / 2].id = current->id;
        merge_paths(m, next->id, current->id);
    }
}

int all_paths_connected(maze *m) {
    int length = m->length;
    int width = m->width;
    int first_id = m->content[1][1].id;

    for (int i = 1; i < length; i += 2) {
        for (int j = 1; j < width; j += 2) {
            if (m->content[i][j].id != first_id) {
                return 0;
            }
        }
    }
    return 1;
}

void place_player(maze *m) {
    player* p = (player*) malloc(sizeof(player));
    p->x = 0;
    p->y = 1;
    m->player = p;
}

void show_surrounding_player(maze *m) {
    player *p = m->player;
    char pc = 'o';

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (p->x + i >= 0 && p->x + i < m->length && p->y + j >= 0 && p->y + j < m->width) {
                if (i == 0 && j == 0) {
                    printw("%c", pc);
                } else {
                    printw("%c", m->content[p->x + i][p->y + j].symbol);
                }
            } else {
                printw(" ");
            }
        }
        printw("\n");
    }
    printw("\n");
}

int move_player(maze *m, direction dir) {
    player *p = m->player;

    int direction_deltas[4][2] = {
        {-1, 0}, // UP
        {1, 0},  // DOWN
        {0, -1}, // LEFT
        {0, 1}   // RIGHT
    };

    int dx = direction_deltas[dir][0];
    int dy = direction_deltas[dir][1];

    int new_x = p->x + dx;
    int new_y = p->y + dy;

    if (new_x < 0 || new_x >= m->length || new_y < 0 || new_y >= m->width) {
        return -1;
    }

    if (m->content[new_x][new_y].symbol != WALL) {
        p->x = new_x;
        p->y = new_y;
        return 1;
    }
    return 0;
}

void show_player(player p) {
    printw("Player:\n");
    printw("x:%d\n", p.x);
    printw("y:%d\n", p.y);
}

int is_player_at(player p, int x, int y) {
    return (p.x == x && p.y == y);
}

int is_player_at_exit(maze m) {
    return (is_player_at(*m.player, m.length-1, m.width-2));
}

void place_exit(maze *m) {
    int length = m->length;
    int width = m->width;
    m->content[length-1][width-2].symbol = EXIT;
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
    free(m->content);
    free(m);
}

void display(maze m) {
    int length = m.length;
    int width = m.width;
    player p = *m.player;
    for(int i=0; i<length; i++) {
        for(int j=0; j<width; j++) {
            if(is_player_at(p, i, j)) {
                printw("%c", PLAYER);
                continue;
            }
            cell b = m.content[i][j];
            printw("%c", b.symbol);
        }
        printw("\n");
    }
}

void display_debug(maze m) {
    int length = m.length;
    int width = m.width;
    player p = *m.player;
    for(int i=0; i<length; i++) {
        for(int j=0; j<width; j++) {
            if(is_player_at(p, i, j)) {
                printw(" %c", PLAYER);
                continue;
            }
            cell b = m.content[i][j];
            if(b.symbol == PATH) {
                printw("%2d", b.id);
            }
            else {
                printw(" %c", b.symbol);
            }
        }
        printw("\n");
    }
    show_player(*m.player);
    printw("Dimension:\n");
    printw("Lentgh: %2d\n", length);
    printw("Width: %2d\n", width);
}
