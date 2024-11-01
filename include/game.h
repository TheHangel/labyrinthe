#ifndef GAME_H
#define GAME_H

#include <ncurses.h>

typedef struct player player;
typedef struct monster monster;
typedef struct maze maze;
typedef struct leaderboard leaderboard;
typedef int cell;

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

void init_labyrinthe();
int exit_labyrinthe(int code);
direction get_direction_from_input(char key);
void wait_to_press_enter(WINDOW *w);
int menu_selection(WINDOW* w, const char *options[], int n_options);
void display_end_window(maze *m);

#endif
