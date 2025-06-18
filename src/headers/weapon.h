#pragma once
#include <stdbool.h>

struct weapon {
    char *weapon_name;
    unsigned int weapon_health;
    unsigned int weapon_damage;
};

bool create_weapon(const char *name, const unsigned int health, const unsigned int damage, struct weapon *w);
const char *weapon_get_name(const struct weapon *w);
unsigned int weapon_get_health(const struct weapon *w);
unsigned int weapon_get_damage(const struct weapon *w);
void weapon_use(const unsigned int damage, struct weapon *w);
void weapon_repair(const unsigned int repair_health, struct weapon *w);
void weapon_enhance(const unsigned int enhance_damage, struct weapon *w);
bool weapon_name_cmp(const void *w, const void *k);
bool weapon_is_equal(const struct weapon *w1, const struct weapon *w2);
void free_weapon(struct weapon *w);