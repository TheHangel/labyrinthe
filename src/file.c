#include <stdlib.h>
#include <string.h>
#include "file.h"

char* get_maze_path(maze *m) {
    size_t total_length = strlen(DATA_PATH) + strlen(m->name) + strlen(MAZE_EXTENSION) + 1;
    char* filename = malloc(total_length);
    strcpy(filename, DATA_PATH);
    strcat(filename, m->name);
    strcat(filename, MAZE_EXTENSION);
    return filename;
}

char* get_leaderboard_path(maze *m) {
    size_t total_length = strlen(DATA_PATH) + strlen(m->name) + strlen(LEADERBOARD_EXTENSION) + 1;
    char* filename = malloc(total_length);
    strcpy(filename, DATA_PATH);
    strcat(filename, m->name);
    strcat(filename, LEADERBOARD_EXTENSION);
    return filename;
}
