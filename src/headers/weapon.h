/*! Weapon declaration file */

#pragma once
#include <stdbool.h>

/**
 * @struct weapon
 * @brief Represents weapon used by players and enemies.
 */
struct weapon {
    /** Weapon name. */
    char *weapon_name;
    /** Weapon health. */
    unsigned int weapon_health;
    /** Weapon damage. */
    unsigned int weapon_damage;
};

/**
 * @brief Initialize weapon.
 * 
 * @param[in] name Name of the weapon.
 * @param[in] health Health of the weapon.
 * @param[in] damage Damage of the weapon.
 * @param[out] w Pointer to caller allocated weapon struct.
 * @return true if created, false otherwise. 
 */
bool weapon_initialize(const char *name, const unsigned int health, const unsigned int damage, struct weapon *w);
/**
 * @brief Gets weapon's name.
 * 
 * @param[in] w Pointer to a weapon struct.
 * @return Name of the weapon if success, NULL otherwise.
 */
const char *weapon_get_name(const struct weapon *w);
/**
 * @brief Gets weapon's health.
 * 
 * @param[in] w Pointer to weapon struct.
 * @return Weapon's health if success, 0 otherwise. 
 */
unsigned int weapon_get_health(const struct weapon *w);
/**
 * @brief Gets the weapon's damage.
 * 
 * @param[in] w Pointer to weapon struct.
 * @return Weapon's damage if success, 0 otherwise. 
 */
unsigned int weapon_get_damage(const struct weapon *w);
/**
 * @brief Uses the weapon by decreasing the weapon's health.
 * 
 * @param[in] damage Damage to cause to weapon.
 * @param[in] w Pointer to weapon struct.
 */
void weapon_use(const unsigned int damage, struct weapon *w);
/**
 * @brief Repair the weapon.
 * 
 * @param[in] repair_health Amount to repair the weapon by.
 * @param[in] w Pointer to weapon struct.
 */
void weapon_repair(const unsigned int repair_health, struct weapon *w);
/**
 * @brief Enhances the weapon by increasing its damage.
 * 
 * @param[in] enhance_damage Amount to increase the weapon by.
 * @param[in] w Pointer to weapon struct.
 */
void weapon_enhance(const unsigned int enhance_damage, struct weapon *w);
/**
 * @brief Comparison function to get weapon by its name.
 * 
 * @param[in] w Pointer to weapon struct.
 * @param[in] k Weapon's name.
 * @return true if weapon found, false otherwise.
 */
bool weapon_name_cmp(const void *w, const void *k);
/**
 * @brief Checks if the both weapons are equal.
 * 
 * @param[in] w1 Pointer to weapon struct to compare to.
 * @param[in] w2 Pointer to weapon struct to compare by.
 * @return true if weapons are equal, false otherwise.
 */
bool weapon_is_equal(const struct weapon *w1, const struct weapon *w2);
/**
 * @brief Deinitializes the weapon.
 * 
 * @param[in] w Pointer to weapon struct.
 */
void weapon_deinitialize(struct weapon *w);