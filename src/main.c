#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
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

    // Dimensions des fenêtres
    int height, width;
    getmaxyx(stdscr, height, width);

    WINDOW *title_win = newwin(3, width, 0, 0);
    WINDOW *game_win = newwin(height - 10, width, 3, 0);
    WINDOW *player_data_win = newwin(3, width, height - 7, 0);
    WINDOW *placeholder_win = newwin(3, width, height - 3, 0);

    // Affichage initial
    while (1) {
        // Nettoyage des fenêtres
        wclear(title_win);
        wclear(game_win);
        wclear(player_data_win);
        wclear(placeholder_win);

        // Titre
        mvwprintw(title_win, 1, (width - 10) / 2, "Labyrinthe");
        draw_borders(title_win);
        wrefresh(title_win);

        // Jeu
        display(m, game_win);
        mvwprintw(game_win, 0, 1, "Seed: %ld", seed);
        draw_borders(game_win);
        wrefresh(game_win);

        // Données du joueur
        display_player_data(m->player, player_data_win);
        draw_borders(player_data_win);
        wrefresh(player_data_win);

        // Placeholder
        mvwprintw(placeholder_win, 1, 1, "Placeholder text");
        draw_borders(placeholder_win);
        wrefresh(placeholder_win);

        if (check_player_pos(m)) break;

        char c = getch();
        if (c == ESCAPE_KEY) {
            break;
        }

        direction d = get_direction_from_input(c);
        if (d != INVALID) {
            move_player(m, d);
        }
    }

    if (m->player->exited) {
        mvprintw(height - 2, (width - 8) / 2, "YOU WIN!");
        wait_to_press_enter();
    }

    endwin();
    return exit_labyrinthe(EXIT_SUCCESS);
}
