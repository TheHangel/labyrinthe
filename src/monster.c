#include <stdlib.h>
#include <ncurses.h>
#include "monster.h"
#include "maze.h"

monster* create_monster(int x, int y, int type, int penalty, int (*move_monster)(monster *m, maze *mze)) {
    monster *m = malloc(sizeof(monster));
    m->x = x;
    m->y = y;
    m->type = type;
    m->penalty = penalty;
    m->move_monster = move_monster;
    return m;
}

monster* create_ghost(int x, int y) {
    return create_monster(x, y, M_GHOST, 1, move_ghost);
}

monster* create_ogre(int x, int y) {
    return create_monster(x, y, M_OGRE, 2, move_ogre);
}

void place_monsters(maze *m) {
    m->n_monsters = (m->width * m->length) / 200;
    if (m->n_monsters < 1) m->n_monsters = 1;

    m->monsters = (monster*) malloc(m->n_monsters * sizeof(monster));

    for (int i = 0; i < m->n_monsters; i++) {
        cell* c = get_random_path(m);
        int x, y;
        get_coords_from_cell(m, c, &x, &y);

        if (rand() % 2 == 0) {
            *(m->monsters + i) = *create_ghost(x, y);
        } else {
            *(m->monsters + i) = *create_ogre(x, y);
        }
    }
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

int move_ghost(monster *m, maze *mze) {
    int dx = rand() % 3 - 1;
    int dy = rand() % 3 - 1;

    int new_x = m->x + dx;
    int new_y = m->y + dy;

    if (new_x >= 0 && new_x < mze->width && new_y >= 0 && new_y < mze->length) {
        m->x = new_x;
        m->y = new_y;
    }

    return M_GHOST;
}

int move_ogre(monster *m, maze *mze) {
    int dx = rand() % 3 - 1;
    int dy = rand() % 3 - 1;

    int new_x = m->x + dx;
    int new_y = m->y + dy;

    if (new_x >= 0 && new_x < mze->width && new_y >= 0 && new_y < mze->length) {
        if (mze->content[new_y][new_x] != WALL) {
            m->x = new_x;
            m->y = new_y;
        }
    }

    return M_OGRE;
}

void move_monsters(maze *m) {
    for (int k = 0; k < m->n_monsters; k++) {
        monster *mon = &m->monsters[k];
        mon->move_monster(mon, m);
    }
}

void destroy_monsters(maze *m) {
    free(m->monsters);
}