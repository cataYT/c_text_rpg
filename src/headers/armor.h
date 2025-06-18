#pragma once
#include <stdbool.h>

struct armor {
    unsigned int _armor_resistance_force;
    unsigned int _armor_health;
    unsigned int _armor_max_health;

    char *armor_name;
};

bool create_armor(const char *name, const unsigned int health, const unsigned int max_health, const unsigned int resistance_force, struct armor *a);
unsigned int armor_get_health(const struct armor *a);
unsigned int armor_get_resistance(const struct armor *a);
void armor_enhance_armor(const unsigned int new_resistance_force, struct armor *a);
void armor_repair_armor(const unsigned int repair_amount, struct armor *a);
void armor_print_stats(const struct armor *a);
bool armor_is_equal(const struct armor *a1, const struct armor *a2);
void armor_add_armor(const struct armor *a1, const struct armor *a2, struct armor *added_armor);
void free_armor(struct armor *a);