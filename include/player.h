#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"
#include "maze.h"
#include "input.h"

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
 * @file player.h
 * @brief Defines structures and functions related to the player in the game.
 * 
 * @version 1.0.0
 * @date November 15, 2024
 * 
 * @details This file includes the `player` structure definition and functions
 * that handle the player's position, movements, interactions, and score management within the maze.
 */

/**
 * @struct player
 * @brief Structure representing the player in the maze.
 */
struct player {
    int x;            ///< x-coordinate in the maze
    int y;            ///< y-coordinate in the maze
    int moves;        ///< Number of moves made by the player
    int score;        ///< Current score of the player
    int has_key;      ///< Key possession flag (1 if the player has the key)
    int exited;       ///< Exit flag (1 if the player has exited the maze)
};

/**
 * @brief Moves the player within the maze based on the given direction.
 * 
 * @param m Pointer to the maze containing the player.
 * @param dir The direction to move (UP, DOWN, LEFT, RIGHT).
 * @return 1 if the player moved successfully, 0 otherwise.
 */
int move_player(maze *m, direction dir);

/**
 * @brief Checks the player's position in the maze to handle key interactions.
 * 
 * @param m Pointer to the maze.
 * @return 1 if the player has exited the maze, 0 otherwise.
 */
int check_player_pos(maze *m);

/**
 * @brief Places the player at the starting position within the maze.
 * 
 * @param m Pointer to the maze where the player will be placed.
 */
void place_player(maze *m);

/**
 * @brief Retrieves the cell in the maze where the player is currently located.
 * 
 * @param m Pointer to the maze.
 * @return A pointer to the cell containing the player.
 */
cell *get_cell_from_player_pos(maze *m);

/**
 * @brief Checks if the player is at a specific maze position.
 * 
 * @param p The player to check.
 * @param x The x-coordinate to check.
 * @param y The y-coordinate to check.
 * @return 1 if the player is at the specified coordinates, 0 otherwise.
 */
int is_player_at(player p, int x, int y);

/**
 * @brief Checks if the player is on a specific cell type.
 * 
 * @param m Pointer to the maze.
 * @param c The cell type to check.
 * @return 1 if the player is on the specified cell type, 0 otherwise.
 */
int is_player_on(maze *m, cell c);

/**
 * @brief Checks if the player is on the same position as any monster in the maze.
 * 
 * @param m Pointer to the maze.
 * @return Index + 1 of the monster if the player is on a monster, 0 otherwise.
 */
int is_player_on_monster(maze *m);

/**
 * @brief Removes the cell content where the player is currently located, setting it as a path.
 * 
 * @param m Pointer to the maze.
 */
void remove_cell_at_player(maze *m);

/**
 * @brief Displays player data (moves and score) in a specified window.
 * 
 * @param p Pointer to the player.
 * @param w Window where the data will be displayed.
 * @return Result of the mvwprintw function call.
 */
int display_player_data(player *p, WINDOW *w);

/**
 * @brief Calculates the player's final score based on moves and points.
 * 
 * @param p Pointer to the player.
 * @return The final score of the player.
 */
int get_final_score(player *p);

/**
 * @brief Converts the player's score into a string representation.
 * 
 * @param score The score to convert.
 * @return A pointer to a string containing the score.
 */
char *convert_score_to_string(int score);

/**
 * @brief Frees the memory allocated for the player.
 * 
 * @param m Pointer to the maze containing the player.
 */
void destroy_player(maze *m);

#endif
