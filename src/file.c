#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "game.h"
#include "file.h"

char* get_maze_path(char *maze_name) {
    size_t total_length = strlen(DATA_PATH) + strlen(maze_name) + strlen(MAZE_EXTENSION) + 1;
    char* filename = malloc(total_length);
    strcpy(filename, DATA_PATH);
    strcat(filename, maze_name);
    strcat(filename, MAZE_EXTENSION);
    return filename;
}

char* get_leaderboard_path(char *maze_name) {
    size_t total_length = strlen(DATA_PATH) + strlen(maze_name) + strlen(LEADERBOARD_EXTENSION) + 1;
    char* filename = malloc(total_length);
    strcpy(filename, DATA_PATH);
    strcat(filename, maze_name);
    strcat(filename, LEADERBOARD_EXTENSION);
    return filename;
}

char** list_saves_files(const char *directory, int *file_count, extension ext) {
    DIR *dir;
    struct dirent *entry;
    char **file_names = malloc(MAX_FILES * sizeof(char*));
    *file_count = 0;

    if ((dir = opendir(directory)) == NULL) {
        free(file_names);
        return NULL;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            char *dot = strrchr(entry->d_name, '.');
            if (dot && strcmp(dot, ext) == 0) {
                size_t name_len = dot - entry->d_name;
                file_names[*file_count] = malloc((name_len + 1) * sizeof(char));
                strncpy(file_names[*file_count], entry->d_name, name_len);
                file_names[*file_count][name_len] = '\0';
                (*file_count)++;
                if (*file_count >= MAX_FILES) break;
            }
        }
    }
    closedir(dir);

    file_names = realloc(file_names, *file_count * sizeof(char*));

    return file_names;
}
