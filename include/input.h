#ifndef INPUT_H
#define INPUT_H

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
 * @file input.h
 * @brief Handling player input and converting it into directions.
 * 
 * @version 1.0.0
 * @date November 15, 2024
 * @details Defines direction enumerations and provides a function to interpret 
 * key inputs into movement directions.
 */

/**
 * @enum direction
 * @brief Enum representing possible movement directions.
 */
typedef enum {
    UP,      ///< Move upwards in the maze.
    DOWN,    ///< Move downwards in the maze.
    LEFT,    ///< Move left in the maze.
    RIGHT,   ///< Move right in the maze.
    INVALID  ///< Invalid input or no movement.
} direction;

/**
 * @brief Converts a character input into a direction.
 * 
 * @param key The character input received from the player (e.g., 'z', 's', 'q', 'd').
 * @return The corresponding direction (`UP`, `DOWN`, `LEFT`, `RIGHT`), or `INVALID` if the input is unrecognized.
 */
direction get_direction_from_input(char key);

#endif
