#include <stdio.h>
#include <stdlib.h>
#include "gameround.h"

Game_round create_game_round(int num_players){
    Game_round * round = malloc(sizeof(Game_round));
    round->num_players = num_players;
    round->call_amount = 0;
    round->position_turn = 0;
    round->pot = 0;
    round->round_number = 1;

    round->ante = 20;

    return * round;
}

void round_position_increment(Game_round * round) {
    round->position_turn += 1;
//    if(round.position_turn == NUM_PLAYERS)
}

void place_ante(Game_round * round, Player * list) {
    for(int j = 0; j < round->call_amount; j++){
        bet(round, &list[j], round->ante);
    }
}

void add_chips(Player * player, int chipsToAdd) {
    player->chips += chipsToAdd;
}

void withdraw_chips(Player * player, int chipsToWithdraw) {
    player->chips -= chipsToWithdraw;
}

void bet(Game_round * round, Player * player, int chips) {
    if (player->chips < chips) {
        allIn(round, player);
    }
    else {
        withdraw_chips(player, chips);
        round->pot += chips;
        round->call_amount += chips;
        player->bet_amount += chips;
        player->status = BET;
        round->position_turn += 1;
    }
}

void call(Game_round * round, Player * player) {
    int chips = round->call_amount - player->bet_amount;
    withdraw_chips(player, chips);
    round->pot += chips;
    player->bet_amount += chips;
    player->status = CALL;
    round->position_turn += 1;
}


void raisea(Game_round * round, Player * player, int chips){
    call(round, player);
    bet(round, player, chips - round->call_amount);
    player->status = RAISE;
    round->position_turn += 1;
}

void fold(Game_round * round, Player * player) {
    player->status = FOLD;
    round->position_turn += 1;
}

void check(Game_round * round, Player * player) {
    round->position_turn += 1;
}

void allIn(Game_round * round, Player * player){
    bet(round, player, player->chips);
    player->status = ALLIN;
}

/* TODO
 * number of players remain when other leaves (out of chips)
 * AI betting
 */