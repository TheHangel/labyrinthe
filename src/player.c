#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "player.h"

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

    if (m->content[new_x][new_y] != WALL) {
        p->x = new_x;
        p->y = new_y;
        p->moves++;
        return 1;
    }
    return 0;
}

void place_player(maze *m) {
    player* p = (player*) malloc(sizeof(player));
    p->x = 0;
    p->y = 1;
    p->moves = 0;
    p->score = 0;
    m->player = p;
}

cell *get_cell_from_player_pos(maze *m) {
    player *p = m->player;
    return &m->content[p->x][p->y];
}

int is_player_at(player p, int x, int y) {
    return (p.x == x && p.y == y);
}

int is_player_on(maze *m, cell c) {
    return (*get_cell_from_player_pos(m) == c);
}

void remove_cell_at_player(maze *m) {
    int x = m->player->x;
    int y = m->player->y;
    m->content[x][y] = PATH;
}

int display_player_data(player p) {
    return printw("Moves: %2d - Score: %2d\n", p.moves, p.score);
}
