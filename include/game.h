#ifndef GAME_H
#define GAME_H

typedef struct player player;
typedef struct monster monster;
typedef struct maze maze;
typedef struct leaderboard leaderboard;

typedef int cell;
typedef int checkbox;
typedef char* extension;

extern int height;
extern int width;

#define MIN_SIZE    5
#define MAX_SIZE 1024

#define MAX_INPUT_TEXTBOX 50
#define MAX_INPUT_PLAYER  20

#define PLAYER   10
#define PATH      0
#define WALL     -1
#define KEY      -2
#define TREASURE -3
#define TRAP     -4
#define EXIT     -5
#define M_GHOST  -6
#define M_OGRE   -7

#define ESCAPE_KEY 27
#define ENTER_KEY  10

#define GO_BACK (maze*) -1

#define IS_VALID_CHAR(ch) ((ch) >= 32 && (ch) <= 126)

typedef enum {
    NORMAL,
    HARD
} difficulty;

// Main menu window
enum main_menu_options {
    MAIN_PLAY,
    MAIN_DISPLAY_LEADERBOARD,
    MAIN_HOW_TO_PLAY,
    MAIN_QUIT
};

// End game window
enum end_game_options {
    END_DISPLAY_LEADERBOARD,
    END_QUIT_MAIN_MENU,
    END_QUIT_GAME
};

enum create_menu_options {
    CREATE_INPUT_NAME,
    CREATE_INPUT_LENGTH,
    CREATE_INPUT_WIDTH,
    CREATE_CHECKBOX_DIFFICULTY,
    CREATE_BTN_CONFIRM
};

// Maze selection mode
typedef enum {
    CREATE_MAZE_MODE,
    VIEW_LEADERBOARD_MODE
} maze_selection_mode;

#endif
