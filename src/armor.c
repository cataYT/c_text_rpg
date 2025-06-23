/*! Armor implementation file */

#include "headers/armor.h"
#include "headers/compatibility.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

bool armor_initialize(const char *name, const unsigned int health, const unsigned int max_health, const unsigned int resistance_force, struct armor *a)
{
    if (!name || name[0] == '\0' || health == 0 || max_health == 0 || health > max_health || resistance_force == 0 || !a) {
        return false;
    }

    size_t name_length = strlen(name);
    a->armor_name = malloc(name_length + 1);
    if (!a->armor_name) {
        return false;
    }
    strcpy_s(a->armor_name, name_length + 1, name);
    a->_armor_health = health;
    a->_armor_max_health = max_health;
    a->_armor_resistance_force = resistance_force;

    return true;
}

unsigned int armor_get_health(const struct armor *a)
{
    if (!a) {
        return 0;
    }

    return a->_armor_health;
}

unsigned int armor_get_resistance(const struct armor *a)
{
    if (!a) {
        return 0;
    }

    return a->_armor_resistance_force;
}

void armor_enhance_armor(const unsigned int new_resistance_force, struct armor *a)
{
    if (new_resistance_force <= a->_armor_resistance_force || !a) {
        return;
    }

    a->_armor_resistance_force = new_resistance_force;
}

void armor_repair_armor(const unsigned int repair_amount, struct armor *a)
{
    if (repair_amount == 0 || !a) {
        return;
    }

    if (a->_armor_health != a->_armor_max_health) {
		a->_armor_health += repair_amount;
		if (a->_armor_health > a->_armor_max_health) {
			a->_armor_health = a->_armor_max_health;
		}
	}
}

void armor_print_stats(const struct armor *a)
{
    if (!a) {
        return;
    }

    printf("Armor name: %s\nArmor health: %u\nArmor max health: %u\nArmor resistance: %u\n", 
        a->armor_name, a->_armor_health, a->_armor_max_health, a->_armor_resistance_force);
}

bool armor_is_equal(const struct armor *a1, const struct armor *a2)
{
    if (!a1 || !a2) {
        return false;
    }

    return strcmp(a1->armor_name, a2->armor_name) == 0 &&
    a1->_armor_health == a2->_armor_health &&
    a1->_armor_max_health == a2->_armor_health &&
    a1->_armor_resistance_force == a2->_armor_resistance_force;
}

void armor_add_armor(const struct armor *a1, const struct armor *a2, struct armor *added_armor)
{
    if (!a1 || !a2 || !added_armor) {
        return;
    }

    size_t total_len = strlen(a1->armor_name) + 1 + strlen(a2->armor_name) + 1;
    added_armor->armor_name = malloc(total_len);
    if (!added_armor->armor_name) {
        return;
    }
    strcpy_s(added_armor->armor_name, total_len, a1->armor_name);
    strcat_s(added_armor->armor_name, total_len, ":");
    strcat_s(added_armor->armor_name, total_len, a2->armor_name);

    added_armor->_armor_health = a1->_armor_health + a2->_armor_health;
    added_armor->_armor_max_health = a1->_armor_max_health + a2->_armor_max_health;
    added_armor->_armor_resistance_force = a1->_armor_resistance_force + a2->_armor_resistance_force;
}

void armor_deinitialize(struct armor *a)
{
    if (!a || !a->armor_name) {
        return;
    }
    free(a->armor_name);
    a->armor_name = NULL;
    a->_armor_health = 0;
    a->_armor_max_health = 0;
    a->_armor_resistance_force = 0;
    memset(a, 0, sizeof(*a));
}