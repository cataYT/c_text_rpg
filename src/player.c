/*! Player implementation file */

#include "headers/player.h"
#include "third_party/pcg_basic.h"
#include "headers/compatibility.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/** Random state */
pcg32_random_t pcg_state;

bool player_initialize(const char *name, const unsigned int health, const struct vector *weapons, const struct armor *armor, struct player *p)
{
    if (!name || name[0] == '\0' || health == 0 || !weapons || !armor || !p) {
        return false;
    }

    size_t name_length = strlen(name);
    p->player_name = malloc(name_length + 1);
    if (!p->player_name) {
        return false;
    }
    strcpy_s(p->player_name, name_length + 1, name);
    p->health = health;
    p->_weapons = *weapons;
    p->current_armor = *armor;
    p->_isWearingArmor = true;

    return true;
}

const struct vector *player_get_weapons(const struct player *p)
{
    if (!p) {
        return NULL;
    }

    return &p->_weapons;
}

const struct armor *player_get_armor(const struct player *p)
{
    if (!p) {
        return NULL;
    }

    return &p->current_armor;
}

void player_get_stats(const struct player *p)
{
    if (!p) {
        return;
    }

    printf("----GETTING STATS FOR %s----\n", p->player_name);
    printf("Health: %u", p->health);
    struct weapon w = {0};
    for (unsigned int i = 0; i <= p->_weapons.size; i++) {
        vector_get_element(&p->_weapons, i, &w);
        printf("%s:%u", w.weapon_name, w.weapon_damage);
    }
    printf("Total weapon size: %zu\n", p->_weapons.size);
    printf("----STATS END----\n");
}

void player_update_weapons(const char *type, const struct weapon *w, struct player *p)
{
    if (!type || type[0] == '\0' || !w || !p) {
        return;
    }

    if (strcmp(type, "add") == 0) {
        vector_push_back(&p->_weapons, w);
        return;
    }

    if (strcmp(type, "remove") == 0) {
        vector_pop_search(&p->_weapons, w);
        return;
    }
}

/**
 * @brief Used to determine critical damage. Gets a random value from 1 to 4 and applying critical damage if the value is 1.
 * 
 * @param[in] weapon_damage Base weapon damage.
 * @param[in] armor_resistance Armor resistance, used for decreasing the total damage.
 * @return damage/resistance * 1.5 or damage/resistance.
 */
unsigned int crit(const unsigned int weapon_damage, const unsigned int armor_resistance)
{
    if (weapon_damage == 0 || armor_resistance == 0) {
        return 0;
    }
    const unsigned int rrand_num = pcg32_random_r(&pcg_state);
    const unsigned int rand_num = (unsigned int) (rrand_num % (4 - 1 + 1)) + 1;
    return (rand_num == 1)
    ? (unsigned int)((weapon_damage / armor_resistance) * 1.5)
    : (weapon_damage / armor_resistance);
}

void player_attack(struct player *attacker, const char *weapon_name, struct player *target)
{
    struct weapon w = {0};
    if (!attacker || !weapon_name || weapon_name[0] == '\0' || !target || target->health == 0 
        || !vector_search_element(&attacker->_weapons, weapon_name, &w, weapon_name_cmp)) {
        return;
    }

    const unsigned int damage = crit(w.weapon_damage, target->current_armor._armor_resistance_force);
    target->health = (target->health > damage) ? target->health - damage : 0;
    weapon_use(damage / 10, &w);
}

void player_heal(const unsigned int amount, struct player *p)
{
    if (amount == 0 || !p) {
        return;
    }

    p->health += amount;
}

void player_equip_armor(const struct armor *a, struct player *p)
{
    if (!a || !p || p->_isWearingArmor) {
        return;
    }

    p->current_armor = *a;
    p->_isWearingArmor = true;
}

void player_add_player(const struct player *p1, const struct player *p2, struct player *add_player)
{
    if (!p1 || !p2 || !add_player) {
        return;
    }

    size_t total_size = strlen(p1->player_name) + 1 + strlen(p2->player_name) + 1;
    add_player->player_name = malloc(total_size);
    if (!add_player->player_name) {
        return;
    }
    strcpy_s(add_player->player_name, total_size,  p1->player_name);
    strcat_s(add_player->player_name, total_size, ":");
    strcat_s(add_player->player_name, total_size, p2->player_name);
    add_player->health = p1->health + p2->health;

    const size_t bigger_size = (p1->_weapons.size > p2->_weapons.size) ? p1->_weapons.size : p2->_weapons.size;
    struct vector new_weapons = {0};
    vector_initialize(bigger_size * 2, sizeof(struct weapon), &new_weapons);

    struct weapon temp_1 = {0};
    struct weapon temp_2 = {0};

    for (size_t i = 0; i < bigger_size; i++) {
        if (i < p1->_weapons.size) {
            vector_get_element(&p1->_weapons, i, &temp_1);
            vector_push_back(&new_weapons, &temp_1);
        }
        if (i < p2->_weapons.size) {
            vector_get_element(&p2->_weapons, i, &temp_2);
            vector_push_back(&new_weapons, &temp_2);
        }
    }

    armor_add_armor(&p1->current_armor, &p2->current_armor, &add_player->current_armor);
    add_player->_isWearingArmor = true;
}

void player_deinitialize(struct player *p)
{
    if (!p || !p->player_name) {
        return;
    }

    free(p->player_name);
    p->player_name = NULL;
    p->health = 0;
    p->_isWearingArmor = false;
    memset(p, 0, sizeof(*p));
}