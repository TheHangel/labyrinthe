#define LENGTH 5
#define WIDTH  7

#define WALL   '#'
#define PATH   ' '
#define PLAYER 'o'
#define EXIT   '-'

typedef struct {
    char symbol;
    unsigned int id;
} box;

typedef struct {
    box content[LENGTH][WIDTH];
} maze;

box* wall();
void brick_maze(maze *m);
void drill_maze(maze *m);
maze* new_maze();
void display(maze m);