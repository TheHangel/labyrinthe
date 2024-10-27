#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "game.h"
#include "maze.h"

void init_labyrinthe() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);

    timeout(100);

    start_color();

    init_pair(-(WALL),     0, COLOR_WHITE);
    init_pair(  PATH,      0, COLOR_BLACK);
    init_pair(-(KEY),      0, COLOR_YELLOW);
    init_pair(-(TREASURE), 0, COLOR_GREEN);
    init_pair(-(TRAP),     0, COLOR_RED);
    init_pair(-(EXIT),     0, COLOR_MAGENTA);

    init_pair(10, COLOR_WHITE, COLOR_CYAN);
}

int exit_labyrinthe(int code) {
    endwin();
    return code;
}

direction get_direction_from_input(char key) {
    switch (key) {
        case 'z':
        case 'Z':
            return UP;
        case 's':
        case 'S':
            return DOWN;
        case 'q':
        case 'Q':
            return LEFT;
        case 'd':
        case 'D':
            return RIGHT;
        default:
            return INVALID;
    }
}

void wait_to_press_enter(WINDOW* w) {
    int width = getmaxx(w);
    int start_col = (width - strlen("Press enter...")) / 2;

    mvwprintw(w, 3, start_col, "Press enter...");

    wrefresh(w);

    char c = 0;
    do {
        c = getch();
    } while(c != '\n' && c != '\r');
}

int menu_selection(WINDOW* w, const char *options[], int n_options) {
    int choice = 0;
    int ch;

    int menu_start_row = 3;

    while (1) {
        for (int i = 0; i < n_options; i++) {
            int width = getmaxx(w);
            int start_col = (width - strlen(options[i])) / 2;
            if (i == choice) {
                wattron(w, A_REVERSE);
                mvwprintw(w, menu_start_row + i, start_col, "%s", options[i]);
                wattroff(w, A_REVERSE);
            } else {
                mvwprintw(w, menu_start_row + i, start_col, "%s", options[i]);
            }
        }

        wrefresh(w);

        ch = getch();
        switch (ch) {
            case KEY_UP:
                choice = (choice == 0) ? n_options - 1 : choice - 1;
                break;
            case KEY_DOWN:
                choice = (choice == n_options - 1) ? 0 : choice + 1;
                break;
            case '\n':
                return choice;
        }
    }
}

void display_end_window(maze *m) {
    int height, width;
    getmaxyx(stdscr, height, width);

    int win_height = 7;
    int win_width = 25;
    int starty = (height - win_height) / 2;
    int startx = (width - win_width) / 2;

    WINDOW *popup_win = newwin(win_height, win_width, starty, startx);

    box(popup_win, 0, 0);

    mvwprintw(popup_win, 1, (win_width - strlen("YOU WIN!")) / 2, "YOU WIN!");

    player *p = m->player;
    int score = get_final_score(p);
    char *score_str = convert_score_to_string(score);

    mvwprintw(popup_win, 2, (win_width - strlen(score_str)) / 2, score_str);
    free(score_str);

    wrefresh(popup_win);

    const char *options[] = {
        "Play again",
        "Quit to Main Menu",
        "Quit game"
    };
    int n_options = sizeof(options) / sizeof(options[0]);

    menu_selection(popup_win, options, n_options);

    delwin(popup_win);
}
