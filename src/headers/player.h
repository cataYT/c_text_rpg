#pragma once

#include "weapon.h"
#include "game.h"
#include "vector.h"
#include "armor.h"
#include <stdbool.h>

struct player {
    struct vector _weapons;
    struct armor current_armor;
    char *player_name;
    unsigned int health;
    bool _isWearingArmor;
};

bool create_player(const char *name, const unsigned int health, const struct vector *weapons, const struct armor *armor, struct player *p);
const struct vector *player_get_weapons(const struct player *p);
const struct armor *player_get_armor(const struct player *p);
void player_get_stats(const struct player *p);
void player_update_weapons(const char *type, const struct weapon *w, struct player *p);
void player_attack(struct player *attacker, const char *weapon_name, struct player *target);
void player_heal(const unsigned int amount, struct player *p);
void player_equip_armor(const struct armor *a, struct player *p);
void player_add_player(const struct player *p1, const struct player *p2, struct player *add_player);
void free_player(struct player *p);