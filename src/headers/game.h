/*! Game declaration file */

#pragma once

#include "vector.h"
#include "player.h"
#include <stdbool.h>
#include <stdlib.h>

/** Forward declaration to avoid linking issues */
struct player;

/**
 * @struct game
 * @brief Represents the main game.
 */
struct game {
    /** Holds all the current players. */
    struct vector players;
};

/**
 * @brief Initializes game.
 * 
 * @param[in] initial_capacity Initial capacity to hold players.
 * @param[out] g Pointer to caller allocated game struct.
 * @return true if created successfully, false otherwise. 
 */
bool game_initialize(const unsigned int initial_capacity, struct game *g);
/**
 * @brief Adds a player into game.
 * 
 * @param[in] p Pointer to player struct.
 * @param[in] g Pointer to game struct.
 * @return true if success, false otherwise.
 */
bool game_insert_player(const struct player *p, struct game *g);
/**
 * @brief Removes a player from the game.
 * 
 * @param[in] p Pointer to player struct.
 * @param[in] g Pointer to game struct.
 * @return true if success, false otherwise.
 */
bool game_remove_player(const struct player *p, struct game *g);
/**
 * @brief Gets the game's winner.
 * 
 * @param[out] winner Pointer to caller allocated player struct.
 * @param[in] g Pointer to game struct.
 */
void game_get_winner(struct player *winner, const struct game *g);
/**
 * @brief Gets the total amount of current players.
 * 
 * @param[in] g Pointer to game struct.
 * @return Total amount of players.
 */
size_t game_get_total_players(const struct game *g);
/**
 * @brief Deinitializes game.
 * 
 * @param[in] g Pointer to game struct.
 */
void game_deinitialize(struct game *g);