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
    p->moves = 0;
    p->score = 0;
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
        p->moves++;
        return 1;
    }
    return 0;
}

void display_player_debug(player p) {
    printw("Player:\n");
    printw("x:%d\n", p.x);
    printw("y:%d\n", p.y);
}

cell *get_cell_from_player_pos(maze *m) {
    player *p = m->player;
    return &m->content[p->x][p->y];
}

int is_player_at(player p, int x, int y) {
    return (p.x == x && p.y == y);
}

int is_player_at_exit(maze m) {
    return (get_cell_from_player_pos(&m)->symbol == EXIT);
}

int is_player_on_key(maze m) {
    return (get_cell_from_player_pos(&m)->symbol == KEY);
}

int is_player_on_treasure(maze m) {
    return (get_cell_from_player_pos(&m)->symbol == TREASURE);
}

int is_player_on_trap(maze m) {
    return (get_cell_from_player_pos(&m)->symbol == TRAP);
}

void place_exit(maze *m) {
    int length = m->length;
    int width = m->width;
    m->content[length-1][width-2].symbol = EXIT;
}

cell* get_random_path(maze *m) {
    int length = m->length;
    int width = m->width;
    int i = 0;
    int j = 0;
    do {
        i = rand() % length;
        j = rand() % width;
    } while (m->content[i][j].symbol != PATH);
    return &m->content[i][j];
}

void place_key(maze *m) {
    cell *key = get_random_path(m);
    key->symbol = KEY;
    key->id = -2;
}

void place_treasures(maze *m) {
    int size = m->length * m->width;
    for (int i = 0; i < size / 50; i++) {
        cell *c = get_random_path(m);
        c->symbol = TREASURE;
        c->id = -3;
    }
}

void place_traps(maze *m) {
    int size = m->length * m->width;
    for (int i = 0; i < size / 70; i++) {
        cell *c = get_random_path(m);
        c->symbol = TRAP;
        c->id = -4;
    }
}

void remove_cell(maze *m, int x, int y) {
    cell *c = &m->content[x][y];
    c->symbol = PATH;
    c->id = 0;
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

int display_player_data(player p) {
    return printw("Moves: %2d - Score: %2d\n", p.moves, p.score);
}

void display(maze m) {
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_WHITE, COLOR_YELLOW);
    init_pair(5, COLOR_WHITE, COLOR_GREEN);
    init_pair(6, COLOR_WHITE, COLOR_RED);
    init_pair(7, COLOR_WHITE, COLOR_MAGENTA);

    int length = m.length;
    int width = m.width;
    player p = *m.player;

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            if (is_player_at(p, i, j)) {
                attron(COLOR_PAIR(3));
                printw("  ");
                attroff(COLOR_PAIR(3));
                continue;
            }

            cell b = m.content[i][j];
            if (b.symbol == WALL) {
                attron(COLOR_PAIR(1));
                printw("  ");
                attroff(COLOR_PAIR(1));
            } else if (b.symbol == PATH) {
                attron(COLOR_PAIR(2));
                printw("  ");
                attroff(COLOR_PAIR(2));
            } else if (b.symbol == KEY) {
                attron(COLOR_PAIR(4));
                printw("  ");
                attroff(COLOR_PAIR(4));
            } else if (b.symbol == TREASURE) {
                attron(COLOR_PAIR(5));
                printw("  ");
                attroff(COLOR_PAIR(5));
            } else if (b.symbol == TRAP) {
                attron(COLOR_PAIR(6));
                printw("  ");
                attroff(COLOR_PAIR(6));
            } else if (b.symbol == EXIT) {
                attron(COLOR_PAIR(7));
                printw("  ");
                attroff(COLOR_PAIR(7));
            }
        }
        printw("\n");
    }

    display_player_data(*m.player);
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
    display_player_debug(*m.player);
    printw("Dimension:\n");
    printw("Lentgh: %2d\n", length);
    printw("Width: %2d\n", width);
}
