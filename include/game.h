#ifndef GAME_H
#define GAME_H

typedef struct player player;
typedef struct maze maze;
typedef int cell;

#define PATH      0
#define WALL     -1
#define KEY      -2
#define TREASURE -3
#define TRAP     -4
#define EXIT     -5

#define ESCAPE_KEY 27
#define ENTER_KEY  10

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    INVALID
} direction;

void init_labyrinthe();
int exit_labyrinthe(int code);
direction get_direction_from_input(char key);
void wait_to_press_enter(WINDOW *w);
int menu_selection(WINDOW* w, const char *options[], int n_options);
void display_end_window(maze *m);

#endif
