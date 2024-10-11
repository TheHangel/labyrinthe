#define LENGTH 25
#define WIDTH  11

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