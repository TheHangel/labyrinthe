#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <locale.h>
#include <string.h>
#include "display.h"
#include "game.h"
#include "maze.h"
#include "leaderboard.h"

#define MAX_INPUT 50

void init_curses() {
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    cbreak();
    curs_set(FALSE);
    keypad(stdscr, TRUE);

    timeout(100);

    start_color();

    // Colors
    init_pair(-(WALL),     0, COLOR_WHITE);
    init_pair(  PATH,      0, COLOR_BLACK);
    init_pair(-(KEY),      0, COLOR_YELLOW);
    init_pair(-(TREASURE), 0, COLOR_GREEN);
    init_pair(-(TRAP),     0, COLOR_RED);
    init_pair(-(EXIT),     0, COLOR_MAGENTA);
    init_pair(-(M_GHOST),  0, COLOR_BLUE);
    init_pair(-(M_OGRE),   0, COLOR_MAGENTA);

    // Player colors
    init_pair(PLAYER, COLOR_WHITE, COLOR_CYAN);
}

int destroy_curses() {
    return endwin();
}

void draw_borders(WINDOW *win) {
    box(win, 0, 0);
}

int menu_selection(WINDOW* w, const char *options[], int n_options, int menu_start_row) {
    int choice = 0;
    int ch;

    keypad(w, TRUE);

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

        ch = wgetch(w);
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

    int win_height = 10;
    int win_width = 35;
    int starty = (height - win_height) / 2;
    int startx = (width - win_width) / 2;

    WINDOW *popup_win = newwin(win_height, win_width, starty, startx);

    draw_borders(popup_win);

    player *p = m->player;
    int score = get_final_score(p);
    char *score_str = convert_score_to_string(score);

    mvwprintw(popup_win, 2, (win_width - strlen(score_str)) / 2, score_str);
    free(score_str);

    wrefresh(popup_win);

    leaderboard lb = load_leaderboard_from_file(LEADERBOARD_FILE);
    int last_score = lb.players[lb.count - 1].score;

    int is_winner = (score > last_score) || (lb.count < MAX_PLAYERS);
    const char *message = (is_winner) ? "NEW HIGH SCORE!" : "YOU WIN!";

    char name[20];

    if(is_winner) {
        mvwprintw(popup_win, 1, (win_width - strlen(message)) / 2, message);

        mvwprintw(popup_win, 4, 1, "Enter your name: ");
        echo();
        wgetnstr(popup_win, name, 20);
        noecho();

        add_player_to_leaderboard(&lb, name, score);
        sort_leaderboard(&lb);
        save_leaderboard_to_file(LEADERBOARD_FILE, &lb);

        werase(popup_win);
        draw_borders(popup_win);
        wrefresh(popup_win);
    }

    mvwprintw(popup_win, 1, (win_width - strlen(message)) / 2, message);

    const char *options[] = {
        "Play again",
        "Display Leaderboard",
        "Quit to Main Menu",
        "Quit game"
    };
    int n_options = 4;
    int menu_start_row = 4;

    int res = menu_selection(popup_win, options, n_options, menu_start_row);

    enum {
        PLAY_AGAIN,
        DISPLAY_LEADERBOARD,
        QUIT_MAIN_MENU,
        QUIT_GAME
    };

    switch (res) {
        case DISPLAY_LEADERBOARD: {
            WINDOW *lb_w = newwin(win_height*2, win_width, starty, startx);
            draw_borders(lb_w);
            display_leaderboard(lb_w, &lb, name);
            break;
        }

        default:
            break;
        }

    destroy_leaderboard(&lb);
    delwin(popup_win);
}

void display_game(maze *m) {
    int height, width;
    getmaxyx(stdscr, height, width);

    WINDOW *title_win = newwin(3, width, 0, 0);
    WINDOW *game_win = newwin(height - 10, width, 3, 0);
    WINDOW *player_data_win = newwin(3, width, height - 7, 0);

    int has_moved = 1;
    while (1) {
        char c = getch();
        if (c == ESCAPE_KEY) {
            break;
        }

        direction d = get_direction_from_input(c);
        if (d != INVALID) {
            has_moved = move_player(m, d);
        }

        if (has_moved) {
            move_monsters(m);
            if (check_player_pos(m)) break;

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

            has_moved = 0;
        }
    }

    if (m->player->exited) {
        display_end_window(m);
    }
}

