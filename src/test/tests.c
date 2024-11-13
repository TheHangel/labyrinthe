/*
 * ENSICAEN
 * 6 Boulevard Maréchal Juin
 * F-14050 Caen Cedex 
 * 
 * This file is owned by ENSICAEN students. No portion of this 
 * document may be reproduced, copied or revised without written 
 * permission of the authors.
 */

/*
 * Testing the main functionalities of maze, player, monster, and leaderboard modules.
 * @author  Thibaud Lebrasseur
 * @version 1.0.0
 * @date    November 15, 2024
 */

#include <stdlib.h>

#include "minunit.h"
#include "game.h"
#include "maze.h"
#include "player.h"
#include "monster.h"
#include "_memory_.h"
#include "leaderboard.h"

#undef MINUNIT_EPSILON
#define MINUNIT_EPSILON 1E-2

int height = 0;
int width  = 0;

// Global variables for test setup
maze *test_maze;
leaderboard test_leaderboard;

void test_setup(void) {
    test_maze = new_maze("TestMaze", 11, 11);
}

void test_teardown(void) {
    destroy_maze(test_maze);
}

// Maze tests
MU_TEST(test_new_maze) {
    mu_check(test_maze != NULL);
    mu_assert_int_eq(test_maze->length, 11);
    mu_assert_int_eq(test_maze->width, 11);
}

MU_TEST(test_generate_maze) {
    generate_maze(test_maze, NORMAL);
    mu_check(test_maze->content[1][1] >= PATH);
}

MU_TEST(test_place_exit) {
    place_exit(test_maze);
    mu_check(test_maze->content[test_maze->length - 1][test_maze->width - 2] == EXIT);
}

// Player tests
MU_TEST(test_player_initialization) {
    place_player(test_maze);
    mu_check(test_maze->player != NULL);
    mu_assert_int_eq(test_maze->player->x, 0);
    mu_assert_int_eq(test_maze->player->y, 1);
}

MU_TEST(test_move_player) {
    place_player(test_maze);
    int moved = move_player(test_maze, DOWN);
    mu_assert_int_eq(moved, 1);
    mu_assert_int_eq(test_maze->player->x, 1);
}

MU_TEST(test_check_player_pos_key) {
    test_maze->content[1][1] = KEY;
    place_player(test_maze);
    test_maze->player->x = 1;
    test_maze->player->y = 1;
    int exited = check_player_pos(test_maze);
    mu_assert_int_eq(test_maze->player->has_key, 1);
    mu_assert_int_eq(exited, 0);
}

// Monster tests
MU_TEST(test_create_monster) {
    monster *ghost = create_ghost(1, 1);
    mu_check(ghost != NULL);
    mu_assert_int_eq(ghost->type, M_GHOST);
    free_and_reset((void*)ghost);
}

MU_TEST(test_move_monster) {
    monster *ogre = create_ogre(2, 2);
    test_maze->content[2][2] = PATH;
    int moved = ogre->move_monster(ogre, test_maze);
    mu_check(moved == M_OGRE);
    free_and_reset((void*)ogre);
}

MU_TEST(test_place_monsters) {
    place_monsters(test_maze);
    mu_check(test_maze->monsters != NULL);
}

// Leaderboard tests
MU_TEST(test_add_player_to_leaderboard) {
    test_leaderboard.count = 0;
    add_player_to_leaderboard(&test_leaderboard, "TestPlayer", 100);
    mu_assert_int_eq(test_leaderboard.count, 1);
    mu_check(strcmp(test_leaderboard.players[0].name, "TestPlayer") == 0);
}

MU_TEST(test_sort_leaderboard) {
    test_leaderboard.count = 2;
    test_leaderboard.players[0].name = strdup("Player1");
    test_leaderboard.players[0].score = 100;
    test_leaderboard.players[1].name = strdup("Player2");
    test_leaderboard.players[1].score = 200;
    sort_leaderboard(&test_leaderboard);
    mu_assert_int_eq(test_leaderboard.players[0].score, 200);
    mu_assert_int_eq(test_leaderboard.players[1].score, 100);
}

// Test suite
MU_TEST_SUITE(test_suite) {
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    MU_RUN_TEST(test_new_maze);
    MU_RUN_TEST(test_generate_maze);
    MU_RUN_TEST(test_place_exit);

    MU_RUN_TEST(test_player_initialization);
    MU_RUN_TEST(test_move_player);
    MU_RUN_TEST(test_check_player_pos_key);

    MU_RUN_TEST(test_create_monster);
    MU_RUN_TEST(test_move_monster);
    MU_RUN_TEST(test_place_monsters);

    MU_RUN_TEST(test_add_player_to_leaderboard);
    MU_RUN_TEST(test_sort_leaderboard);
}

int main(void) {
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}
