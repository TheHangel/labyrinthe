#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "monster.h"
#include "maze.h"

void place_monsters(maze *m) {
    m->n_monsters = 2;
    m->monsters = (monster*) malloc(m->n_monsters * sizeof(monster));
    m->monsters[0].x = 2;
    m->monsters[0].y = 2;
    m->monsters[0].type = M_GHOST;
    m->monsters[0].move_monster = move_ghost;
    m->monsters[1].x = 1;
    m->monsters[1].y = 1;
    m->monsters[1].type = M_OGRE;
    m->monsters[1].move_monster = move_ogre;
}

void display_monsters(maze *m, WINDOW* w) {
    for (int k = 0; k < m->n_monsters; k++) {
        monster *mon = &m->monsters[k];
        int color_pair = (mon->type == M_GHOST) ? -(M_GHOST) : -(M_OGRE);

        wattron(w, COLOR_PAIR(color_pair));
        mvwprintw(w, mon->y + 1, mon->x * 2 + 1, "  ");
        wattroff(w, COLOR_PAIR(color_pair));
    }
}

int move_ghost(int x, int y) {
    return M_GHOST;
}

int move_ogre(int x, int y) {
    return M_OGRE;
}
