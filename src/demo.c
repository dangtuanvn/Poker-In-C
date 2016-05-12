#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "poker.h"
#include "gameround.h"
#include "player.h"

int main(){
    Deck * deck = create_deck();
    //print_cards(deck, LENGTH_DECK);

    Player ** players_list = create_players_list(NUM_PLAYERS, LENGTH_HANDS, AI_NORMAL);
    strcpy(players_list[0]->name , "PLAYER");
    strcpy(players_list[1]->name , "BOB");
    strcpy(players_list[2]->name , "KEVIN");
    strcpy(players_list[3]->name , "SARAH");
    //players_list[1]->chips = 3005;
    //players_list[2]->chips = 3003;
    //players_list[3]->chips = 2000;

    Game_round * round = create_game_round(NUM_PLAYERS);

    int ongoing = 1;
    while(ongoing){
        // ROUND START
        shuffle_deck(deck, LENGTH_DECK);
        // print_cards(deck, LENGTH_DECK);

        for(int j = 0; j < LENGTH_HANDS; j++){
            for(int i = 0; i < NUM_PLAYERS; i++) {
                deal_card(deck, *players_list[i], LENGTH_HANDS);
            }
        }
        place_ante(round, players_list);


        players_list[2]->player_hands[0].number = (Number) 14;
        players_list[2]->player_hands[0].suit = (Suit) 1;
        players_list[2]->player_hands[1].number = (Number) 10;
        players_list[2]->player_hands[1].suit = (Suit) 1;
        players_list[2]->player_hands[2].number = (Number) 13;
        players_list[2]->player_hands[2].suit = (Suit) 1;
        players_list[2]->player_hands[3].number = (Number) 11;
        players_list[2]->player_hands[3].suit = (Suit) 1;
        players_list[2]->player_hands[4].number = (Number) 12;
        players_list[2]->player_hands[4].suit = (Suit) 1;

        players_list[3]->player_hands[0].number = (Number) 14;
        players_list[3]->player_hands[0].suit = (Suit) 1;
        players_list[3]->player_hands[1].number = (Number) 10;
        players_list[3]->player_hands[1].suit = (Suit) 1;
        players_list[3]->player_hands[2].number = (Number) 13;
        players_list[3]->player_hands[2].suit = (Suit) 1;
        players_list[3]->player_hands[3].number = (Number) 11;
        players_list[3]->player_hands[3].suit = (Suit) 1;
        players_list[3]->player_hands[4].number = (Number) 12;
        players_list[3]->player_hands[4].suit = (Suit) 1;

        for(int j = 0; j < NUM_PLAYERS; j++)
        {
            sort_hands(players_list[j]->player_hands, LENGTH_HANDS);
        }
        // BETTING PHASE 1
        // print_player_info(players_list[0]);

        /*
        action_bet(&round, &players_list[0], 20);
        action_call(&round, &players_list[1]);
        action_raise(&round, &players_list[2], 70);
        action_call(&round, &players_list[3]);

        AI_bet_phase1(&round, &players_list[1]);
        AI_bet_phase1(&round, &players_list[2]);
        AI_bet_phase1(&round, &players_list[3]);
        */
        int position = 0;

        while(round->position_turn  > 0){
            // printf("%d %d", players_list[0].bet_amount, round.call_amount);
            if(players_list[position]->type == HUMAN){
                if(players_list[position]->status > 2) {
                    if (players_list[position]->bet_amount == round->call_amount) {
                        action_check(round, players_list[position]);
                    }
                    else {
                        action_call(round, players_list[position]);
                    }
                }
            }
            else{
                if(players_list[position]->status > 2) {
                    AI_bet_phase1(round, players_list[position]);
                }
            }


            if(players_list[position]->status == CHECK){
                printf("%s checks, %d\n", players_list[position]->name, players_list[position]->bet_amount);
            }
            else if(players_list[position]->status == CALL){
                printf("%s calls, %d\n", players_list[position]->name, players_list[position]->bet_amount);
            }
            else if(players_list[position]->status == BET){
                printf("%s bets, %d\n", players_list[position]->name, players_list[position]->bet_amount);
            }
            else if(players_list[position]->status == RAISE){
                printf("%s raises, %d\n", players_list[position]->name, players_list[position]->bet_amount);
            }
            else if(players_list[position]->status == FOLD){
                printf("%s folds\n", players_list[position]->name);
            }
            else if(players_list[position]->status == ALLIN){
                printf("%s all in, %d\n", players_list[position]->name, players_list[position]->bet_amount);
            }

            // printf("%s: %d - %d\n", players_list[position].name, players_list->bet_amount, players_list->status);
            // printf("Position: %d\n", position);
            position++;
            if(position == 4){
                position = 0;
            }

            round->position_turn--;
            waitFor(1);
        }
        printf("\n");
        printf("BETTING PHASE 1 FINISHED\n");
        printf("Call amount: %d\n", round->call_amount);
        printf("Pot: %d\n", round->pot);
        printf("\n");

        // EXCHANGE CARDS PHASE
        AI_change_cards(deck, players_list, NUM_PLAYERS);

        // BETTING PHASE 2
        round->position_turn = 4;
        while(round->position_turn  > 0){
            // printf("%d %d", players_list[0].bet_amount, round.call_amount);
            if(players_list[position]->type == HUMAN){
                if(players_list[position]->status > 2) {
                    if (players_list[position]->bet_amount == round->call_amount) {
                        action_check(round, players_list[position]);
                    }
                    else {
                        action_call(round, players_list[position]);
                    }
                }
            }
            else{
                if(players_list[position]->status > 2) {
                    AI_bet_phase2(round, players_list[position]);
                }
            }

            if(players_list[position]->status == CHECK){
                printf("%s checks, %d\n", players_list[position]->name, players_list[position]->bet_amount);
            }
            else if(players_list[position]->status == CALL){
                printf("%s calls, %d\n", players_list[position]->name, players_list[position]->bet_amount);
            }
            else if(players_list[position]->status == BET){
                printf("%s bets, %d\n", players_list[position]->name, players_list[position]->bet_amount);
            }
            else if(players_list[position]->status == RAISE){
                printf("%s raises, %d\n", players_list[position]->name, players_list[position]->bet_amount);
            }
            else if(players_list[position]->status == FOLD){
                printf("%s folds\n", players_list[position]->name);
            }
            else if(players_list[position]->status == ALLIN){
                printf("%s all in, %d\n", players_list[position]->name, players_list[position]->bet_amount);
            }

            // printf("%s: %d - %d\n", players_list[position].name, players_list->bet_amount, players_list->status);
            // printf("Position: %d\n", position);
            position++;
            if(position == 4){
                position = 0;
            }

            round->position_turn--;
            waitFor(1);
        }
        printf("\n");
        printf("BETTING PHASE 2 FINISHED\n");
        printf("Call amount: %d\n", round->call_amount);
        printf("Pot: %d\n", round->pot);

        // SHOWDOWN PHASE
        printf("\n");
        for(int j = 0; j < NUM_PLAYERS; j++)
        {
            sort_hands(players_list[j]->player_hands, LENGTH_HANDS);
            printf("%s:\t", players_list[j]->name);
            print_cards(players_list[j]->player_hands, LENGTH_HANDS);
        }
        printf("\n");

        printf("---------------------SHOWDOWN---------------------\n\n");
        int top_rank = showdown(*round, players_list);
        get_pot(round, players_list, top_rank);

        for(int j = 0; j < NUM_PLAYERS; j++){
            printf("\n");
            print_player_info(*players_list[j]);
        }
        ongoing = 0;
    }

    printf("Call amount: %d\n", round->call_amount);
    printf("\nPot: %d\n", round->pot);

/*
    for(int j = 0; j < 1; j++)
{
    print_cards(players_list[j].player_hands, LENGTH_HANDS);
}
*/
    free_deck(deck);
    free_players_list(players_list, NUM_PLAYERS);
    free_game_round(round);
    return 0;
}