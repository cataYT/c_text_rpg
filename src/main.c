/*! Main file */

#include "headers/player.h"
#include "headers/vector.h"
#include "headers/game.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

/**
 * @brief Used for getting user input.
 * 
 * @param[in] msg Message to display to user.
 * @param[in] size Size of the user input.
 * @param[out] buffer User allocated buffer to hold user input.
 */
void get_input(const char *msg, size_t size, char *buffer)
{
    printf("%s", msg);
    fflush(stdout);
    if (fgets(buffer, size, stdin)) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    } else {
        fprintf(stderr, "Error reading input.\n");
        buffer[0] = '\0';  // Clear buffer instead of buffer = NULL
    }
}

/**
 * @brief Parse string to unsigned int.
 * 
 * @param[in] str String to convert to unsigned int.
 * @param[out] out_val Pointer to unsigned int to store the value.
 * @return true if successful, false otherwise.
 */
bool parse_int(const char *str, unsigned int *out_val)
{
    if (!str || !out_val) return false;

    char *endptr;
    unsigned long val = strtoul(str, &endptr, 10);

    if (*endptr != '\0') return false;
    if (val > UINT_MAX) return false;

    *out_val = (unsigned int)val;
    return true;
}

/**
 * @brief Main function.
 * 
 * @return 0 on success, 1 otherwise. 
 */
int main(void)
{
    char p_name[100] = {'\0'};
    get_input("Enter your player name: ", sizeof(p_name), p_name);

    char w_name[100] = {'\0'};
    get_input("Enter weapon name: ", sizeof(w_name), w_name);

    char w_dmg_input[10] = {'\0'};
    get_input("Enter weapon damage: ", sizeof(w_dmg_input), w_dmg_input);

    unsigned int w_dmg = 0;

    if (!parse_int(w_dmg_input, &w_dmg)) {
        fprintf(stderr, "failed to parse weapon damage\n");
        return 1;
    }

    struct weapon first_weapon = {0};
    weapon_initialize(w_name, 100, w_dmg, &first_weapon);

    struct vector player_weapons = {0};
    vector_initialize(10, sizeof(struct weapon), &player_weapons);
    vector_push_back(&player_weapons, &first_weapon);

    struct armor basic_armor = {0};
    armor_initialize("BASIC", 10, 100, 1, &basic_armor);

    struct player cata = {0};
    player_initialize(p_name, 100, &player_weapons, &basic_armor, &cata);

    struct weapon sword = {0};
    weapon_initialize("Sword", 100, 10, &sword);

    struct vector enemy_weapons = {0};
    vector_initialize(10, sizeof(struct weapon), &enemy_weapons);
    vector_push_back(&enemy_weapons, &sword);

    struct player enemy = {0};
    player_initialize("enemy", 50, &enemy_weapons, &basic_armor, &enemy);

    struct game g = {0};
    game_initialize(2, &g);
    game_insert_player(&cata, &g);
    game_insert_player(&enemy, &g);

    player_attack(&enemy, "Sword", &cata);
    if (enemy.health == 0) {
        game_remove_player(&enemy, &g);
    }

    get_input("Enter the name of the weapon you want to use: ", sizeof(w_name), w_name);

    player_attack(&cata, w_name, &enemy);
    if (cata.health == 0) {
        game_remove_player(&cata, &g);
    }

    struct player winner = {0};
    game_get_winner(&winner, &g);
    if (winner.player_name) {
        printf("%s has won!\n", winner.player_name);
    } else {
        printf("No body won!\n");
    }

    weapon_deinitialize(&first_weapon);
    vector_deinitialize(&player_weapons);
    armor_deinitialize(&basic_armor);
    player_deinitialize(&cata);
    player_deinitialize(&enemy);
    weapon_deinitialize(&sword);
    vector_deinitialize(&enemy_weapons);
    game_deinitialize(&g);

    return 0;
}