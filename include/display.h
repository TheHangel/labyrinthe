#ifndef DISPLAY_H
#define DISPLAY_H

#include <ncurses.h>
#include "maze.h"

void init_curses();
int destroy_curses();
void draw_borders(WINDOW *win);
int menu_selection(WINDOW* w, const char *options[], int n_options);
void display_end_window(maze *m);
void display_game(maze *m);

#endif
