#ifndef MONSTER_H
#define MONSTER_H

#include "maze.h"

struct monster {
    int x;
    int y;
    int type;
    int penalty;
    int (*move_monster)(monster *m, maze *mze);
};

void place_monsters(maze *m);
void display_monsters(maze *m, WINDOW* w, int offset_x, int offset_y, int view_width, int view_height);
int move_ghost(monster *m, maze *mze);
int move_ogre(monster *m, maze *mze);
void move_monsters(maze *m);
void destroy_monsters(maze *m);

#endif
