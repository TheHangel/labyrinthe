#ifndef FILE_H
#define FILE_H

#include "maze.h"

#define MAX_FILES 1024

// paths
#define DATA_PATH             "data/"

// extensions
#define MAZE_EXTENSION        ".cfg"
#define LEADERBOARD_EXTENSION ".score"

char* get_maze_path(char *maze_name);
char* get_leaderboard_path(char *maze_name);
char** list_saves_files(const char *directory, int *file_count, extension ext);
int save_maze_to_file(const char *filename, maze *m);
maze* load_maze_from_file(const char *filename);

#endif
