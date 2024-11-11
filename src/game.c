#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "game.h"
#include "maze.h"
#include "leaderboard.h"

int height = 0;
int width  = 0;

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
