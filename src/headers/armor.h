/*! Armor declaration file. */

#pragma once
#include <stdbool.h>

/**
 * @struct armor
 * @brief Represents armor used by players and enemies.
 */
struct armor {
    /** Armor's resistance force which dictates how much the player/enemy can reduce its damage */
    unsigned int _armor_resistance_force;
    /** Armor's health */
    unsigned int _armor_health;
    /** Armor's max health. */
    unsigned int _armor_max_health;

    /** Armor's name */
    char *armor_name;
};

/**
 * @brief Initializes armor.
 * 
 * @param[in] name Name of the armor.
 * @param[in] health Health of the armor. 
 * @param[in] max_health Max health of the armor.
 * @param[in] resistance_force Resistance force of the armor.
 * @param[out] a Pointer to a caller allocated armor struct to initialize.
 * @return true if armor created, false otherwise.
 */
bool armor_initialize(const char *name, const unsigned int health, const unsigned int max_health, const unsigned int resistance_force, struct armor *a);
/**
 * @brief Gets the armor's health.
 * 
 * @param[in] a Pointer to armor struct.
 * @return Armor's health if success, 0 otherwise.
 */
unsigned int armor_get_health(const struct armor *a);
/**
 * @brief Gets the armor's resistance force.
 * 
 * @param[in] a Pointer to armor struct.
 * @return Armor's resistance force, 0 otherwise. 
 */
unsigned int armor_get_resistance(const struct armor *a);
/**
 * @brief Enhances the armor by increasing its resistance force.
 * 
 * @param[in] new_resistance_force New resistance force to set the armor to. Cannot be less or equal to current armor resistance force.
 * @param[in,out] a Pointer to armor struct.
 */
void armor_enhance_armor(const unsigned int new_resistance_force, struct armor *a);
/**
 * @brief Repairs the armor by increasing its health.
 * 
 * @param[in] repair_amount Amount to increase the armor health by.
 * @param[in,out] a Pointer to armor struct.
 */
void armor_repair_armor(const unsigned int repair_amount, struct armor *a);
/**
 * @brief Prints all the details of armor.
 * 
 * @param[in] a Pointer to armor struct.
 */
void armor_print_stats(const struct armor *a);
/**
 * @brief Checks if both armors are equal.
 * 
 * @param[in] a1 Pointer to armor struct to compare to.
 * @param[in] a2 Pointer to armor struct to compare by.
 * @return true if both armors are equal, false otherwise.
 */
bool armor_is_equal(const struct armor *a1, const struct armor *a2);
/**
 * @brief Adds both armors by combining both armors stats.
 * 
 * @param[in] a1 Pointer to armor struct to add to.
 * @param[in] a2 Pointer to armor struct to add to.
 * @param[out] added_armor Pointer to caller allocated armor struct to hold the combined armor.
 */
void armor_add_armor(const struct armor *a1, const struct armor *a2, struct armor *added_armor);
/**
 * @brief Deinitializes the armor.
 * 
 * @param[in] a Pointer to armor struct.
 */
void armor_deinitialize(struct armor *a);