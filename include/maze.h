#ifndef MAZE_H
#define MAZE_H

#include "game.h"
#include "player.h"

#define PATH      0
#define WALL     -1
#define KEY      -2
#define TREASURE -3
#define TRAP     -4
#define EXIT     -5

struct maze {
    cell **content;
    int length;
    int width;
    player *player;
};

void brick_maze(maze *m);
void drill_maze(maze *m);
void merge_paths(maze *m, int old_id, int new_id);
void open_wall(maze *m, int i, int j, int di, int dj);
int all_paths_connected(maze *m);
void place_exit(maze *m);
cell* get_random_path(maze *m);
void place_key(maze *m);
void place_treasures(maze *m);
void place_traps(maze *m);
void remove_cell(maze *m, int x, int y);
void generate_maze(maze *m);
maze* new_maze(int length, int width);
void destroy_maze(maze *m);
void display(maze m);

#endif
