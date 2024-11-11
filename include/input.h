#ifndef INPUT_H
#define INPUT_H

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    INVALID
} direction;

direction get_direction_from_input(char key);

#endif
