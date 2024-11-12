#ifndef MONSTER_H
#define MONSTER_H

#include "maze.h"

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
 * @file monster.h
 * @brief Defines structures and functions related to monsters in the game.
 * 
 * @version 1.0.0
 * @date November 15, 2024
 * 
 * @details This file contains the `monster` structure, functions for creating
 * and managing monsters, and functions for their movement within the maze.
 */

/**
 * @struct monster
 * @brief Structure representing a monster in the maze.
 */
struct monster {
    int x;                            ///< x-coordinate in the maze
    int y;                            ///< y-coordinate in the maze
    int type;                         ///< Type identifier for the monster
    int penalty;                      ///< Penalty points for encountering this monster
    int (*move_monster)(monster *m, maze *mze); ///< Function pointer for movement logic
};

/**
 * @brief Creates a generic monster with specified properties.
 * 
 * @param x The initial x-coordinate of the monster.
 * @param y The initial y-coordinate of the monster.
 * @param type The type of the monster (e.g., ghost or ogre).
 * @param penalty The penalty associated with the monster.
 * @param move_monster Pointer to the function handling monster movement.
 * 
 * @return A pointer to the newly created monster.
 */
monster* create_monster(int x, int y, int type, int penalty, int (*move_monster)(monster *m, maze *mze));

/**
 * @brief Creates a ghost-type monster.
 * 
 * @param x The initial x-coordinate of the ghost.
 * @param y The initial y-coordinate of the ghost.
 * 
 * @return A pointer to the created ghost monster.
 */
monster* create_ghost(int x, int y);

/**
 * @brief Creates an ogre-type monster.
 * 
 * @param x The initial x-coordinate of the ogre.
 * @param y The initial y-coordinate of the ogre.
 * 
 * @return A pointer to the created ogre monster.
 */
monster* create_ogre(int x, int y);

/**
 * @brief Places monsters randomly within the maze.
 * 
 * @param m Pointer to the maze where monsters will be placed.
 */
void place_monsters(maze *m);

/**
 * @brief Displays all monsters within the view window of the maze.
 * 
 * @param m Pointer to the maze.
 * @param w The window where monsters are displayed.
 * @param offset_x Horizontal offset for displaying within view.
 * @param offset_y Vertical offset for displaying within view.
 * @param view_width Width of the viewable area.
 * @param view_height Height of the viewable area.
 */
void display_monsters(maze *m, WINDOW* w, int offset_x, int offset_y, int view_width, int view_height);

/**
 * @brief Moves a ghost randomly within the maze.
 * 
 * @param m Pointer to the ghost monster to be moved.
 * @param mze Pointer to the maze.
 * 
 * @return The type identifier for the ghost.
 */
int move_ghost(monster *m, maze *mze);

/**
 * @brief Moves an ogre within the maze, avoiding walls.
 * 
 * @param m Pointer to the ogre monster to be moved.
 * @param mze Pointer to the maze.
 * 
 * @return The type identifier for the ogre.
 */
int move_ogre(monster *m, maze *mze);

/**
 * @brief Moves all monsters in the maze according to their specific movement behavior.
 * 
 * @param m Pointer to the maze where monsters reside.
 */
void move_monsters(maze *m);

/**
 * @brief Loads appropriate movement functions for each monster based on its type.
 * 
 * @param m Pointer to the maze containing the monsters.
 */
void load_monster_functions(maze *m);

/**
 * @brief Frees memory allocated for all monsters in the maze.
 * 
 * @param m Pointer to the maze from which monsters will be destroyed.
 */
void destroy_monsters(maze *m);

#endif
