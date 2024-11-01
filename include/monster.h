#ifndef MONSTER_H
#define MONSTER_H

#include "maze.h"

struct monster {
    int x;
    int y;
    int type;
    int (*move_monster)(int, int);
};

void place_monsters(maze *m);
void display_monsters(maze *m, WINDOW *w);
int move_ghost(int x, int y);
int move_ogre(int x, int y);

#endif
