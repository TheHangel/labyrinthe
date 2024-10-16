#define LENGTH 9
#define WIDTH  17

#define WALL   '#'
#define PATH   '.'
#define PLAYER 'o'
#define EXIT   '-'

typedef struct {
    int x;
    int y;
} player;

typedef struct {
    char symbol;
    int id;
} box;

typedef struct {
    box **content;
    int length;
    int width;
    player *player;
} maze;

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    INVALID
} direction;

box* wall();
void brick_maze(maze *m);
void drill_maze(maze *m);
int move_player(maze *m, direction dir);
void show_player(player *p);
void generate_maze(maze *m);
maze* new_maze(int length, int width);
void destroy_maze(maze *m);
void display(maze m);
void display_debug(maze m);
