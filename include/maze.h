#define PATH      0
#define WALL     -1
#define KEY      -2
#define TREASURE -3
#define TRAP     -4
#define EXIT     -5

typedef struct {
    int x;
    int y;
    int moves;
    int score;
    int has_key;
} player;

typedef struct {
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
void remove_cell_at_player(maze *m);
int is_player_at_exit(maze m);
int is_player_on_key(maze m);
int is_player_on_treasure(maze m);
int is_player_on_trap(maze m);
void generate_maze(maze *m);
maze* new_maze(int length, int width);
void destroy_maze(maze *m);
void display(maze m);
