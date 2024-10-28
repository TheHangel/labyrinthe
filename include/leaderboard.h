#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include "game.h"

#define MAX_PLAYERS 10

typedef struct {
    char *name;
    int score;
} player_score;

struct leaderboard {
    player_score players[MAX_PLAYERS];
    int count;
};

void display_leaderboard(leaderboard *lb);
void add_player_to_leaderboard(leaderboard *lb, const char *name, int score);
leaderboard load_leaderboard_from_file(const char *filename);
int save_leaderboard_to_file(const char *filename, leaderboard *lb);
int compare_scores(const void *a, const void *b);
void sort_leaderboard(leaderboard *lb);
void destroy_leaderboard(leaderboard *lb);

#endif
