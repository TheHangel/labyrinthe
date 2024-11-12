#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include "game.h"

/*
 * ENSICAEN
 * 6 Boulevard Maréchal Juin
 * F-14050 Caen Cedex 
 * 
 * This file is owned by Thibaud Lebrasseur. No portion of this 
 * document may be reproduced, copied, or revised without written 
 * permission of the authors.
 */

/**
 * @file leaderboard.h
 * @brief Managing the leaderboard system.
 * 
 * @version 1.0.0
 * @date November 15, 2024
 * @details Defines structures and functions to manage, display, 
 * and sort player scores in the leaderboard.
 */

#define MAX_PLAYERS 10 ///< Maximum number of players that can be displayed in the leaderboard.

/**
 * @brief Represents a player's score entry in the leaderboard.
 */
typedef struct {
    char *name;  ///< Player's name in the leaderboard entry.
    int score;   ///< Player's score in the leaderboard entry.
} player_score;

/**
 * @brief Structure representing the leaderboard.
 */
struct leaderboard {
    player_score players[MAX_PLAYERS]; ///< Array of player scores sorted in descending order.
    int count;                         ///< The current count of players in the leaderboard.
};

/**
 * @brief Displays the leaderboard in a ncurses window.
 * 
 * @param lb Pointer to the leaderboard to display.
 * @param highlight_name The name of the player to highlight in the display, if any.
 */
void display_leaderboard(leaderboard *lb, const char *highlight_name);

/**
 * @brief Adds a new player score to the leaderboard.
 * 
 * @param lb Pointer to the leaderboard.
 * @param name The name of the player.
 * @param score The player's score.
 */
void add_player_to_leaderboard(leaderboard *lb, const char *name, int score);

/**
 * @brief Compares two player scores. Used for sorting.
 * 
 * @param a Pointer to the first player score.
 * @param b Pointer to the second player score.
 * @return int Negative if `b`'s score is higher, positive if `a`'s score is higher, zero if equal.
 */
int compare_scores(const void *a, const void *b);

/**
 * @brief Sorts the leaderboard in descending order based on scores.
 * 
 * @param lb Pointer to the leaderboard.
 */
void sort_leaderboard(leaderboard *lb);

/**
 * @brief Frees memory used by names in the leaderboard.
 * 
 * @param lb Pointer to the leaderboard.
 */
void destroy_leaderboard(leaderboard *lb);

#endif
