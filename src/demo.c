#include <stdio.h>
#include <stdlib.h>

#include "poker.h"

int main(){
    struct deck * deck = create_deck();
    // print_cards(deck, LENGTH_DECK);

    shuffle_deck(deck, LENGTH_DECK);
    // print_cards(deck, LENGTH_DECK);

    struct player * players_list = create_players_list(NUM_PLAYERS, LENGTH_HANDS);

for(int j = 0; j < LENGTH_HANDS; j++){
    for(int i = 0; i < NUM_PLAYERS; i++) {
        deal_card(deck, players_list[i], LENGTH_HANDS);
    }
}

/*
    for(int j = 0; j < 1; j++)
{
    print_cards(players_list[j].player_hands, LENGTH_HANDS);
}
*/

    // change_card(deck, players_list[0], 0);


    players_list[1].player_hands[0].number = (Number) 8;
    players_list[1].player_hands[0].suit = (Suit) 3;
    players_list[1].player_hands[1].number = (Number) 1;
    players_list[1].player_hands[1].suit = (Suit) 3;
    players_list[1].player_hands[2].number = (Number) 7;
    players_list[1].player_hands[2].suit = (Suit) 3;
    players_list[1].player_hands[3].number = (Number) 4;
    players_list[1].player_hands[3].suit = (Suit) 3;
    players_list[1].player_hands[4].number = (Number) 3;
    players_list[1].player_hands[4].suit = (Suit) 3;



    players_list[3].player_hands[0].number = (Number) 10;
    players_list[3].player_hands[0].suit = (Suit) 2;
    players_list[3].player_hands[1].number = (Number) 8;
    players_list[3].player_hands[1].suit = (Suit) 2;
    players_list[3].player_hands[2].number = (Number) 8;
    players_list[3].player_hands[2].suit = (Suit) 2;
    players_list[3].player_hands[3].number = (Number) 9;
    players_list[3].player_hands[3].suit = (Suit) 2;
    players_list[3].player_hands[4].number = (Number) 3;
    players_list[3].player_hands[4].suit = (Suit) 2;


    for(int j = 0; j < NUM_PLAYERS; j++)
    {
        sort_hands(players_list[j].player_hands, LENGTH_HANDS);
        print_cards(players_list[j].player_hands, LENGTH_HANDS);
    }
    showdown(players_list);


    free_deck(deck);
    free(players_list);
    return 0;
}