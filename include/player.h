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
    int exited;
};

int move_player(maze *m, direction dir);
int check_player_pos(maze *m);
void place_player(maze *m);
cell *get_cell_from_player_pos(maze *m);
int is_player_at(player p, int x, int y);
int is_player_on(maze *m, cell c);
int is_player_on_monster(maze *m);
void remove_cell_at_player(maze *m);
int display_player_data(player *p, WINDOW *w);
int get_final_score(player *p);
char *convert_score_to_string(int score);
void destroy_player(maze *m);

#endif
