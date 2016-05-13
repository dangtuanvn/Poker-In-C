#ifndef COSC2451_A2_S3500286_S3500291_GAMEROUND_H
#define COSC2451_A2_S3500286_S3500291_GAMEROUND_H


#include "player.h"

/* Struct game_round with unique variables
 */
typedef struct {
    int round_number;
    int position_turn;
    int pot;
    int call_amount;
    int ante;
    int num_players;
    int remaining_players;
    int fold_count;
} Game_round;

Game_round * create_game_round(int num_players);

void free_game_round(Game_round * game_round);

void round_position_increment(Game_round * round);

void place_ante(Game_round * round, Player ** player);

void add_chips(Game_round * round, Player * player, int chipsToAdd);

void withdraw_chips(Player * player, int chipsToWithdraw);

void action_bet(Game_round * round, Player * player, int chips);

void action_call(Game_round * round, Player * player);

void action_raise(Game_round * round, Player * player, int chips);

void action_fold(Game_round * round, Player * player);

void action_check(Game_round * round, Player * player);

void action_allIn(Game_round * round, Player * player);

int get_pot(Game_round * round, Player ** list, int winner_position);

int check_num_busted_players(Game_round * round, Player ** list);

void reset_round(Game_round * round, Player ** list);

int check_fold_count(Game_round * round, Player ** list);

#endif //COSC2451_A2_S3500286_S3500291_GAMEROUND_H
