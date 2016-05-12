#ifndef COSC2451_A2_S3500286_S3500291_POKER_H
#define COSC2451_A2_S3500286_S3500291_POKER_H

#include "gameround.h"

#define     NUM_PLAYERS         4


// TYPEDEF, ENUM and STRUCT

// FUNCTIONS

/* Determine the hands of each player, then pick the best hands
 * @param list is the list of players
 */
void showdown(Player ** list);

void AI_change_cards(Deck * deck, Player ** list, int length);

void AI_normal_change(Deck * deck, Player player);

void AI_easy_change(Deck * deck, Player player);

void AI_bet_phase1(Game_round * round, Player * player);

void AI_bet_phase2(Game_round * round, Player * player);

void waitFor (unsigned int secs);

#endif //COSC2451_A2_S3500286_S3500291_POKER_H