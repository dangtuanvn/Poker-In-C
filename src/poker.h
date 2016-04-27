#include "player.h"

#define     NUM_PLAYERS         4


// TYPEDEF, ENUM and STRUCT

// FUNCTIONS

/* Determine the hands of each player, then pick the best hands
 * @param list is the list of players
 */
void showdown(Player * list);

void AI_change_cards(Deck * deck, Player * list);

void AI_normal_change(Deck * deck, Player player);

void AI_easy_change(Deck * deck, Player player);

