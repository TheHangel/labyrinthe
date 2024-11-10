#ifndef FILE_H
#define FILE_H

#include "maze.h"

// paths
#define DATA_PATH             "data/"

// extensions
#define MAZE_EXTENSION        ".cfg"
#define LEADERBOARD_EXTENSION ".score"

char* get_maze_path(maze *m);
char* get_leaderboard_path(maze *m);

#endif
