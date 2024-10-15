#define LENGTH 5
#define WIDTH  7

#define WALL   '#'
#define PATH   ' '
#define PLAYER 'o'
#define EXIT   '-'

typedef struct {
    char symbol;
    int id;
} box;

typedef struct {
    box content[LENGTH][WIDTH];
} maze;

box* wall();
void brick_maze(maze *m);
void drill_maze(maze *m);
void merge_paths(maze *m, int old_id, int new_id);
void open_wall(maze *m, int i, int j, int di, int dj);
int all_paths_connected(maze *m);
void generate_maze(maze *m);
maze* new_maze();
void destroy_maze(maze *m);
void display(maze m);
void display_debug(maze m);
