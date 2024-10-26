#define WALL   '#'
#define PATH   ' '
#define PLAYER 'o'
#define EXIT   '-'

#define KEY      '+'
#define TREASURE 'T'
#define TRAP     '*'

typedef struct {
    int x;
    int y;
    int moves;
    int score;
    int has_key;
} player;

typedef struct {
    char symbol;
    int id;
} cell;

typedef struct {
    cell **content;
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

cell* wall();
void brick_maze(maze *m);
void drill_maze(maze *m);
int move_player(maze *m, direction dir);
void display_player_debug(player p);
void remove_cell(maze *m, int x, int y);
int is_player_at_exit(maze m);
int is_player_on_key(maze m);
int is_player_on_treasure(maze m);
int is_player_on_trap(maze m);
void generate_maze(maze *m);
maze* new_maze(int length, int width);
void destroy_maze(maze *m);
void display(maze m);
void display_debug(maze m);
