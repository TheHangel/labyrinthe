#include <ncurses.h>
#include <string.h>
#include "game.h"

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

int menu_selection(WINDOW* w) {
    // Options du menu
    const char *options[] = {
        "Play again",
        "Quit to Main Menu",
        "Quit game"
    };
    int n_options = sizeof(options) / sizeof(options[0]);
    int choice = 0;  // L'option sélectionnée (index)
    int ch;

    // Position de départ pour les options du menu, sous le texte "YOU WIN!"
    int menu_start_row = 3;

    // Affiche les options du menu
    while (1) {
        // Dessine uniquement les options du menu, sans effacer la fenêtre
        for (int i = 0; i < n_options; i++) {
            int width = getmaxx(w);
            int start_col = (width - strlen(options[i])) / 2;
            if (i == choice) {
                wattron(w, A_REVERSE);  // Inverse les couleurs pour montrer l'option sélectionnée
                mvwprintw(w, menu_start_row + i, start_col, "%s", options[i]);
                wattroff(w, A_REVERSE);
            } else {
                mvwprintw(w, menu_start_row + i, start_col, "%s", options[i]);
            }
        }

        wrefresh(w);

        // Récupère l'entrée de l'utilisateur
        ch = getch();
        switch (ch) {
            case KEY_UP:
                choice = (choice == 0) ? n_options - 1 : choice - 1;
                break;
            case KEY_DOWN:
                choice = (choice == n_options - 1) ? 0 : choice + 1;
                break;
            case '\n': // Appui sur Entrée
                return choice;
        }
    }
}
