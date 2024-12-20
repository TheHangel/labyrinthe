#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <locale.h>
#include <string.h>
#include "display.h"
#include "game.h"
#include "input.h"
#include "maze.h"
#include "file.h"
#include "_memory_.h"
#include "leaderboard.h"
#include "messages.h"

void init_display() {
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    cbreak();
    curs_set(FALSE);
    keypad(stdscr, TRUE);

    timeout(100);
    set_escdelay(0);

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

    init_pair(11, COLOR_WHITE, COLOR_BLACK);

    update_size();
}

void update_size() {
    getmaxyx(stdscr, height, width);
}

void draw_borders(WINDOW *win) {
    box(win, 0, 0);
}

WINDOW* create_centered_window(int win_height, int win_width) {
    int starty = (height - win_height) / 2;
    int startx = (width - win_width) / 2;
    WINDOW* w = newwin(win_height, win_width, starty, startx);
    draw_borders(w);
    return w;
}

int menu_selection(WINDOW* w, const char *options[], int n_options, int menu_start_row) {
    int choice = 0;
    int ch;

    keypad(w, TRUE);

    while (TRUE) {
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
    int win_height = 10;
    int win_width = 35;

    char* filename = get_leaderboard_path(m->name);

    leaderboard lb = load_leaderboard_from_file(filename);

    player *p = m->player;
    int score = get_final_score(p);
    char *score_str = convert_score_to_string(score);

    int last_score = lb.players[lb.count - 1].score;
    int is_winner = (score > last_score) || (lb.count < MAX_PLAYERS);
    const char *message = (is_winner) ? MSG_NEW_HIGH_SCORE : MSG_YOU_WIN;

    char name[MAX_INPUT_PLAYER] = "";

    if (is_winner) {
        WINDOW *popup_win = create_centered_window(win_height, win_width);
        mvwprintw(popup_win, 2, (win_width - strlen(message)) / 2, "%s", message);
        mvwprintw(popup_win, 4, 1, LABEL_ENTER_NAME);
        echo();
        wgetnstr(popup_win, name, MAX_INPUT_PLAYER);
        noecho();

        add_player_to_leaderboard(&lb, name, score);
        sort_leaderboard(&lb);
        save_leaderboard_to_file(filename, &lb);

        werase(popup_win);
        draw_borders(popup_win);
        wrefresh(popup_win);
        delwin(popup_win);
    }

    free_and_reset((void**)&filename);
    free_and_reset((void**)&score_str);

    while (TRUE) {
        WINDOW *popup_win = create_centered_window(win_height, win_width);

        mvwprintw(popup_win, 2, (win_width - strlen(message)) / 2, "%s", message);
        const char *options[] = {
            BTN_DISPLAY_LEADERBOARD,
            BTN_QUIT_TO_MAIN_MENU,
            BTN_QUIT_GAME
        };
        int n_options = 3;
        int menu_start_row = 4;

        int res = menu_selection(popup_win, options, n_options, menu_start_row);

        switch (res) {
            case END_DISPLAY_LEADERBOARD: {
                display_leaderboard(&lb, name);
                break;
            }

            case END_QUIT_MAIN_MENU:
                delwin(popup_win);
                destroy_leaderboard(&lb);
                return;

            case END_QUIT_GAME:
                delwin(popup_win);
                destroy_leaderboard(&lb);
                endwin();
                exit(0);
        }

        delwin(popup_win);
    }

    destroy_leaderboard(&lb);
}

void display_game(maze *m) {
    WINDOW *title_win       = newwin(3, width, 0, 0);
    WINDOW *game_win        = newwin(height - 6, width, 3, 0);
    WINDOW *player_data_win = newwin(3, width, height - 3, 0);

    int has_moved = 1;
    int last_x = m->player->x, last_y = m->player->y;

    while (TRUE) {
        char c = getch();
        if (c == ESCAPE_KEY) {
            break;
        }

        direction d = get_direction_from_input(c);
        if (d != INVALID) {
            has_moved = move_player(m, d);
        }

        if (has_moved) {
            if(m->n_monsters > 0){
                move_monsters(m);
            }
            if (check_player_pos(m)) break;

            mvwprintw(title_win, 1, (width - strlen(m->name)) / 2, "%s", m->name);
            draw_borders(title_win);
            wrefresh(title_win);

            mvwprintw(game_win, last_y + 1, last_x * 2 + 1, "  ");
            display(m, game_win);
            draw_borders(game_win);
            wrefresh(game_win);

            last_x = m->player->x;
            last_y = m->player->y;

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

    for (int i = 0; i < 6; i++) {
        int start_col = (width / 2) - 38;
        mvwprintw(win, start_row + i, start_col, "%s", title[i]);
    }
    wrefresh(win);
}

void draw_textbox(WINDOW *win, int width, const char *label, char *text) {
    werase(win);
    box(win, 0, 0);

    wattron(win, COLOR_PAIR(11));

    mvwprintw(win, 0, 1, "%s", label);

    mvwprintw(win, 1, 1, "%-*s", width - 2, text);

    wattroff(win, COLOR_PAIR(11));

    wrefresh(win);
}

void draw_checkbox(WINDOW *win, int y, int x, int checked) {
    mvwprintw(win, y, x, "[%c] Hard Mode", checked ? 'X' : ' ');
    wrefresh(win);
}

void draw_button(WINDOW *win, int y, int x, char *label) {
    mvwprintw(win, y, x, "[ %s ]", label);
    wrefresh(win);
}

void display_message_window(const char *message) {
    int win_height = 7;
    int win_width = strlen(message) + 6;
    if (win_width < 20) win_width = 20;

    WINDOW *msg_win = create_centered_window(win_height, win_width);

    mvwprintw(msg_win, 2, (win_width - strlen(message)) / 2, "%s", message);

    mvwprintw(msg_win, 4, (win_width - strlen(LABEL_OK)) / 2, "%s", LABEL_OK);

    wrefresh(msg_win);

    int ch;
    while (TRUE) {
        ch = wgetch(msg_win);
        if (ch == '\n' || ch == ESCAPE_KEY) {
            break;
        }
    }

    delwin(msg_win);
    touchwin(stdscr);
}

maze *display_create_maze() {
    int win_height = 20;
    int win_width = 50;

    WINDOW *center_win = create_centered_window(win_height, win_width);

    keypad(center_win, TRUE);

    char input_name  [MAX_INPUT_TEXTBOX] = "";
    char input_length[MAX_INPUT_TEXTBOX] = "";
    char input_width [MAX_INPUT_TEXTBOX] = "";
    checkbox hard_mode = 0;
    int choice = 0;

    WINDOW *textbox_name_win   = derwin(center_win, 3, win_width - 2, 2,  1);
    WINDOW *textbox_length_win = derwin(center_win, 3, win_width - 2, 6,  1);
    WINDOW *textbox_width_win  = derwin(center_win, 3, win_width - 2, 10, 1);
    WINDOW *checkbox_win       = derwin(center_win, 3, win_width - 2, 14, 1);
    WINDOW *button_win         = derwin(center_win, 3, win_width - 2, 16, 1);

    draw_textbox(textbox_name_win,   win_width - 4, LABEL_NAME,   input_name  );
    draw_textbox(textbox_length_win, win_width - 4, LABEL_LENGTH, input_length);
    draw_textbox(textbox_width_win,  win_width - 4, LABEL_WIDTH, input_width );
    draw_checkbox(checkbox_win, 1, 1, hard_mode);
    draw_button(button_win, 1, 1, BTN_CREATE_MAZE);

    int ch;
    int cursor_pos_name = 0, cursor_pos_length = 0, cursor_pos_width = 0;
    while (TRUE) {
        ch = wgetch(center_win);
        switch (ch) {
            case ESCAPE_KEY:
                delwin(textbox_name_win);
                delwin(textbox_length_win);
                delwin(textbox_width_win);
                delwin(checkbox_win);
                delwin(button_win);
                delwin(center_win);
                return GO_BACK;
            case KEY_UP:
                if (choice > CREATE_INPUT_NAME) choice--;
                break;
            case KEY_DOWN:
                if (choice < CREATE_BTN_CONFIRM) choice++;
                break;
            case ' ':
            case '\n':
                if (choice == CREATE_CHECKBOX_DIFFICULTY) {
                    hard_mode = !hard_mode;
                    draw_checkbox(checkbox_win, 1, 1, hard_mode);
                }
                else if (choice == CREATE_BTN_CONFIRM && ch == '\n') {
                    int length = atoi(input_length);
                    int width = atoi(input_width);
                    if (length == 0 || width == 0) {
                        display_message_window(MSG_INVALID_DIMENSIONS);
                    } else if (length < MIN_SIZE || width < MIN_SIZE) {
                        display_message_window(MSG_DIMENSIONS_TOO_LOW);
                    } else if (length > MAX_SIZE || width > MAX_SIZE) {
                        display_message_window(MSG_DIMENSIONS_TOO_HIGH);
                    } else if (!strlen(input_name)) {
                        display_message_window(MSG_INVALID_NAME);
                    } else {
                        refresh();
                        if (length % 2 == 0) length++;
                        if (width % 2 == 0) width++;
                        difficulty d = hard_mode ? HARD : NORMAL;
                        maze *m = new_maze(input_name, length, width);
                        generate_maze(m, d);
                        delwin(center_win);
                        char* filename = get_maze_path(m->name);
                        save_maze_to_file(filename, m);
                        free_and_reset((void**)&filename);
                        return m;
                    }

                    werase(center_win);
                    draw_borders(center_win);
                    draw_textbox(textbox_name_win, win_width - 4, LABEL_NAME, input_name);
                    draw_textbox(textbox_length_win, win_width - 4, LABEL_LENGTH, input_length);
                    draw_textbox(textbox_width_win, win_width - 4, LABEL_WIDTH, input_width);
                    draw_checkbox(checkbox_win, 1, 1, hard_mode);
                    draw_button(button_win, 1, 1, BTN_CREATE_MAZE);
                    wrefresh(center_win);
                }
                break;
            case KEY_BACKSPACE:
            case 127:
            case 8:
                if (choice == CREATE_INPUT_NAME && cursor_pos_name > 0) {
                    input_name[--cursor_pos_name] = '\0';
                    draw_textbox(textbox_name_win, win_width - 4, LABEL_NAME, input_name);
                }
                else if (choice == CREATE_INPUT_LENGTH && cursor_pos_length > 0) {
                    input_length[--cursor_pos_length] = '\0';
                    draw_textbox(textbox_length_win, win_width - 4, LABEL_LENGTH, input_length);
                }
                else if (choice == CREATE_INPUT_WIDTH && cursor_pos_width > 0) {
                    input_width[--cursor_pos_width] = '\0';
                    draw_textbox(textbox_width_win, win_width - 4, LABEL_WIDTH, input_width);
                }
                break;
            default:
                if (IS_VALID_CHAR(ch)) {
                    if (choice == CREATE_INPUT_NAME && cursor_pos_name < MAX_INPUT_TEXTBOX - 1) {
                        input_name[cursor_pos_name++] = ch;
                        input_name[cursor_pos_name] = '\0';
                        draw_textbox(textbox_name_win, win_width - 4, LABEL_NAME, input_name);
                    }
                    else if (choice == CREATE_INPUT_LENGTH && cursor_pos_length < MAX_INPUT_TEXTBOX - 1) {
                        input_length[cursor_pos_length++] = ch;
                        input_length[cursor_pos_length] = '\0';
                        draw_textbox(textbox_length_win, win_width - 4, LABEL_LENGTH, input_length);
                    }
                    else if (choice == CREATE_INPUT_WIDTH && cursor_pos_width < MAX_INPUT_TEXTBOX - 1) {
                        input_width[cursor_pos_width++] = ch;
                        input_width[cursor_pos_width] = '\0';
                        draw_textbox(textbox_width_win, win_width - 4, LABEL_WIDTH, input_width);
                    }
                }
                break;
        }

        if (choice == CREATE_INPUT_NAME) {
            wattron(textbox_name_win, A_REVERSE);
            draw_textbox(textbox_name_win, win_width - 4, LABEL_NAME, input_name);
            wattroff(textbox_name_win, A_REVERSE);
        } else {
            draw_textbox(textbox_name_win, win_width - 4, LABEL_NAME, input_name);
        }

        if (choice == CREATE_INPUT_LENGTH) {
            wattron(textbox_length_win, A_REVERSE);
            draw_textbox(textbox_length_win, win_width - 4, LABEL_LENGTH, input_length);
            wattroff(textbox_length_win, A_REVERSE);
        } else {
            draw_textbox(textbox_length_win, win_width - 4, LABEL_LENGTH, input_length);
        }

        if (choice == CREATE_INPUT_WIDTH) {
            wattron(textbox_width_win, A_REVERSE);
            draw_textbox(textbox_width_win, win_width - 4, LABEL_WIDTH, input_width);
            wattroff(textbox_width_win, A_REVERSE);
        } else {
            draw_textbox(textbox_width_win, win_width - 4, LABEL_WIDTH, input_width);
        }

        if (choice == CREATE_CHECKBOX_DIFFICULTY) {
            wattron(checkbox_win, A_REVERSE);
            draw_checkbox(checkbox_win, 1, 1, hard_mode);
            wattroff(checkbox_win, A_REVERSE);
        } else {
            draw_checkbox(checkbox_win, 1, 1, hard_mode);
        }

        if (choice == CREATE_BTN_CONFIRM) {
            wattron(button_win, A_REVERSE);
            draw_button(button_win, 1, 1, BTN_CREATE_MAZE);
            wattroff(button_win, A_REVERSE);
        } else {
            draw_button(button_win, 1, 1, BTN_CREATE_MAZE);
        }
    }

    delwin(textbox_name_win);
    delwin(textbox_length_win);
    delwin(textbox_width_win);
    delwin(checkbox_win);
    delwin(button_win);
    delwin(center_win);
    return NULL;
}

maze *display_maze_selection(maze_selection_mode mode) {
    int win_width = 35;
    char *extension = (mode == CREATE_MAZE_MODE) ? MAZE_EXTENSION : LEADERBOARD_EXTENSION;

    int file_count;
    char **saves = list_saves_files(DATA_PATH, &file_count, extension);
    int win_height = file_count + 4;
    const int min_height = 12;
    if (win_height < min_height) win_height = min_height;

    WINDOW *maze_win = create_centered_window(win_height, win_width);

    int menu_start_row_maze = (win_height - file_count - 1) / 2;

    const char *last_option = (mode == CREATE_MAZE_MODE) ? BTN_CREATE_MAZE : BTN_BACK;
    const char *menu_options[file_count + 1];
    for (int i = 0; i < file_count; i++) {
        menu_options[i] = saves[i];
    }
    menu_options[file_count] = last_option;

    int res_maze = menu_selection(maze_win, menu_options, file_count + 1, menu_start_row_maze);
    delwin(maze_win);

    maze *m = NULL;
    if (res_maze == file_count) {
        if (mode == CREATE_MAZE_MODE) {
            m = display_create_maze();
            if (m == NULL) {
                for (int i = 0; i < file_count; i++) {
                    free_and_reset((void**)&saves[i]);
                }
                free_and_reset((void**)&saves);
                return GO_BACK;
            }
        } else {
            return GO_BACK;
        }
    } else {
        if (mode == CREATE_MAZE_MODE) {
            char *filename = get_maze_path(saves[res_maze]);
            m = load_maze_from_file(filename);
            free_and_reset((void**)&filename);
        } else {
            char *filename = get_leaderboard_path(saves[res_maze]);
            leaderboard lb = load_leaderboard_from_file(filename);

            display_leaderboard(&lb, "");
        }
    }

    for (int i = 0; i < file_count; i++) {
        free_and_reset((void**)&saves[i]);
    }
    free_and_reset((void**)&saves);

    return m;
}

void display_main_menu() {
    while (TRUE) {
        WINDOW *win = newwin(height, width, 0, 0);
        draw_borders(win);
        display_title(win);

        int win_height = 10;
        int win_width = 35;
        WINDOW *sel_win = create_centered_window(win_height, win_width);

        const char *options[] = {
            BTN_PLAY,
            BTN_DISPLAY_LEADERBOARD,
            BTN_HOW_TO_PLAY,
            BTN_QUIT_GAME
        };
        int n_options = 4;
        int menu_start_row = (win_height - n_options) / 2;
        int selection = menu_selection(sel_win, options, n_options, menu_start_row);

        switch (selection) {
            case MAIN_PLAY: {
                maze *m = display_maze_selection(CREATE_MAZE_MODE);

                if (m == GO_BACK) {
                    break;
                }

                if (m == NULL) {
                    display_message_window(MSG_CANNOT_LOAD_MAZE);
                    break;
                }

                display_game(m);
                destroy_maze(m);
                break;
            }

            case MAIN_DISPLAY_LEADERBOARD: {
                display_maze_selection(1);
                break;
            }

            case MAIN_HOW_TO_PLAY:
                display_message_window(BTN_HOW_TO_PLAY_DIALOG);
                break;

            case MAIN_QUIT:
                delwin(win);
                delwin(sel_win);
                return;
        }

        delwin(win);
        delwin(sel_win);
    }
}
