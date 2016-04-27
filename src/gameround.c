#include <stdio.h>
#include "gameround.h"


void round_position_increment(Game_round round) {
    round.position_turn += 1;
//    if(round.position_turn == NUM_PLAYERS)
}

void place_ante(Game_round round, Player *player) {

}

void add_chips(Player player, int chipsToAdd) {
    player.chips += chipsToAdd;
}

void withdraw_chips(Player player, int chipsToWithdraw) {
    if (player.chips < chipsToWithdraw) {

    }
    else {
        player.chips -= chipsToWithdraw;
    }
}


void bet(Game_round round, Player player, int chips) {
    round.pot += chips;
    round.call_amount = chips;
    withdraw_chips(player, chips);
    player.bet_amount += chips;
}

void call(Game_round round, Player player) {
    int chips = round.call_amount - player.bet_amount;
    withdraw_chips(player, chips);
    round.pot += chips;
    player.bet_amount = chips;
}

void fold(Player player) {
    player.status = FOLD;
}

void check(Game_round round, Player player) {
    round.position_turn += 1;
}

void allIn(Player);

void raise(Player, int chips);

/* TODO
 * position round
 * number of players remain when other leaves (out of chips)
 * AI
 */