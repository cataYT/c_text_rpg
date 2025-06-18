#pragma once

#include "vector.h"
#include "player.h"
#include <stdbool.h>
#include <stdlib.h>

struct player;

struct game {
    struct vector players;
};

bool create_game(const unsigned int initial_capacity, struct game *g);
bool game_insert_player(const struct player *p, struct game *g);
bool game_remove_player(const struct player *p, struct game *g);
void game_get_winner(struct player *winner, const struct game *g);
size_t game_get_total_players(const struct game *g);
void free_game(struct game *g);