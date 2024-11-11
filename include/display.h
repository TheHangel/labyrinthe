#ifndef DISPLAY_H
#define DISPLAY_H

#include <ncurses.h>
#include "maze.h"

/*
 * ENSICAEN
 * 6 Boulevard Maréchal Juin
 * F-14050 Caen Cedex 
 * 
 * This file is owned by Thibaud Lebrasseur. No portion of this 
 * document may be reproduced, copied, or revised without written 
 * permission of the authors.
 */

/**
 * @file display.h
 * @brief Functions related to the game interface.
 * This header defines functions for initializing and managing the display
 * windows used in the game, such as the main menu, the game display, and
 * message dialog windows.
 * 
 * @version 1.0.0
 * @date November 15, 2024
 * 
 * @details Functions in this header rely on the ncurses library and 
 * are designed to create and manage windows for game interactions.
 */

/**
 * @brief Initializes the ncurses display settings and color pairs.
 * This function sets locale, initializes ncurses, and configures color pairs
 * for different elements in the game display.
 */
void init_display();

/**
 * @brief Updates the global terminal height and width based on the current terminal size.
 */
void update_size();

/**
 * @brief Draws a border around a specified window.
 * @param win The window on which to draw the border.
 */
void draw_borders(WINDOW *win);

/**
 * @brief Creates and centers a new window with specified dimensions.
 * @param win_height Height of the window.
 * @param win_width Width of the window.
 * @return WINDOW* Pointer to the newly created window.
 */
WINDOW* create_centered_window(int win_height, int win_width);

/**
 * @brief Displays a selection menu within a specified window.
 * @param w The window where the menu is displayed.
 * @param options An array of menu option strings.
 * @param n_options Number of options in the menu.
 * @param menu_start_row Starting row in the window for displaying menu options.
 * @return int Index of the selected menu option.
 */
int menu_selection(WINDOW* w, const char *options[], int n_options, int menu_start_row);

/**
 * @brief Displays the end game window with score and leaderboard options.
 * @param m The maze structure containing the player's information.
 */
void display_end_window(maze *m);

/**
 * @brief Displays the main game screen and manages player and monster movements.
 * @param m The maze structure containing the game's state.
 */
void display_game(maze *m);

/**
 * @brief Displays the game title in the specified window.
 * @param win The window where the title will be displayed.
 */
void display_title(WINDOW *win);

/**
 * @brief Draws an input textbox with a label and current text value.
 * @param win The window where the textbox will be drawn.
 * @param width Width of the textbox.
 * @param label Label displayed above the textbox.
 * @param text Pointer to the current text value.
 */
void draw_textbox(WINDOW *win, int width, const char *label, char *text);

/**
 * @brief Draws a checkbox in the specified window.
 * @param win The window where the checkbox will be drawn.
 * @param y Row position in the window for the checkbox.
 * @param x Column position in the window for the checkbox.
 * @param checked Boolean indicating if the checkbox is checked.
 */
void draw_checkbox(WINDOW *win, int y, int x, int checked);

/**
 * @brief Draws a button with a label in the specified window.
 * @param win The window where the button will be drawn.
 * @param y Row position in the window for the button.
 * @param x Column position in the window for the button.
 * @param label The text label displayed inside the button.
 */
void draw_button(WINDOW *win, int y, int x, char *label);

/**
 * @brief Displays a message window centered on the screen.
 * @param message The message string to display in the window.
 */
void display_message_window(const char *message);

/**
 * @brief Displays the window for creating a new maze and handles input for maze parameters.
 * @return maze* Pointer to the newly created maze structure.
 */
maze *display_create_maze();

/**
 * @brief Displays a menu to select a maze from saved files or return to the previous menu.
 * @param mode The mode for the maze selection (e.g., CREATE_MAZE_MODE, LEADERBOARD_MODE).
 * @return maze* Pointer to the selected or created maze, or a special value indicating to go back.
 */
maze *display_maze_selection(maze_selection_mode mode);

/**
 * @brief Displays the main menu and manages user selection of different game options.
 */
void display_main_menu();

#endif
