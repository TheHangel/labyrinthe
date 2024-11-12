#ifndef MAZE_H
#define MAZE_H

#include <ncurses.h>
#include "game.h"
#include "player.h"
#include "monster.h"

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
 * @file maze.h
 * @brief Maze generation and manipulation.
 * 
 * @version 1.0.0
 * @date November 15, 2024
 * 
 * @details Contains functions and data structures for creating, manipulating, and displaying a maze 
 * in a terminal-based game, including player and monster positioning and movement.
 */

/**
 * @struct maze
 * @brief Structure representing the maze layout and associated elements.
 */
struct maze {
    char* name;           ///< Name of the maze.
    cell **content;       ///< 2D array representing the maze cells.
    int length;           ///< Length of the maze (number of rows).
    int width;            ///< Width of the maze (number of columns).
    player *player;       ///< Pointer to the player in the maze.
    monster *monsters;    ///< Array of monsters present in the maze.
    int n_monsters;       ///< Number of monsters in the maze.
};

/**
 * @brief Fills the maze with walls in preparation for path drilling.
 * 
 * @param m Pointer to the maze.
 */
void brick_maze(maze *m);

/**
 * @brief Drills paths within the maze by assigning unique identifiers to create passageways.
 * 
 * @param m Pointer to the maze.
 */
void drill_maze(maze *m);

/**
 * @brief Merges two paths in the maze by updating their identifiers.
 * 
 * @param m Pointer to the maze.
 * @param old_id ID of the old path to be replaced.
 * @param new_id New path ID to apply across the merged cells.
 */
void merge_paths(maze *m, int old_id, int new_id);

/**
 * @brief Opens a wall between two cells in the maze.
 * 
 * @param m Pointer to the maze.
 * @param i Row index of the first cell.
 * @param j Column index of the first cell.
 * @param di Row direction for the second cell relative to the first.
 * @param dj Column direction for the second cell relative to the first.
 */
void open_wall(maze *m, int i, int j, int di, int dj);

/**
 * @brief Checks if all paths in the maze are connected.
 * 
 * @param m Pointer to the maze.
 * @return 1 if all paths are connected, 0 otherwise.
 */
int all_paths_connected(maze *m);

/**
 * @brief Retrieves a random path cell in the maze.
 * 
 * @param m Pointer to the maze.
 * @return Pointer to a random path cell.
 */
cell* get_random_path(maze *m);

/**
 * @brief Retrieves a random wall cell in the maze.
 * 
 * @param m Pointer to the maze.
 * @return Pointer to a random wall cell.
 */
cell* get_random_wall(maze *m);

/**
 * @brief Retrieves the coordinates of a given cell in the maze.
 * 
 * @param m Pointer to the maze.
 * @param c Pointer to the target cell.
 * @param x Pointer to store the x-coordinate.
 * @param y Pointer to store the y-coordinate.
 */
void get_coords_from_cell(maze *m, cell *c, int *x, int *y);

/**
 * @brief Checks if a cell is a path.
 * 
 * @param cell The cell to check.
 * @return 1 if the cell is a path, 0 otherwise.
 */
int is_path(cell cell);

/**
 * @brief Checks if a cell is a wall.
 * 
 * @param cell The cell to check.
 * @return 1 if the cell is a wall, 0 otherwise.
 */
int is_wall(cell cell);

/**
 * @brief Checks if a wall cell is on the maze border.
 * 
 * @param m Pointer to the maze.
 * @param c Pointer to the wall cell.
 * @return 1 if the wall is a border wall, 0 otherwise.
 */
int is_wall_a_border(maze *m, cell *c);

/**
 * @brief Randomly removes a specified number of walls in the maze.
 * 
 * @param m Pointer to the maze.
 * @param n Number of walls to remove.
 */
void destroy_walls(maze *m, int n);

/**
 * @brief Places the exit cell in the maze.
 * 
 * @param m Pointer to the maze.
 */
void place_exit(maze *m);

/**
 * @brief Places a key cell in the maze.
 * 
 * @param m Pointer to the maze.
 */
void place_key(maze *m);

/**
 * @brief Randomly places treasures in the maze.
 * 
 * @param m Pointer to the maze.
 */
void place_treasures(maze *m);

/**
 * @brief Randomly places traps in the maze.
 * 
 * @param m Pointer to the maze.
 */
void place_traps(maze *m);

/**
 * @brief Removes a specific cell from the maze.
 * 
 * @param m Pointer to the maze.
 * @param x X-coordinate of the cell.
 * @param y Y-coordinate of the cell.
 */
void remove_cell(maze *m, int x, int y);

/**
 * @brief Generates a complete maze with paths, walls, and items.
 * 
 * @param m Pointer to the maze.
 * @param d Difficulty level for maze generation.
 */
void generate_maze(maze *m, difficulty d);

/**
 * @brief Creates a new maze with specified dimensions and name.
 * 
 * @param name The name of the maze.
 * @param length Length of the maze.
 * @param width Width of the maze.
 * @return Pointer to the new maze or NULL on failure.
 */
maze* new_maze(char* name, int length, int width);

/**
 * @brief Frees all memory associated with a maze.
 * 
 * @param m Pointer to the maze to be destroyed.
 */
void destroy_maze(maze *m);

/**
 * @brief Displays the maze within a specified window.
 * 
 * @param m Pointer to the maze.
 * @param w Pointer to the ncurses window for rendering.
 */
void display(maze *m, WINDOW *w);

#endif
