/*! Weapon implementation file */

#include "headers/weapon.h"
#include "headers/compatibility.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool weapon_initialize(const char *name, const unsigned int health, const unsigned int damage, struct weapon *w)
{
    if (!name || name[0] == '\0' || health == 0 || damage == 0 || !w) {
        return false;
    }

    size_t name_length = strlen(name);
    w->weapon_name = malloc(name_length + 1);
    if (!w->weapon_name) {
        return false;
    }
    strcpy_s(w->weapon_name, name_length + 1, name);
    w->weapon_health = health;
    w->weapon_damage = damage;

    return true;
}

const char *weapon_get_name(const struct weapon *w)
{
    if (!w) {
        return NULL;
    }

    return w->weapon_name;
}

unsigned int weapon_get_health(const struct weapon *w)
{
    if (!w) {
        return 0;
    }

    return w->weapon_health;
}

unsigned int weapon_get_damage(const struct weapon *w)
{
    if (!w) {
        return 0;
    }

    return w->weapon_damage;
}

void weapon_use(const unsigned int damage, struct weapon *w)
{
    if (damage == 0 || !w) {
        return;
    }

    if (w->weapon_health <= damage) {
        w->weapon_health = 0;
    }

    w->weapon_health -= damage;
}

void weapon_repair(const unsigned int repair_health, struct weapon *w)
{
    if (repair_health == 0) {
        return;
    }

    w->weapon_health += repair_health;
}

void weapon_enhance(const unsigned int enhance_damage, struct weapon *w)
{
    if (enhance_damage == 0) {
        return;
    }

    w->weapon_damage += enhance_damage;
}

bool weapon_name_cmp(const void *w, const void *k)
{
    if (!w || !k) {
        return false;
    }

    const struct weapon *weapon = (const struct weapon *)w;
    const char *key = (const char *)k;
    return strcmp(weapon->weapon_name, key) == 0;
}

bool weapon_is_equal(const struct weapon *w1, const struct weapon *w2)
{
    if (!w1 || !w2) {
        return false;
    }

    return strcmp(w1->weapon_name, w2->weapon_name) == 0 &&
    w1->weapon_health == w2->weapon_health &&
    w1->weapon_damage == w2->weapon_damage;
}

void weapon_deinitialize(struct weapon *w)
{
    if (!w || !w->weapon_name) {
        return;
    }
    free(w->weapon_name);
    w->weapon_name = NULL;
    w->weapon_health = 0;
    w->weapon_damage = 0;
    memset(w, 0, sizeof(*w));
}