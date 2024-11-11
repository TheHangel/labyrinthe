#ifndef FILE_H
#define FILE_H

/*
 * ENSICAEN
 * 6 Boulevard Maréchal Juin
 * F-14050 Caen Cedex 
 * 
 * This file is owned by Thibaud Lebrasseur. No portion of this 
 * document may be reproduced, copied, or revised without written 
 * permission of the authors.
 */

/**
 * @file file.h
 * @brief File management functions and constants.
 * 
 * This header defines constants and functions for file operations in the
 * game, such as saving and loading mazes and leaderboards, as well as
 * managing directories and files.
 * 
 * @version 1.0.0
 * @date November 15, 2024
 * @details Functions in this file handle file path generation, file existence checks,
 * and reading/writing binary data for game data structures.
 */

/**
 * @brief Maximum number of files to handle within the directory.
 */
#define MAX_FILES 1024

/**
 * @brief Path to the directory where game data files are stored.
 */
#define DATA_PATH "data/"

/**
 * @brief File extension for maze configuration files.
 */
#define MAZE_EXTENSION ".cfg"

/**
 * @brief File extension for leaderboard score files.
 */
#define LEADERBOARD_EXTENSION ".score"

/**
 * @brief Initializes the data directory if it does not already exist.
 * 
 * Checks if the directory defined in DATA_PATH exists. If not, it attempts
 * to create it with the appropriate permissions.
 * 
 * @return int 0 on success, -1 if an error occurred while creating the directory.
 */
int init_saves();

/**
 * @brief Generates the full path for a maze file based on its name.
 * 
 * Constructs a full file path by appending the maze name and the maze file extension
 * to the DATA_PATH directory.
 * 
 * @param maze_name Name of the maze.
 * @return char* The complete path to the maze file.
 */
char* get_maze_path(char *maze_name);

/**
 * @brief Generates the full path for a leaderboard file based on the maze name.
 * 
 * Constructs a full file path by appending the maze name and the leaderboard file extension
 * to the DATA_PATH directory.
 * 
 * @param maze_name Name of the maze associated with the leaderboard.
 * @return char* The complete path to the leaderboard file.
 */
char* get_leaderboard_path(char *maze_name);

/**
 * @brief Lists all saved files in the specified directory with a given extension.
 * 
 * Reads the directory specified and returns a list of filenames that match the provided
 * file extension, excluding the extension in the output names.
 * 
 * @param directory Path to the directory to search.
 * @param file_count Pointer to an integer that will store the number of files found.
 * @param ext The file extension to filter by (e.g., ".cfg" or ".score").
 * @return char** Array of file names found, or NULL if no files match or an error occurred.
 */
char** list_saves_files(const char *directory, int *file_count, extension ext);

/**
 * @brief Saves the maze structure to a binary file.
 * 
 * Serializes the maze structure, including its name, dimensions, content, player, and monsters,
 * and writes it to a binary file.
 * 
 * @param filename Path to the file where the maze will be saved.
 * @param m Pointer to the maze structure.
 * @return int 0 on success, -1 on error.
 */
int save_maze_to_file(const char *filename, maze *m);

/**
 * @brief Loads a maze structure from a binary file.
 * 
 * Reads and deserializes the maze structure, including its name, dimensions, content, player, 
 * and monsters, from a binary file.
 * 
 * @param filename Path to the file to load the maze from.
 * @return maze* Pointer to the loaded maze structure, or NULL if loading fails.
 */
maze* load_maze_from_file(const char *filename);

/**
 * @brief Saves the leaderboard structure to a binary file.
 * 
 * Serializes the leaderboard structure, including player names and scores, and writes it to 
 * a binary file.
 * 
 * @param filename Path to the file where the leaderboard will be saved.
 * @param lb Pointer to the leaderboard structure.
 * @return int 0 on success, EXIT_FAILURE on error.
 */
int save_leaderboard_to_file(const char *filename, leaderboard *lb);

/**
 * @brief Loads a leaderboard structure from a binary file.
 * 
 * Reads and deserializes the leaderboard structure, including player names and scores, from 
 * a binary file.
 * 
 * @param filename Path to the file to load the leaderboard from.
 * @return leaderboard The loaded leaderboard structure.
 */
leaderboard load_leaderboard_from_file(const char *filename);

#endif