void display_title(WINDOW *win) {
    const char *title[] = {
        "██╗      █████╗ ██████╗ ██╗   ██╗██████╗ ██╗███╗   ██╗████████╗██╗  ██╗███████╗",
        "██║     ██╔══██╗██╔══██╗╚██╗ ██╔╝██╔══██╗██║████╗  ██║╚══██╔══╝██║  ██║██╔════╝",
        "██║     ███████║██████╔╝ ╚████╔╝ ██████╔╝██║██╔██╗ ██║   ██║   ███████║█████╗",
        "██║     ██╔══██║██╔══██╗  ╚██╔╝  ██╔══██╗██║██║╚██╗██║   ██║   ██╔══██║██╔══╝",
        "███████╗██║  ██║██████╔╝   ██║   ██║  ██║██║██║ ╚████║   ██║   ██║  ██║███████╗",
        "╚══════╝╚═╝  ╚═╝╚═════╝    ╚═╝   ╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝   ╚═╝   ╚═╝  ╚═╝╚══════╝"
    };

    int start_row = 1;
    int width = getmaxx(win);

    for (int i = 0; i < 6; i++) {
        int start_col = (width / 2) - 38;
        mvwprintw(win, start_row + i, start_col, "%s", title[i]);
    }
    wrefresh(win);
}

void draw_textbox(WINDOW *win, int width, char *text) {
    box(win, 0, 0);
    mvwprintw(win, 1, 1, "%-*s", width - 2, text);
    wrefresh(win);
}

void draw_checkbox(WINDOW *win, int y, int x, int checked) {
    mvwprintw(win, y, x, "[%c] Difficile", checked ? 'X' : ' ');
    wrefresh(win);
}

void draw_button(WINDOW *win, int y, int x, char *label) {
    mvwprintw(win, y, x, "[ %s ]", label);
    wrefresh(win);
}

void display_message_window(const char *message) {
    int height, width;
    getmaxyx(stdscr, height, width);

    int win_height = 7;
    int win_width = strlen(message) + 6;
    if (win_width < 20) win_width = 20;

    int starty = (height - win_height) / 2;
    int startx = (width - win_width) / 2;

    WINDOW *msg_win = newwin(win_height, win_width, starty, startx);
    box(msg_win, 0, 0);

    mvwprintw(msg_win, 2, (win_width - strlen(message)) / 2, "%s", message);

    const char *button_label = "[ OK ]";
    mvwprintw(msg_win, 4, (win_width - strlen(button_label)) / 2, "%s", button_label);

    wrefresh(msg_win);

    int ch;
    while (1) {
        ch = getch();
        if (ch == '\n' || ch == 27) {
            break;
        }
    }

    delwin(msg_win);
    touchwin(stdscr);
    refresh();
}

