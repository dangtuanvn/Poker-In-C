#ifndef COSC2451_A2_S3500286_S3500291_POKER_H
#define COSC2451_A2_S3500286_S3500291_POKER_H

#include "gameround.h"

/** Determine the hands of each player, then pick the best hands
 * @param list is the list of players
 * @param round is the game round
 */
int showdown(Game_round round, Player ** list);

/** Determine the AI level and call the appropriate AI to change cards
 * @param deck is the deck used to deal card
 * @param list is the players list
 * @param length is the number of players
 */
void AI_change_cards(Deck * deck, Player ** list, int length);

/** AI level Normal change cards
 * @param deck is the deck used to deal card
 * @param player is the AI player
 */
void AI_normal_change(Deck * deck, Player player);

/** AI level Easy change cards
 * @param deck is the deck used to deal card
 * @param player is the AI player
 */
void AI_easy_change(Deck * deck, Player player);

/** Determine the AI level and call the appropriate AI to bet in phase 1
 * @param round is the game round
 * @param player is the AI player
 */
void AI_bet_phase1(Game_round * round, Player * player);

/** Determine the AI level and call the appropriate AI to bet in phase 2
 * @param round is the game round
 * @param player is the AI player
 */
void AI_bet_phase2(Game_round * round, Player * player);

/** AI level Normal bet phase 1
 * @param round is the game round
 * @param player is the AI player
 */
void AI_normal_bet_phase1(Game_round * round, Player * player);

/** AI level Normal bet phase 2
 * @param round is the game round
 * @param player is the AI player
 */
void AI_normal_bet_phase2(Game_round * round, Player * player);

/** AI level Easy bet phase 1
 * @param round is the game round
 * @param player is the AI player
 */
void AI_easy_bet_phase1(Game_round * round, Player * player);

/** AI level Easy bet phase 2
 * @param round is the game round
 * @param player is the AI player
 */
void AI_easy_bet_phase2(Game_round * round, Player * player);

/** Tell the program to wait for a number of seconds
 * @param secs is the seconds to be waited for
 */
void waitFor (unsigned int secs);

#endif //COSC2451_A2_S3500286_S3500291_POKER_H