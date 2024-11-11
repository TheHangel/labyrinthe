#ifndef DISPLAY_H
#define DISPLAY_H

#include <ncurses.h>
#include "maze.h"

void init_curses();
void update_size();
void draw_borders(WINDOW *win);
WINDOW* create_centered_window(int win_height, int win_width);
int menu_selection(WINDOW* w, const char *options[], int n_options, int menu_start_row);
void display_end_window(maze *m);
void display_game(maze *m);
void display_title(WINDOW *win);
void display_main_menu();

#endif
