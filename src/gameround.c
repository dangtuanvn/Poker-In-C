#include <stdio.h>
#include <stdlib.h>
#include "gameround.h"
#include "player.h"

Game_round * create_game_round(int num_players){ // TODO: free game_round
    Game_round * round = malloc(sizeof(Game_round));
    round->num_players = num_players;
    round->call_amount = 0;
    round->position_turn = num_players;
    round->pot = 0;
    round->round_number = 1;

    if(round->round_number < 5) {
        round->ante = 8;
    }
    else if(round->round_number < 9){
        round->ante *= 5;
    }
    else if(round->round_number < 13){
        round->ante *= 5;
    }
    else if(round->round_number >= 13){
        round->ante = 1000;
    }

    return round;
}

void free_game_round(Game_round * game_round){
    free(game_round);
} // TODO: not finished

void place_ante(Game_round * round, Player **list) {
    for(int j = 0; j < round->num_players; j++){
        if(list[j]->status != BUSTED) {
            if(list[j]->chips < round->ante){
                withdraw_chips(list[j], list[j]->chips);
                round->pot += list[j]->chips;
                list[j]->bet_amount = round->ante;
                list[j]->status = ALLIN;
            }
            else{
                withdraw_chips(list[j], round->ante);
                round->pot += round->ante;
                list[j]->bet_amount = round->ante;
                list[j]->status = ACTIVE;
            }
        }
    }
    round->call_amount = round->ante;
}

void add_chips(Player * player, int chipsToAdd) {
    player->chips += chipsToAdd;
    // TODO: deduct chips from the pot
}

void withdraw_chips(Player * player, int chipsToWithdraw) {
    player->chips -= chipsToWithdraw;
}

void action_bet(Game_round * round, Player * player, int chips) {
    round->position_turn = round->num_players;
    if (player->chips < chips) {
        action_allIn(round, player);
        round->call_amount += player->chips;
    }
    else {
        withdraw_chips(player, chips);
        round->pot += chips;
        round->call_amount += chips;
        player->bet_amount += chips;
        player->status = BET;
        printf("%s bets %d\n", player->name, chips );
    }
}

void action_call(Game_round * round, Player * player) {
    player->status = CALL;
    int chips = round->call_amount - player->bet_amount;
    if(chips > player->chips){
        chips = player->chips;
        player->status = ALLIN;
    }
    withdraw_chips(player, chips);
    round->pot += chips;
    player->bet_amount += chips;
    printf("%s calls %d\n", player->name, chips );
}


void action_raise(Game_round * round, Player * player, int chips){
    round->position_turn = round->num_players;
    if (player->chips < chips) {
        action_allIn(round, player);
        round->call_amount += player->chips;
    }
    else {
        action_call(round, player);
        action_bet(round, player, chips - round->call_amount);
        player->status = RAISE;
        printf("%s raises %d\n", player->name, chips );
    }
}

void action_fold(Game_round * round, Player * player) {
    player->status = FOLD;
    printf("%s folds\n", player->name);
}

void action_check(Game_round * round, Player * player) {
    printf("%s checks\n", player->name);
}

void action_allIn(Game_round * round, Player * player){
    int chips = player->chips;
    withdraw_chips(player, chips);
    round->pot += chips;
    player->bet_amount += chips;
    player->status = ALLIN;
    printf("%s all in %d\n", player->name, chips );
}

/* TODO
 * number of players remain when other leaves (out of chips)
 */