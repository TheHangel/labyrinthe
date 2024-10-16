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
    int length = m->length;
    int width = m->width;
    for(int i=0; i<length; i++) {
        for(int j=0; j<width; j++) {
            box* b = wall();
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
            box* b = (box*) malloc(sizeof(box));
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
    for (int i = 1; i < length; i += 2) {
        for (int j = 1; j < width; j += 2) {
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

    char lu = m->content[p->x-1][p->y-1].symbol;
    char u = m->content[p->x-1][p->y].symbol;
    char ru = m->content[p->x-1][p->y+1].symbol;
    char l = m->content[p->x][p->y-1].symbol;
    char r = m->content[p->x][p->y+1].symbol;
    char ld = m->content[p->x+1][p->y-1].symbol;
    char d = m->content[p->x][p->y-1].symbol;
    char rd = m->content[p->x+1][p->y+1].symbol;

    printf("\n");
    printf("%c%c%c\n", lu, u, ru);
    printf("%c%c%c\n", l, pc, r);
    printf("%c%c%c\n", ld, d, rd);
    printf("\n");
}

int move_player(maze *m, int direction) {
    show_surrounding_player(m);
    player *p = m->player;
    // 0 = up, 1 = down, 2 = left, 3 = right
    if(direction == 0) {
        if(p->x == 0) {
            return -1;
        }
        if(m->content[p->x+1][p->y].symbol != WALL) {
            return (p->x += 1);
        }
    }
    if(direction == 1) {
        char symbol = m->content[p->x+1][p->y].symbol;
        printf("check at: %c\n", symbol);
        if(symbol != WALL) {
            return (p->x += 1);
        }
    }
    if(direction == 2) {
        char symbol = m->content[p->x][p->y-1].symbol;
        printf("check at: %c\n", symbol);
        if(symbol != WALL) {
            return (p->y -= 1);
        }
    }
    if(direction == 3) {
        char symbol = m->content[p->x][p->y+1].symbol;
        printf("check at: %c\n", symbol);
        if(symbol != WALL) {
            return (p->y += 1);
        }
    }
    return 0;
}

void show_player(player *p) {
    printf("Player:\n");
    printf("x:%d\n", p->x);
    printf("y:%d\n", p->y);
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
    maze* m = (maze*) malloc(sizeof(maze));
    m->length = length;
    m->width = width;
    m->content = (box**) malloc(length * sizeof(box*));
    for (int i = 0; i < length; i++) {
        m->content[i] = (box*) malloc(width * sizeof(box));
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

int is_player_at(player p, int x, int y) {
    return (p.x == x && p.y == y);
}

void display(maze m) {
    int length = m.length;
    int width = m.width;
    player p = *m.player;
    for(int i=0; i<length; i++) {
        for(int j=0; j<width; j++) {
            if(is_player_at(p, i, j)) {
                printf("%c", PLAYER);
                continue;
            }
            box b = m.content[i][j];
            printf("%c", b.symbol);
        }
        printf("\n");
    }
}

void display_debug(maze m) {
    int length = m.length;
    int width = m.width;
    for(int i=0; i<length; i++) {
        for(int j=0; j<width; j++) {
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
