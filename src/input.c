#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "game.h"
#include "input.h"
#include "maze.h"
#include "leaderboard.h"

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
