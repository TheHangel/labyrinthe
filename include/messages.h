#ifndef MESSAGES_H
#define MESSAGES_H

#include "game.h"

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

// Main menu
#define BTN_PLAY               "Play"
#define BTN_HOW_TO_PLAY        "How to play"
#define BTN_HOW_TO_PLAY_DIALOG "Use ZQSD to move. Press ESC to quit."
#define BTN_QUIT_GAME          "Quit game"

// End game window - Score
#define MSG_NEW_HIGH_SCORE     "NEW HIGH SCORE!"
#define MSG_YOU_WIN            "YOU WIN!"

#define LABEL_ENTER_NAME       "Enter your name: "

// End game window selection
#define BTN_DISPLAY_LEADERBOARD "Display Leaderboard"
#define BTN_QUIT_TO_MAIN_MENU   "Quit to Main Menu"

// Create maze window
#define LABEL_NAME              "Name:"
#define LABEL_LENGTH            "Length:"
#define LABEL_WIDTH             "Width:"

// Create maze and maze selection
#define BTN_CREATE_MAZE         "Create maze"

#define MSG_CANNOT_LOAD_MAZE    "Cannot load maze file."

// Create maze window messages
#define MSG_INVALID_DIMENSIONS  "Invalid Dimensions."
#define MSG_DIMENSIONS_TOO_LOW  "Dimensions must be greater or equal to " TOSTRING(MIN_SIZE) "."
#define MSG_DIMENSIONS_TOO_HIGH "Dimensions must be less or equal to "    TOSTRING(MAX_SIZE) "."

#endif
