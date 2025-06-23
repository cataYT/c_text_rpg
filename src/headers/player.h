/*! Player declaration file */

#pragma once

#include "weapon.h"
#include "game.h"
#include "vector.h"
#include "armor.h"
#include <stdbool.h>

/**
 * @struct player
 * @brief Represents player.
 */
struct player {
    /** Vector to hold weapons. */
    struct vector _weapons;
    /** Current armor used by player */
    struct armor current_armor;
    /** Player's name */
    char *player_name;
    /** Player's health */
    unsigned int health;
    /** Boolean to check if player is already wearing armor or not */
    bool _isWearingArmor;
};

/**
 * @brief Initializes player.
 * 
 * @param[in] name Name of the player.
 * @param[in] health Health of the player.
 * @param[in] weapons Vector of weapon.
 * @param[in] armor Vector of armor.
 * @param[out] p Pointer to caller allocated player struct to initialize.
 * @return true if success, false otherwise.
 */
bool player_initialize(const char *name, const unsigned int health, const struct vector *weapons, const struct armor *armor, struct player *p);
/**
 * @brief Gets the player's weapons.
 * 
 * @param[in] p Pointer to player struct.
 * @return Vector of weapons if success, NULL otherwise.
 */
const struct vector *player_get_weapons(const struct player *p);
/**
 * @brief Gets the player's armor.
 * 
 * @param[in] p Pointer to player struct.
 * @return Current armor of the player if success, NULL otherwise.
 */
const struct armor *player_get_armor(const struct player *p);
/**
 * @brief Prints the player's details.
 * 
 * @param[in] p Pointer to player struct.
 */
void player_get_stats(const struct player *p);
/**
 * @brief Updates the player weapons based on the type of operation.
 * 
 * @param[in] type Type of operation to perform, can only be add or remove.
 * @param[in] w Pointer to weapon struct to add or remove.
 * @param[in] p Pointer to player struct.
 */
void player_update_weapons(const char *type, const struct weapon *w, struct player *p);
/**
 * @brief Attacks another player by decreasing its health.
 * 
 * @param[in] attacker Pointer to player struct which is going to attack.
 * @param[in] weapon_name Weapon name to attack to. Must be owned by the attacker.
 * @param[in] target Pointer to player struct to attack.
 */
void player_attack(struct player *attacker, const char *weapon_name, struct player *target);
/**
 * @brief Heals the player by increasing its health.
 * 
 * @param[in] amount Amount to heal the player, cannot be 0.
 * @param[in] p Pointer to the player struct.
 */
void player_heal(const unsigned int amount, struct player *p);
/**
 * @brief Makes the player equip the armor.
 * 
 * @param[in] a Pointer to armor struct.
 * @param[in] p Pointer to player struct
 */
void player_equip_armor(const struct armor *a, struct player *p);
/**
 * @brief Adds players by combining stats of both the players.
 * 
 * @param[in] p1 Pointer to player struct to add to.
 * @param[in] p2 Pointer to player struct to add to.
 * @param[out] add_player Pointer to caller allocated player struct.
 */
void player_add_player(const struct player *p1, const struct player *p2, struct player *add_player);
/**
 * @brief Deinitializes player.
 * 
 * @param[in] p Pointer to player struct
 */
void player_deinitialize(struct player *p);