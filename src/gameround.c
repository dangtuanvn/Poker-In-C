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
                printf("-----------------------_ALL IN---------------------------------------\n");
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

void add_chips(Game_round * round, Player * player, int chipsToAdd) {
    player->chips += chipsToAdd;
    round->pot -= chipsToAdd;
}

void withdraw_chips(Player * player, int chipsToWithdraw) {
    player->chips -= chipsToWithdraw;
}

void action_bet(Game_round * round, Player * player, int chips) {
    round->position_turn = round->num_players;
    if(player->chips <= chips){
        action_allIn(round, player);
    }
    else{
        withdraw_chips(player, chips);
        round->pot += chips;
        round->call_amount += chips;
        player->bet_amount += chips;
        player->status = BET;
        }
}

void action_call(Game_round * round, Player * player) {
    player->status = CALL;
    int chips = round->call_amount - player->bet_amount;
    if(player->chips <= chips){
        chips = player->chips;
        player->status = ALLIN;
        //printf("-----------------------_ALL IN---------------------------------------\n");
    }
    withdraw_chips(player, chips);
    round->pot += chips;
    player->bet_amount += chips;
}

void action_raise(Game_round * round, Player * player, int chips){
    round->position_turn = round->num_players;
    if (player->chips <= chips) {
        action_allIn(round, player);
    }
    else {
        action_call(round, player);
        action_bet(round, player, chips - round->call_amount);
        player->status = RAISE;
    }
}

void action_allIn(Game_round * round, Player * player){
    int chips = player->chips;
    withdraw_chips(player, chips);
    round->pot += chips;
    player->bet_amount += chips;
    player->status = ALLIN;
    if(round->call_amount < player->bet_amount){
        round->call_amount = player->bet_amount;
    }
    //printf("-----------------------_ALL IN---------------------------------------\n");
}

void action_fold(Game_round * round, Player * player) {
    player->status = FOLD;
}

void action_check(Game_round * round, Player * player) {
    player->status = CHECK;
}

int get_pot(Game_round * round, Player ** list, int top_rank){
    int num_winners = 0;
    int winner_positions[round->num_players];
    for (int j = 0; j < round->num_players; j++) {
        if (list[j]->rank == top_rank) {
            winner_positions[num_winners] = j;
            num_winners++;
        }
    }

    int total_chips = 0;
    int temp = num_winners;
    for (int i = 0; i < num_winners; i++) {
        for (int j = 0; j < round->num_players; j++) {
            int winning_chips = list[j]->bet_amount / temp;
            add_chips(round, list[winner_positions[i]], winning_chips);
            total_chips += winning_chips;
            list[j]->bet_amount -= winning_chips;
            if (i == num_winners - 1) {
                add_chips(round, list[j], list[j]->bet_amount);
                list[j]->bet_amount = 0;
            }
        }
        temp--;
    }
    printf("\n%d %d\n", total_chips, num_winners);
    return total_chips / num_winners;
}

/* TODO
 * number of players remain when other leaves (out of chips)
 * winner receive money
 * Change NUM_PLAYERS
 */