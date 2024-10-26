#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"
#include "maze.h"

struct player {
    int x;
    int y;
    int moves;
    int score;
    int has_key;
};

int move_player(maze *m, direction dir);
void place_player(maze *m);
void show_surrounding_player(maze *m);
void display_player_debug(player p);
cell *get_cell_from_player_pos(maze *m);
int is_player_at(player p, int x, int y);
int is_player_at_exit(maze m);
int is_player_on_key(maze m);
int is_player_on_treasure(maze m);
int is_player_on_trap(maze m);
void remove_cell_at_player(maze *m);
int display_player_data(player p);

#endif
