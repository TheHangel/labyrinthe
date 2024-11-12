#ifndef MESSAGES_H
#define MESSAGES_H

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
 * @file messages.h
 * @brief Contains all message and label definitions for game UI.
 * 
 * @version 1.0.0
 * @date November 15, 2024
 * 
 * @details This file centralizes the UI messages and labels used throughout the game.
 * Constants for menu options, game notifications, and instructions are defined here.
 */

/**
 * @brief Macro to convert a value to a string.
 */
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

// Main Menu Options
#define BTN_PLAY               "Play"                      ///< Play button label
#define BTN_HOW_TO_PLAY        "How to play"               ///< How to play button label
#define BTN_HOW_TO_PLAY_DIALOG "Use ZQSD to move. Press ESC to quit." ///< How to play instructions
#define BTN_QUIT_GAME          "Quit game"                 ///< Quit game button label

// End Game Messages
#define MSG_NEW_HIGH_SCORE     "NEW HIGH SCORE!"           ///< Displayed when a high score is achieved
#define MSG_YOU_WIN            "YOU WIN!"                  ///< Displayed upon winning

#define LABEL_ENTER_NAME       "Enter your name: "         ///< Prompt for player name input

// End Game Options
#define BTN_DISPLAY_LEADERBOARD "Display Leaderboard"      ///< Button label to view leaderboard
#define BTN_QUIT_TO_MAIN_MENU   "Quit to Main Menu"        ///< Button label to return to main menu

// Maze Creation and Selection Labels
#define LABEL_NAME              "Name:"                    ///< Label for maze name input
#define LABEL_LENGTH            "Length:"                  ///< Label for maze length input
#define LABEL_WIDTH             "Width:"                   ///< Label for maze width input
#define BTN_CREATE_MAZE         "Create maze"              ///< Button to create a new maze
#define BTN_BACK                "Back"                     ///< Button to go back in menu

// Error Messages
#define MSG_CANNOT_LOAD_MAZE    "Cannot load maze file."   ///< Error message when maze file cannot be loaded
#define MSG_INVALID_DIMENSIONS  "Invalid Dimensions."      ///< Error message for invalid dimensions
#define MSG_INVALID_NAME        "Invalid Name."            ///< Error message for invalid name
#define MSG_DIMENSIONS_TOO_LOW  "Dimensions must be greater or equal to " TOSTRING(MIN_SIZE) "." ///< Message for dimensions too low
#define MSG_DIMENSIONS_TOO_HIGH "Dimensions must be less or equal to "    TOSTRING(MAX_SIZE) "." ///< Message for dimensions too high

// Leaderboard Labels
#define LABEL_LEADERBOARD       "Leaderboard"              ///< Leaderboard title
#define LABEL_PLAYERS           "Players"                  ///< Column label for player names
#define LABEL_SCORE             "Score"                    ///< Column label for scores
#define LABEL_OK                "OK"                       ///< OK button label

#endif
