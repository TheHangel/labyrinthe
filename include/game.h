#ifndef GAME_H
#define GAME_H

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
 * @file game.h
 * @brief Game constants, types, and enums for managing gameplay elements.
 * 
 * @version 1.0.0
 * @date November 15, 2024
 * @details Provides definitions for constants, data types, and 
 * enumerations used in the game, including player and maze attributes,
 * game modes, and input validation.
 */

/**
 * @typedef player
 * @brief Structure representing a player in the game.
 */
typedef struct player player;

/**
 * @typedef monster
 * @brief Structure representing a monster in the game.
 */
typedef struct monster monster;

/**
 * @typedef maze
 * @brief Structure representing the maze layout.
 */
typedef struct maze maze;

/**
 * @typedef leaderboard
 * @brief Structure representing the leaderboard for player scores.
 */
typedef struct leaderboard leaderboard;

/**
 * @typedef cell
 * @brief Represents a cell in the maze grid, indicating its type or status.
 */
typedef int cell;

/**
 * @typedef checkbox
 * @brief Represents the state of a checkbox (selected or not) in the UI.
 */
typedef int checkbox;

/**
 * @typedef extension
 * @brief Type for file extensions used in save/load operations.
 */
typedef char* extension;

/**
 * @brief Global screen dimensions for the game interface.
 */
extern int height; ///< Current height of the terminal screen.
extern int width;  ///< Current width of the terminal screen.

/**
 * @brief Minimum and maximum sizes for the maze.
 */
#define MIN_SIZE    5    ///< Minimum allowed size for maze dimensions.
#define MAX_SIZE 1024    ///< Maximum allowed size for maze dimensions.

/**
 * @brief Maximum character input limits for text fields.
 */
#define MAX_INPUT_TEXTBOX 50 ///< Max characters for general input textboxes.
#define MAX_INPUT_PLAYER  20 ///< Max characters for player name input.

/**
 * @brief Cell types representing the different elements in the maze.
 */
#define PLAYER   10     ///< Player character.
#define PATH      0     ///< Empty path cell.
#define WALL     -1     ///< Wall cell.
#define KEY      -2     ///< Key cell.
#define TREASURE -3     ///< Treasure cell.
#define TRAP     -4     ///< Trap cell.
#define EXIT     -5     ///< Exit cell.
#define M_GHOST  -6     ///< Ghost monster cell.
#define M_OGRE   -7     ///< Ogre monster cell.

/**
 * @brief Key codes for user input.
 */
#define ESCAPE_KEY 27   ///< Escape key code.
#define ENTER_KEY  10   ///< Enter key code.

/**
 * @brief Return value indicating a request to go back in the menu system.
 */
#define GO_BACK (maze*) -1

/**
 * @brief Check if a character is printable (standard ASCII range).
 * 
 * @param ch Character to validate.
 * @return 1 if the character is valid, 0 otherwise.
 */
#define IS_VALID_CHAR(ch) ((ch) >= 32 && (ch) <= 126)

/**
 * @enum difficulty
 * @brief Enumeration for selecting difficulty levels in the game.
 */
typedef enum {
    NORMAL, ///< Normal difficulty level: Perfect maze and no monsters.
    HARD    ///< Hard difficulty level: Unperfect maze and monsters.
} difficulty;

/**
 * @enum main_menu_options
 * @brief Menu options available in the main menu.
 */
enum main_menu_options {
    MAIN_PLAY,                 ///< Play.
    MAIN_DISPLAY_LEADERBOARD,  ///< Display leaderboard.
    MAIN_HOW_TO_PLAY,          ///< How to play.
    MAIN_QUIT                  ///< Quit game.
};

/**
 * @enum end_game_options
 * @brief Options available in the end game screen.
 */
enum end_game_options {
    END_DISPLAY_LEADERBOARD,   ///< Display leaderboard.
    END_QUIT_MAIN_MENU,        ///< Quit to main menu.
    END_QUIT_GAME              ///< Quit game.
};

/**
 * @enum create_menu_options
 * @brief Options for creating a maze, including inputs and buttons.
 */
enum create_menu_options {
    CREATE_INPUT_NAME,            ///< Input field for maze name.
    CREATE_INPUT_LENGTH,          ///< Input field for maze length.
    CREATE_INPUT_WIDTH,           ///< Input field for maze width.
    CREATE_CHECKBOX_DIFFICULTY,   ///< Checkbox to toggle difficulty.
    CREATE_BTN_CONFIRM            ///< Button to confirm maze creation.
};

/**
 * @enum maze_selection_mode
 * @brief Mode for maze selection, either to create a new maze or view the leaderboard.
 */
typedef enum {
    CREATE_MAZE_MODE,         ///< Mode to create a new maze.
    VIEW_LEADERBOARD_MODE     ///< Mode to view the leaderboard.
} maze_selection_mode;

#endif
