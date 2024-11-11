#ifndef DISPLAY_H
#define DISPLAY_H

#include <ncurses.h>
#include "maze.h"

void init_display();
void update_size();
void draw_borders(WINDOW *win);
WINDOW* create_centered_window(int win_height, int win_width);
int menu_selection(WINDOW* w, const char *options[], int n_options, int menu_start_row);
void display_end_window(maze *m);
void display_game(maze *m);
void display_title(WINDOW *win);
void draw_textbox(WINDOW *win, int width, const char *label, char *text);
void draw_checkbox(WINDOW *win, int y, int x, int checked);
void draw_button(WINDOW *win, int y, int x, char *label);
void display_message_window(const char *message);
maze *display_create_maze();
maze *display_maze_selection(maze_selection_mode mode);
void display_main_menu();

#endif
