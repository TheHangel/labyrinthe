#ifndef FILE_H
#define FILE_H

#include "maze.h"

// paths
#define DATA_PATH             "data/"

// extensions
#define MAZE_EXTENSION        ".cfg"
#define LEADERBOARD_EXTENSION ".score"

char* get_maze_path(char *maze_name);
char* get_leaderboard_path(char *maze_name);

#endif
