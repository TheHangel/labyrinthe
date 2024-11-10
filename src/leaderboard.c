#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "display.h"
#include "leaderboard.h"

int height = 0;
int width  = 0;

void display_leaderboard(leaderboard *lb, const char *highlight_name) {
    int max_displayable = MAX_PLAYERS;
    int win_height = (lb->count < max_displayable) ? lb->count + 6 : max_displayable + 6;
    int win_width = 30;

    WINDOW *win = create_centered_window(win_height, win_width);

    const char *title = "Leaderboard";
    mvwprintw(win, 1, (win_width - strlen(title)) / 2, "%s", title);

    int col_pseudo = 2;
    int col_score = win_width - 12;
    mvwprintw(win, 3, col_pseudo, "Players");
    mvwprintw(win, 3, col_score, "Score");

    // Limiter les lignes pour ne pas dépasser la hauteur de la fenêtre
    int display_count = (lb->count < max_displayable) ? lb->count : max_displayable;
    for (int i = 0; i < display_count; i++) {
        int y = 4 + i;

        if (highlight_name && strcmp(lb->players[i].name, highlight_name) == 0) {
            wattron(win, A_REVERSE);
        }

        mvwprintw(win, y, col_pseudo, "%-20s", lb->players[i].name);
        mvwprintw(win, y, col_score, "%10d", lb->players[i].score);

        wattroff(win, A_REVERSE);
    }

    wattron(win, A_REVERSE);
    mvwprintw(win, win_height - 2, (win_width - strlen("OK")) / 2, "OK");
    wattroff(win, A_REVERSE);

    wrefresh(win);

    int ch;
    while ((ch = wgetch(win)) != '\n');

    werase(win);
    wrefresh(win);
    delwin(win);
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
    else {
        player_score *last_player = &lb->players[lb->count - 1];
        if (score > last_player->score) {
            free(last_player->name);
            last_player->name = malloc(strlen(name) + 1);
            if (last_player->name != NULL) {
                strcpy(last_player->name, name);
                last_player->score = score;
            }
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
    return EXIT_FAILURE;
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