maze *display_create_maze() {
    char input_length[MAX_INPUT] = "";
    char input_width[MAX_INPUT] = "";
    int checkbox_checked = 0;
    int choice = 0;

    WINDOW *textbox_length_win = newwin(3, 40, 5, 10);
    WINDOW *textbox_width_win = newwin(3, 40, 9, 10);
    WINDOW *checkbox_win = newwin(3, 20, 12, 10);
    WINDOW *button_win = newwin(3, 20, 15, 10);

    draw_textbox(textbox_length_win, 40, input_length);
    draw_textbox(textbox_width_win, 40, input_width);
    draw_checkbox(checkbox_win, 1, 1, checkbox_checked);
    draw_button(button_win, 1, 1, "Confirmer");

    int ch;
    int cursor_pos_length = 0, cursor_pos_width = 0;
    while (1) {
        ch = getch();
        switch (ch) {
            case KEY_UP:
                if (choice > 0) choice--;
                break;
            case KEY_DOWN:
                if (choice < 3) choice++;
                break;
            case ' ':
            case '\n':
                if (choice == 2) {
                    checkbox_checked = !checkbox_checked;
                    draw_checkbox(checkbox_win, 1, 1, checkbox_checked);
                } else if (choice == 3 && ch == '\n') { // Appuyer sur le bouton "Confirmer"
                    refresh();
                    int length = atoi(input_length);
                    int width = atoi(input_width);
                    if(length == 0 || width == 0) {
                        display_message_window("Les dimensions doivent être valides.");
                        break;
                    }
                    else if (length < 5 || width < 5) {
                        display_message_window("Les dimensions doivent être supérieures ou égales à 5.");
                        break;
                    }
                    if (length % 2 == 0) length++;
                    if (width % 2 == 0) width++;
                    difficulty d = checkbox_checked ? HARD : NORMAL;
                    maze *m = new_maze(length, width);
                    generate_maze(m, d);
                    return m;
                }
                break;
            case KEY_BACKSPACE:
            case 127:  // Pour certains terminaux, la touche backspace peut renvoyer 127
            case 8:    // Pour d'autres, c'est 8
                if (choice == 0 && cursor_pos_length > 0) {
                    input_length[--cursor_pos_length] = '\0';
                    draw_textbox(textbox_length_win, 40, input_length);
                } else if (choice == 1 && cursor_pos_width > 0) {
                    input_width[--cursor_pos_width] = '\0';
                    draw_textbox(textbox_width_win, 40, input_width);
                }
                break;
            default:
                if (ch >= 32 && ch <= 126) {
                    if (choice == 0 && cursor_pos_length < MAX_INPUT - 1) {
                        input_length[cursor_pos_length++] = ch;
                        input_length[cursor_pos_length] = '\0';
                        draw_textbox(textbox_length_win, 40, input_length);
                    } else if (choice == 1 && cursor_pos_width < MAX_INPUT - 1) {
                        input_width[cursor_pos_width++] = ch;
                        input_width[cursor_pos_width] = '\0';
                        draw_textbox(textbox_width_win, 40, input_width);
                    }
                }
                break;
        }

        if (choice == 0) {
            wattron(textbox_length_win, A_REVERSE);
            draw_textbox(textbox_length_win, 40, input_length);
            wattroff(textbox_length_win, A_REVERSE);
        } else {
            draw_textbox(textbox_length_win, 40, input_length);
        }

        if (choice == 1) {
            wattron(textbox_width_win, A_REVERSE);
            draw_textbox(textbox_width_win, 40, input_width);
            wattroff(textbox_width_win, A_REVERSE);
        } else {
            draw_textbox(textbox_width_win, 40, input_width);
        }

        if (choice == 2) {
            wattron(checkbox_win, A_REVERSE);
            draw_checkbox(checkbox_win, 1, 1, checkbox_checked);
            wattroff(checkbox_win, A_REVERSE);
        } else {
            draw_checkbox(checkbox_win, 1, 1, checkbox_checked);
        }

        if (choice == 3) {
            wattron(button_win, A_REVERSE);
            draw_button(button_win, 1, 1, "Confirmer");
            wattroff(button_win, A_REVERSE);
        } else {
            draw_button(button_win, 1, 1, "Confirmer");
        }
    }

    delwin(textbox_length_win);
    delwin(textbox_width_win);
    delwin(checkbox_win);
    delwin(button_win);
    return NULL;
}

maze *display_maze_selection() {
    int height, width;
    getmaxyx(stdscr, height, width);
    int win_height = 12;
    int win_width = 35;
    int starty = (height - win_height) / 2;
    int startx = (width - win_width) / 2;

    WINDOW *maze_win = newwin(win_height, win_width, starty, startx);
    draw_borders(maze_win);
    wrefresh(maze_win);

    int file_count;
    char **saves = list_saves_files("data/", &file_count);
    int menu_start_row_maze = (win_height - file_count - 1) / 2;

    const char *menu_options[file_count + 1];
    for (int i = 0; i < file_count; i++) {
        menu_options[i] = saves[i];
    }
    menu_options[file_count] = "Create maze";

    int res_maze = menu_selection(maze_win, menu_options, file_count + 1, menu_start_row_maze);

    maze *m = NULL;
    if (res_maze == file_count) {
        m = display_create_maze();
    } else {
        size_t total_length = strlen("data/") + strlen(saves[res_maze]) + strlen(".cfg") + 1;
        char *filename = malloc(total_length);

        strcpy(filename, "data/");
        strcat(filename, saves[res_maze]);
        strcat(filename, ".cfg");

        m = load_maze_from_file(filename);

        free(filename);
    }

    delwin(maze_win);
    for (int i = 0; i < file_count; i++) {
        free(saves[i]);
    }
    free(saves);

    return m;
}

void display_main_menu() {
    int height, width;
    getmaxyx(stdscr, height, width);
    WINDOW *win = newwin(height, width, 0, 0);
    draw_borders(win);

    display_title(win);

    int win_height = 10;
    int win_width = 35;
    int starty = (height - win_height) / 2;
    int startx = (width - win_width) / 2;

    WINDOW *sel_win = newwin(win_height, win_width, starty, startx);
    draw_borders(sel_win);

    wrefresh(sel_win);

    const char *options[] = { "Play", "How to play", "Quit" };
    int n_options = 3;

    int menu_start_row = (win_height - n_options) / 2;
    int selection = menu_selection(sel_win, options, n_options, menu_start_row);

    enum {
        PLAY,
        HOW_TO_PLAY,
        QUIT
    };

    switch (selection) {
        case PLAY: {
            maze *m = display_maze_selection();

            if(m == NULL) break;

            display_game(m);
            destroy_maze(m);
            break;
        }

        default:
            break;
    }

    delwin(win);
    delwin(sel_win);
    endwin();
}
