#include <stdlib.h>
#include <ncurses.h>
#include "monster.h"
#include "maze.h"
#include "_memory_.h"

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
            *(m->monsters + i) = *create_ghost(y, x);
        } else {
            *(m->monsters + i) = *create_ogre(y, x);
        }
    }
}

void display_monsters(maze *m, WINDOW* w, int offset_x, int offset_y, int view_width, int view_height) {
    for (int k = 0; k < m->n_monsters; k++) {
        monster *mon = &m->monsters[k];
        int monster_x = mon->y;
        int monster_y = mon->x;

        if (monster_y >= offset_y && monster_y < offset_y + view_height &&
            monster_x >= offset_x && monster_x < offset_x + view_width) {
            
            int color_pair = (mon->type == M_GHOST) ? -(M_GHOST) : -(M_OGRE);
            wattron(w, COLOR_PAIR(color_pair));
            mvwprintw(w, monster_y - offset_y + 1, (monster_x - offset_x) * 2 + 1, "  ");
            wattroff(w, COLOR_PAIR(color_pair));
        }
    }
}

int move_ghost(monster *m, maze *mze) {
    int dx = rand() % 3 - 1;
    int dy = rand() % 3 - 1;

    int new_x = m->x + dx;
    int new_y = m->y + dy;

    if (new_x >= 0 && new_y < mze->width && new_y >= 0 && new_x < mze->length) {
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

    if (new_x >= 0 && new_y < mze->width && new_y >= 0 && new_x < mze->length) {
        if (mze->content[new_x][new_y] != WALL) {
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

void load_monster_functions(maze *m) {
    for (int i = 0; i < m->n_monsters; i++) {
        if (m->monsters[i].type == M_GHOST) {
            m->monsters[i].move_monster = move_ghost;
        } else if (m->monsters[i].type == M_OGRE) {
            m->monsters[i].move_monster = move_ogre;
        }
    }
}

void destroy_monsters(maze *m) {
    free_and_reset((void*)m->monsters);
}
