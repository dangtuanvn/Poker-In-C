#ifndef COSC2451_A2_S3500286_S3500291_GAMEROUND_H
#define COSC2451_A2_S3500286_S3500291_GAMEROUND_H


#include "player.h"

/** Define game round
 */
typedef struct {
    int round_number; /**< Round number */
    int remaining_turns; /**< Remaining turns until bet phase ends */
    int pot; /**< Number of chips in the pot */
    int call_amount; /**< The amount the player must bet to stay in the round */
    int ante; /**< The initial ante amount */
    int num_players; /**< Number of players */
    int remaining_players; /**< Number of remaining players */
    int fold_count; /**< Number of players have folded or busted */
} Game_round;

/** Create a game round
 * @param num_players is the number of players
 */
Game_round * create_game_round(int num_players);

/** Free the allocated resources for game round
 * @param game_round is the round to be freed
 */
void free_game_round(Game_round * game_round);

/** Force all players to place ante at the start of a round
 * @param round is the game round
 * @param player is the list of players
 */
void place_ante(Game_round * round, Player ** player);

/** Add chips to a player
 * @param round is the game round
 * @param player is the player
 * @param chipsToAdd is the number of chips to added to the player
 */
void add_chips(Game_round * round, Player * player, int chipsToAdd);

/** Withdraw chips from a player
 * @param player is the player
 * @param chipsToWithdraw is the number of chips to be withdrew
 */
void withdraw_chips(Player * player, int chipsToWithdraw);

/** Bet a number of chips
 * @param round is the game round
 * @param player is the player
 * @param chips is the number of chips to be bet
 */
void action_bet(Game_round * round, Player * player, int chips);

/** Bet the same amount of chips as other playeres to stay in the round
 * @param round is the game round
 * @param player is the player
 */
void action_call(Game_round * round, Player * player);

/** Raise the betting amount
 * @param round is the game round
 * @param player is the player
 * @param chips is the number of chips to be bet
 */
void action_raise(Game_round * round, Player * player, int chips);

/** Skip the round
 * @param round is the game round
 * @param player is the player
 */
void action_fold(Game_round * round, Player * player);

/** Pass the turn to another player without betting
 * @param round is the game round
 * @param player is the player
 */
void action_check(Game_round * round, Player * player);

/** Bet all the available chips
 * @param round is the game round
 * @param player is the player
 */
void action_allIn(Game_round * round, Player * player);

/** Divide the pot to the winners
 * @param round is the game round
 * @param list is the players list
 * @param winner_position is the position of the winner
 */
int get_pot(Game_round * round, Player ** list, int winner_position);

/** Check number of busted players
 * @param round is the game round
 * @param list is the players list
 */
int check_num_busted_players(Game_round * round, Player ** list);

/** Reset the round to start a new round
 * @param round is the game round
 * @param list is the players list
 */
void reset_round(Game_round * round, Player ** list);

/** Check the number of folded players
 * @param round is the game round
 * @param list is the players list
 */
int check_fold_count(Game_round * round, Player ** list);

#endif //COSC2451_A2_S3500286_S3500291_GAMEROUND_H
