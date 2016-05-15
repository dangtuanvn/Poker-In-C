#include <stdio.h>
#include <stdlib.h>
#include "gameround.h"
#include "player.h"

Game_round * create_game_round(int num_players){
    Game_round * round = malloc(sizeof(Game_round));
    round->num_players = num_players;
    round->remaining_players = num_players;
    round->remaining_turns = num_players;
    round->call_amount = 0;
    round->pot = 0;
    round->round_number = 1;
    round->ante = 8;
    round->fold_count = 0;
    return round;
}

void free_game_round(Game_round * game_round){
    free(game_round);
}

void place_ante(Game_round * round, Player **list) {
    for(int j = 0; j < round->num_players; j++){
        if(list[j]->status != BUSTED) {
            if(list[j]->chips <= round->ante){
                round->pot += list[j]->chips;
                list[j]->bet_amount = list[j]->chips;
                withdraw_chips(list[j], list[j]->chips);
                list[j]->status = ALLIN;
                //printf("-----------------------_ALL IN---------------------------------------\n");
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
    //printf("Add %d to %s\n", chipsToAdd, player->name);
    round->pot -= chipsToAdd;
}

void withdraw_chips(Player * player, int chipsToWithdraw) {
    player->chips -= chipsToWithdraw;
}

void action_bet(Game_round * round, Player * player, int chips) {
    round->remaining_turns = round->num_players;
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
    round->remaining_turns = round->num_players;
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
    round->fold_count++;
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
            if(list[j]->status == BUSTED){
                continue;
            }
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
    // printf("\n%d %d\n", total_chips, num_winners);
    return total_chips / num_winners;
}

int check_num_busted_players(Game_round * round, Player ** list){
    int count = 0;
    for(int j = 0; j < round->num_players; j++){
        if(list[j]->chips == 0){
            list[j]->status = BUSTED;
            count++;
        }
    }
    return count;
}

void reset_round(Game_round * round, Player ** list){
    int count = check_num_busted_players(round, list);
    round->remaining_players = round->num_players - count;
    round->fold_count = count;
    round->round_number++;
    round->remaining_turns = round->num_players;
    round->call_amount = 0;

    if(round->round_number < 5) {
        round->ante = 8;
    }
    else if(round->round_number == 5){
        round->ante *= 5;
    }
    else if(round->round_number == 9){
        round->ante *= 5;
    }
    else if(round->round_number > 13){
        round->ante = 1000;
    }
    for (int j = 0; j < round->num_players; j++) {
        for(int i = 0; i < LENGTH_HANDS; i++){
            list[j]->player_hands[i].number = (Number) 0;
            if(list[j]->status == BUSTED) {
                list[j]->rank = -1;
            }
            else{
                list[j]->rank = 0;
            }
        }
    }
}

int check_fold_count(Game_round * round, Player ** list){
    if(round->fold_count == round->num_players - 1){
        for(int j = 0; j < round->num_players; j++){
            list[j]->bet_amount = 0;
        }
        for(int j = 0; j < round->num_players; j++) {
            if(list[j]->status > 2) {
                add_chips(round, list[j], round->pot);
                printf("%s steals the pot\n", list[j]->name);
                return 1;
            }
        }
    }
    return 0;
}

/* TODO
 * When all players fold.
 */