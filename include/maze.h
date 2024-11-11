#ifndef MAZE_H
#define MAZE_H

#include <ncurses.h>
#include "game.h"
#include "player.h"
#include "monster.h"

struct maze {
    char* name;
    cell **content;
    int length;
    int width;
    player *player;
    monster *monsters;
    int n_monsters;
};

void brick_maze(maze *m);
void drill_maze(maze *m);
void merge_paths(maze *m, int old_id, int new_id);
void open_wall(maze *m, int i, int j, int di, int dj);
int all_paths_connected(maze *m);
void place_exit(maze *m);
cell* get_random_path(maze *m);
void get_coords_from_cell(maze *m, cell *c, int *x, int *y);
void place_key(maze *m);
void place_treasures(maze *m);
void place_traps(maze *m);
void remove_cell(maze *m, int x, int y);
void generate_maze(maze *m, difficulty d);
maze* new_maze(char* name, int length, int width);
void destroy_maze(maze *m);
void display(maze *m, WINDOW *w);
int save_maze_to_file(const char *filename, maze *m);
maze* load_maze_from_file(const char *filename);

#endif
