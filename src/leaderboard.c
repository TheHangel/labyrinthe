#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leaderboard.h"

#include <stdio.h>

void display_leaderboard(leaderboard *lb) {
    printf("Leaderboard:\n");
    printf("%-20s %10s\n", "Pseudo", "Score");

    for (int i = 0; i < lb->count; i++) {
        printf("%-20s %10d\n", lb->players[i].name, lb->players[i].score);
    }
}

void add_player_to_leaderboard(leaderboard *lb, const char *name, int score) {
    if (lb->count < MAX_PLAYERS) {
        lb->players[lb->count].name = malloc(strlen(name) + 1);
        if (lb->players[lb->count].name != NULL) {
            strcpy(lb->players[lb->count].name, name);
            lb->players[lb->count].score = score;
            lb->count++;
        }
    }
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
    return 0;
}

int compare_scores(const void *a, const void *b) {
    player_score *playerA = (player_score *)a;
    player_score *playerB = (player_score *)b;
    return playerB->score - playerA->score;
}

void sort_leaderboard(leaderboard *lb) {
    qsort(lb->players, lb->count, sizeof(player_score), compare_scores);
}

void destroy_leaderboard(leaderboard *lb) {
    for (int i = 0; i < lb->count; i++) {
        free(lb->players[i].name);
    }
    lb->count = 0;
}
