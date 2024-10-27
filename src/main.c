#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <string.h>
#include "maze.h"

void draw_borders(WINDOW *win) {
    box(win, 0, 0);
}

int main(void) {
    init_labyrinthe();
    time_t seed = time(NULL);
    srand(seed);
    int l = 17;
    int w = 35;
    maze *m = new_maze(l, w);
    if (m == NULL) return exit_labyrinthe(EXIT_FAILURE);

    generate_maze(m);

    int height, width;
    getmaxyx(stdscr, height, width);

    WINDOW *title_win = newwin(3, width, 0, 0);
    WINDOW *game_win = newwin(height - 10, width, 3, 0);
    WINDOW *player_data_win = newwin(3, width, height - 7, 0);
    WINDOW *placeholder_win = newwin(3, width, height - 3, 0);

    int has_moved = 1;
    while (1) {
        char c = getch();
        if (c == ESCAPE_KEY) {
            break;
        }

        direction d = get_direction_from_input(c);
        if (d != INVALID) {
            int old_x = m->player->x;
            int old_y = m->player->y;
            move_player(m, d);
            has_moved = (old_x != m->player->x || old_y != m->player->y);
        }

        if (has_moved) {
            mvwprintw(title_win, 1, (width - 10) / 2, "Labyrinthe");
            draw_borders(title_win);
            wrefresh(title_win);

            wclear(game_win);
            display(m, game_win);
            draw_borders(game_win);
            wrefresh(game_win);

            wclear(player_data_win);
            display_player_data(m->player, player_data_win);
            draw_borders(player_data_win);
            wrefresh(player_data_win);

            mvwprintw(placeholder_win, 1, 1, "Placeholder text");
            draw_borders(placeholder_win);
            wrefresh(placeholder_win);

            has_moved = 0;
        }

        if (check_player_pos(m)) break;
    }

    if (m->player->exited) {
        int win_height = 7;
        int win_width = 25;
        int starty = (height - win_height) / 2;
        int startx = (width - win_width) / 2;

        WINDOW *popup_win = newwin(win_height, win_width, starty, startx);

        box(popup_win, 0, 0);

        mvwprintw(popup_win, 1, (win_width - strlen("YOU WIN!")) / 2, "YOU WIN!");

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

    return exit_labyrinthe(EXIT_SUCCESS);
}
