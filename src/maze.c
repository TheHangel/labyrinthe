#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "maze.h"
#include "_memory_.h"
#include "monster.h"

void brick_maze(maze *m) {
    int length = m->length;
    int width = m->width;
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            m->content[i][j] = WALL;
        }
    }
}

void drill_maze(maze *m) {
    int length = m->length;
    int width = m->width;
    int id = 0;
    for (int i = 1; i < length; i += 2) {
        for (int j = 1; j < width; j += 2) {
            m->content[i][j] = id;
            id++;
        }
    }
}

void merge_paths(maze *m, int old_id, int new_id) {
    int length = m->length;
    int width = m->width;
    for (int i = 1; i < length; i++) {
        for (int j = 1; j < width; j++) {
            if (m->content[i][j] == old_id) {
                m->content[i][j] = new_id;
            }
        }
    }
}

void open_wall(maze *m, int i, int j, int di, int dj) {
    cell *current = &m->content[i][j];
    cell *next = &m->content[i + di][j + dj];

    if (*current != *next) {
        m->content[i + di / 2][j + dj / 2] = *current;
        merge_paths(m, *next, *current);
    }
}

int all_paths_connected(maze *m) {
    int length = m->length;
    int width = m->width;
    int first_id = m->content[1][1];

    for (int i = 1; i < length; i += 2) {
        for (int j = 1; j < width; j += 2) {
            if (m->content[i][j] != first_id) {
                return 0;
            }
        }
    }
    return 1;
}

cell* get_random_cell(maze *m, int (*condition)(int)) {
    int length = m->length;
    int width = m->width;
    int i = 0;
    int j = 0;
    do {
        i = rand() % length;
        j = rand() % width;
    } while (!condition(m->content[i][j]));
    return &m->content[i][j];
}

cell* get_random_path(maze *m) {
    return get_random_cell(m, is_path);
}

cell* get_random_wall(maze *m) {
    return get_random_cell(m, is_wall);
}

void get_coords_from_cell(maze *m, cell *c, int *x, int *y) {
    int length = m->length;
    int width = m->width;

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            if (&m->content[i][j] == c) {
                *y = i;
                *x = j;
                return;
            }
        }
    }
}

int is_path(cell cell) {
    return cell >= PATH;
}

int is_wall(cell cell) {
    return cell == WALL;
}

int is_wall_a_border(maze *m, cell *c) {
    int length = m->length;
    int width = m->width;

    int i, j;
    for (i = 0; i < length; i++) {
        for (j = 0; j < width; j++) {
            if (&m->content[i][j] == c) {
                return i == 0 || i == length - 1 || j == 0 || j == width - 1;
            }
        }
    }
    return 0;
}

void destroy_walls(maze *m, int n) {
    for (int i = 0; i < n; i++) {
        cell *c = get_random_wall(m);
        if(!is_wall_a_border(m, c)) {
            *c = PATH;
        }
    }
}

void place_exit(maze *m) {
    int length = m->length;
    int width = m->width;
    m->content[length - 1][width - 2] = EXIT;
}

void place_key(maze *m) {
    cell *key = get_random_path(m);
    *key = KEY;
}

void place_treasures(maze *m) {
    int size = m->length * m->width;
    for (int i = 0; i < size / 50; i++) {
        cell *c = get_random_path(m);
        *c = TREASURE;
    }
}

void place_traps(maze *m) {
    int size = m->length * m->width;
    for (int i = 0; i < size / 70; i++) {
        cell *c = get_random_path(m);
        *c = TRAP;
    }
}

void remove_cell(maze *m, int x, int y) {
    m->content[x][y] = PATH;
}

void generate_maze(maze *m, difficulty d) {
    int length = m->length;
    int width = m->width;
    int directions[4][2] = {{0, 2}, {0, -2}, {2, 0}, {-2, 0}};

    while (!all_paths_connected(m)) {
        int i = rand() % (length / 2) * 2 + 1;
        int j = rand() % (width / 2) * 2 + 1;
        int dir = rand() % 4;

        int ni = i + directions[dir][0];
        int nj = j + directions[dir][1];

        if (ni >= 1 && ni < length - 1 && nj >= 1 && nj < width - 1) {
            open_wall(m, i, j, directions[dir][0], directions[dir][1]);
        }
    }
    if(d == HARD) {
        destroy_walls(m, length * width / 10);
        place_monsters(m);
    }
    place_exit(m);
    place_key(m);
    place_treasures(m);
    place_traps(m);
}

maze* new_maze(char* name, int length, int width) {
    if(!(length % 2) || !(width % 2)) return NULL;
    maze* m = (maze*) malloc(sizeof(maze));
    m->name = malloc(strlen(name) + 1);
    if (!m->name) {
        free_and_reset((void**)&m);
        return NULL;
    }
    strcpy(m->name, name);
    m->length = length;
    m->width = width;
    m->content = (cell**) malloc(length * sizeof(cell*));
    for (int i = 0; i < length; i++) {
        m->content[i] = (cell*) malloc(width * sizeof(cell));
    }
    place_player(m);
    brick_maze(m);
    drill_maze(m);
    return m;
}

void destroy_cells(maze *m) {
    for (int i = 0; i < m->length; i++) {
        free_and_reset((void**)&m->content[i]);
    }
    free_and_reset((void**)&m->content);
}

void destroy_maze(maze *m) {
    destroy_cells(m);
    destroy_player(m);
    destroy_monsters(m);
    free_and_reset((void**)&m->name);
    free_and_reset((void**)&m);
}

void display(maze *m, WINDOW* w) {
    int height, width;
    getmaxyx(w, height, width);

    int view_height = height - 2;
    int view_width = (width - 2) / 2;

    if (view_height > m->length) view_height = m->length;
    if (view_width > m->width) view_width = m->width;

    player *p = m->player;
    int player_x = p->y;
    int player_y = p->x;

    int offset_y = player_y - view_height / 2;
    int offset_x = player_x - view_width / 2;

    if (offset_y < 0) offset_y = 0;
    if (offset_x < 0) offset_x = 0;
    if (offset_y + view_height > m->length) offset_y = m->length - view_height;
    if (offset_x + view_width > m->width) offset_x = m->width - view_width;

    for (int i = 0; i < view_height && (i + offset_y) < m->length; i++) {
        for (int j = 0; j < view_width && (j + offset_x) < m->width; j++) {
            int maze_y = i + offset_y;
            int maze_x = j + offset_x;

            if (is_player_at(*p, maze_y, maze_x)) {
                wattron(w, COLOR_PAIR(10));
                mvwprintw(w, i + 1, j * 2 + 1, "  ");
                wattroff(w, COLOR_PAIR(10));
                continue;
            }

            cell b = m->content[maze_y][maze_x];
            wattron(w, COLOR_PAIR(-(b)));
            mvwprintw(w, i + 1, j * 2 + 1, "  ");
            wattroff(w, COLOR_PAIR(-(b)));
        }
    }

    display_monsters(m, w, offset_x, offset_y, view_width, view_height);
}
