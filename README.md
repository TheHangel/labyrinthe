# Author
Thibaud Lebrasseur <thibaud.lebrasseur@ecole.ensicaen.fr>

# Labyrinthe

This project is a maze-based adventure game implemented in C with various gameplay elements with bonus and traps, key to find, monster encounters, and leaderboard tracking. The game utilizes `ncurses` for the user interface, and `MinUnit` is used for unit testing the different modules.

## Project Structure

- **include/** : Contains header files for different components.
  - `_memory_.h` : Header file for managing memory allocations.
  - `display.h` : Header file for display functions using `ncurses`.
  - `file.h` : Header file for file handling and save/load operations.
  - `input.h` : Header file for handling player input.
  - `leaderboard.h` : Header file for leaderboard management.
  - `maze.h` : Header file for maze generation and manipulation.
  - `monster.h` : Header file for monster management.
  - `player.h` : Header file for player attributes and actions.
  - `game.h` : Header file defining constants and shared structures.
  - `messages.h` : Header file for text labels and messages in the game.

- **src/** : Source files for the main program and game mechanics.
  - `display.c` : Contains display functions for rendering the game screen.
  - `file.c` : Implementation of file handling functions for saving and loading.
  - `input.c` : Functions for interpreting and processing user input.
  - `leaderboard.c` : Implementation of leaderboard functions to store and display player scores.
  - `maze.c` : Maze generation and manipulation functions.
  - `memory.c` : Functions for managing memory allocations.
  - `monster.c` : Functions for managing monster behavior in the maze.
  - `player.c` : Functions for managing player actions and attributes.
  - `main.c` : Main file to run the game application.

- **src/test/** : Contains unit tests using MinUnit.
  - `tests.c` : Unit tests for maze, player, monster, and leaderboard modules.

- **Makefile** : Instructions for building the game and running tests.

- **README.md** : Documentation for the project.

# Build Instructions for the Project

## Building the Game

To compile the main game program, use the following command:

```bash
make
```

The final executable is located in bin/app.

## Running Tests

To compile and run the tests, use the following command:

```bash
make tests
```

This will compile the test files from the test/ directory and the necessary source files into an executable located in bin/tests.

## Get the documentation

To get the documentation, use the following command:

```bash
make doc
```

This will compile a documentation in the doc/ directory. To display the documentation, run doc/index.html in your browser.

## Cleaning Up

To remove all object files and compiled binaries, use:

```bash
make clean
```

This will delete all .o files and the final executables from the bin/ directory.
