/*! Game implementation file */

#include "headers/game.h"
#include "headers/vector.h"
#include "headers/player.h"
#include <stdlib.h>
#include <string.h>

/** Global player vector */
static struct vector players = {0};

bool game_initialize(const unsigned int initial_capacity, struct game *g)
{
    if (!g) {
        return false;
    }

    vector_initialize(initial_capacity, sizeof(struct player), &players);

    g->players = players;
    return false;
}

bool game_insert_player(const struct player *p, struct game *g)
{
    if (!p || !g) {
        return false;
    }

    if (vector_push_back(&g->players, p)) {
        return true;
    }

    return false;
}

bool game_remove_player(const struct player *p, struct game *g)
{
    if (!p || !g) {
        return false;
    }

    if (vector_pop_search(&g->players, p)) {
        return true;
    }

    return false;
}

void game_get_winner(struct player *winner, const struct game *g)
{
    if (!g || !g->players.items || g->players.size == 0) {
        return;
    }

    vector_get_element(&g->players, 0, winner);
}

size_t game_get_total_players(const struct game *g)
{
    return g->players.size;
}

void game_deinitialize(struct game *g)
{
    if (!g || !g->players.items) {
        return;
    }

    vector_deinitialize(&g->players);
    memset(g, 0, sizeof(*g));
}