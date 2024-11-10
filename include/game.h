#ifndef GAME_H
#define GAME_H

typedef struct player player;
typedef struct monster monster;
typedef struct maze maze;
typedef struct leaderboard leaderboard;
typedef int cell;

#define MIN_SIZE 5
#define MAX_SIZE 1024

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

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    INVALID
} direction;

typedef enum {
    NORMAL,
    HARD
} difficulty;

// Main menu window
enum {
    PLAY,
    HOW_TO_PLAY,
    QUIT
};

// End game window
enum {
    DISPLAY_LEADERBOARD,
    QUIT_MAIN_MENU,
    QUIT_GAME
};

direction get_direction_from_input(char key);

#endif
