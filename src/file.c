#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "game.h"
#include "maze.h"
#include "leaderboard.h"
#include "file.h"

int init_saves() {
    struct stat st = {0};

    if (stat(DATA_PATH, &st) == -1) {
        return mkdir(DATA_PATH, 0755);
    }
    return EXIT_SUCCESS;
}

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


int save_maze_to_file(const char *filename, maze *m) {
    FILE *file = fopen(filename, "wb");
    if (!file) return -1;

    int name_length = strlen(m->name) + 1;
    fwrite(&name_length, sizeof(int), 1, file);
    fwrite(m->name, sizeof(char), name_length, file);

    fwrite(&m->length, sizeof(int), 1, file);
    fwrite(&m->width, sizeof(int), 1, file);

    for (int i = 0; i < m->length; i++) {
        fwrite(m->content[i], sizeof(cell), m->width, file);
    }

    fwrite(m->player, sizeof(player), 1, file);

    fwrite(&m->n_monsters, sizeof(int), 1, file);
    fwrite(m->monsters, sizeof(monster), m->n_monsters, file);

    return fclose(file);
}

maze* load_maze_from_file(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) return NULL;

    maze *m = (maze*) malloc(sizeof(maze));
    if (!m) {
        fclose(file);
        return NULL;
    }

    int name_length;
    if (fread(&name_length, sizeof(int), 1, file) != 1) {
        free(m);
        fclose(file);
        return NULL;
    }

    m->name = (char*) malloc(name_length);
    if (!m->name || fread(m->name, sizeof(char), name_length, file) != (size_t)name_length) {
        free(m->name);
        free(m);
        fclose(file);
        return NULL;
    }

    if (fread(&m->length, sizeof(int), 1, file) != 1 || fread(&m->width, sizeof(int), 1, file) != 1) {
        fclose(file);
        free(m);
        return NULL;
    }

    m->content = (cell**) malloc(m->length * sizeof(cell*));
    if (!m->content) {
        fclose(file);
        free(m);
        return NULL;
    }
    for (int i = 0; i < m->length; i++) {
        m->content[i] = (cell*) malloc(m->width * sizeof(cell));
        if (!m->content[i] || fread(m->content[i], sizeof(cell), m->width, file) != (size_t)m->width) {
            for (int j = 0; j <= i; j++) {
                free(m->content[j]);
            }
            free(m->content);
            free(m);
            fclose(file);
            return NULL;
        }
    }

    m->player = (player*) malloc(sizeof(player));
    if (!m->player || fread(m->player, sizeof(player), 1, file) != 1) {
        for (int i = 0; i < m->length; i++) {
            free(m->content[i]);
        }
        free(m->content);
        free(m->player);
        free(m);
        fclose(file);
        return NULL;
    }

    if (fread(&m->n_monsters, sizeof(int), 1, file) != 1) {
        free(m->player);
        for (int i = 0; i < m->length; i++) {
            free(m->content[i]);
        }
        free(m->content);
        free(m);
        fclose(file);
        return NULL;
    }

    m->monsters = (monster*) malloc(m->n_monsters * sizeof(monster));
    if (!m->monsters || fread(m->monsters, sizeof(monster), m->n_monsters, file) != (size_t)m->n_monsters) {
        free(m->monsters);
        free(m->player);
        for (int i = 0; i < m->length; i++) {
            free(m->content[i]);
        }
        free(m->content);
        free(m);
        fclose(file);
        return NULL;
    }

    fclose(file);

    load_monster_functions(m);
    return m;
}

leaderboard load_leaderboard_from_file(const char *filename) {
    leaderboard lb = { .count = 0 };
    FILE *file = fopen(filename, "rb");

    if (file != NULL) {
        fread(&lb.count, sizeof(int), 1, file);

        for (int i = 0; i < lb.count; i++) {
            int name_len;
            fread(&name_len, sizeof(int), 1, file);

            lb.players[i].name = malloc(name_len + 1);
            fread(lb.players[i].name, sizeof(char), name_len, file);
            lb.players[i].name[name_len] = '\0';

            fread(&lb.players[i].score, sizeof(int), 1, file);
        }
        fclose(file);
    }

    return lb;
}

int save_leaderboard_to_file(const char *filename, leaderboard *lb) {
    FILE *file = fopen(filename, "wb");

    if (file != NULL) {
        fwrite(&lb->count, sizeof(int), 1, file);

        for (int i = 0; i < lb->count; i++) {
            int name_len = strlen(lb->players[i].name);
            fwrite(&name_len, sizeof(int), 1, file);
            fwrite(lb->players[i].name, sizeof(char), name_len, file);
            fwrite(&lb->players[i].score, sizeof(int), 1, file);
        }
        return fclose(file);
    }
    return EXIT_FAILURE;
}
