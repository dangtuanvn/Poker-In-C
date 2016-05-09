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


/* TODO
 * number of players remain when other leaves (out of chips)
 * AI betting
 */