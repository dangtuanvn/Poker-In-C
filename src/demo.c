#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "poker.h"

int main(){
    Deck * deck = create_deck();
    // print_cards(deck, LENGTH_DECK);

    shuffle_deck(deck, LENGTH_DECK);
    // print_cards(deck, LENGTH_DECK);

    Player * players_list = create_players_list(NUM_PLAYERS, LENGTH_HANDS);
    strcpy(players_list[0].name , "Duck");
    strcpy(players_list[1].name , "Bob");
    strcpy(players_list[2].name , "Kevin");
    strcpy(players_list[3].name , "Sarah");

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

    /*
    players_list[0].player_hands[0].number = (Number) 11;
    players_list[0].player_hands[0].suit = (Suit) 3;
    players_list[0].player_hands[1].number = (Number) 4;
    players_list[0].player_hands[1].suit = (Suit) 1;
    players_list[0].player_hands[2].number = (Number) 4;
    players_list[0].player_hands[2].suit = (Suit) 2;
    players_list[0].player_hands[3].number = (Number) 4;
    players_list[0].player_hands[3].suit = (Suit) 3;
    players_list[0].player_hands[4].number = (Number) 4;
    players_list[0].player_hands[4].suit = (Suit) 0;

    players_list[1].player_hands[0].number = (Number) 14;
    players_list[1].player_hands[0].suit = (Suit) 3;
    players_list[1].player_hands[1].number = (Number) 14;
    players_list[1].player_hands[1].suit = (Suit) 2;
    players_list[1].player_hands[2].number = (Number) 3;
    players_list[1].player_hands[2].suit = (Suit) 2;
    players_list[1].player_hands[3].number = (Number) 3;
    players_list[1].player_hands[3].suit = (Suit) 1;
    players_list[1].player_hands[4].number = (Number) 3;
    players_list[1].player_hands[4].suit = (Suit) 0;

    players_list[2].player_hands[0].number = (Number) 14;
    players_list[2].player_hands[0].suit = (Suit) 1;
    players_list[2].player_hands[1].number = (Number) 13;
    players_list[2].player_hands[1].suit = (Suit) 1;
    players_list[2].player_hands[2].number = (Number) 5;
    players_list[2].player_hands[2].suit = (Suit) 1;
    players_list[2].player_hands[3].number = (Number) 7;
    players_list[2].player_hands[3].suit = (Suit) 1;
    players_list[2].player_hands[4].number = (Number) 9;
    players_list[2].player_hands[4].suit = (Suit) 1;

    players_list[3].player_hands[0].number = (Number) 14;
    players_list[3].player_hands[0].suit = (Suit) 1;
    players_list[3].player_hands[1].number = (Number) 10;
    players_list[3].player_hands[1].suit = (Suit) 1;
    players_list[3].player_hands[2].number = (Number) 13;
    players_list[3].player_hands[2].suit = (Suit) 1;
    players_list[3].player_hands[3].number = (Number) 11;
    players_list[3].player_hands[3].suit = (Suit) 1;
    players_list[3].player_hands[4].number = (Number) 12;
    players_list[3].player_hands[4].suit = (Suit) 1;
    */

    printf("-----------------------START-----------------------\n\n");
    for(int j = 0; j < NUM_PLAYERS; j++)
    {
        sort_hands(players_list[j].player_hands, LENGTH_HANDS);
        printf("%s:\t", players_list[j].name);
        print_cards(players_list[j].player_hands, LENGTH_HANDS);
    }
    printf("\n");

    printf("----------------------CHANGE-----------------------\n\n");

    // change_card(deck, players_list[0], 0);
    // change_card(deck, players_list[0], 4);
    AI_change_cards(deck, players_list);

    for(int j = 0; j < NUM_PLAYERS; j++)
    {
        sort_hands(players_list[j].player_hands, LENGTH_HANDS);
        printf("%s:\t", players_list[j].name);
        print_cards(players_list[j].player_hands, LENGTH_HANDS);
    }
    printf("\n");

    printf("---------------------SHOWDOWN---------------------\n\n");
    showdown(players_list);

    free_deck(deck);
    free(players_list);
    return 0;
}