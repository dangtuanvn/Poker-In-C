#include <stdio.h>
#include <stdlib.h>

#include "poker.h"

int main(){
    struct deck_52 * deck = create_deck_52();
    // print_cards(deck, LENGTH_DECK);
    shuffle_deck(deck, LENGTH_DECK);
    // print_cards(deck, LENGTH_DECK);

    struct player_5draw * players_list = create_players_list_5draw(NUM_PLAYERS, LENGTH_HANDS_5DRAW);

for(int j = 0; j < LENGTH_HANDS_5DRAW; j++){
    for(int i = 0; i < NUM_PLAYERS; i++) {
        deal_card(deck->cards, players_list[i].player_hands, LENGTH_HANDS_5DRAW);
    }
}
for(int j = 0; j < 1; j++)
{
    print_cards(players_list[j].player_hands, LENGTH_HANDS_5DRAW);
}
//    change_card(deck, players_list[0].player_hands, 0);

    players_list[0].player_hands[0].number = (Number) ACE;
    players_list[0].player_hands[0].suit = (Suit) 0;
    players_list[0].player_hands[1].number = (Number) KING;
    players_list[0].player_hands[1].suit = (Suit) 0;
    players_list[0].player_hands[2].number = (Number) JACK;
    players_list[0].player_hands[2].suit = (Suit) 0;
    players_list[0].player_hands[3].number = (Number) 10;
    players_list[0].player_hands[3].suit = (Suit) 0;
    players_list[0].player_hands[4].number = (Number) QUEEN;
    players_list[0].player_hands[4].suit = (Suit) 0;

    sort_hands(players_list[0].player_hands, LENGTH_HANDS_5DRAW);
    print_cards(players_list[0].player_hands, LENGTH_HANDS_5DRAW);

    struct poker_hands check = showdown(players_list[0].player_hands, LENGTH_HANDS_5DRAW);
    printf("%d\n", check.hands);
    free(deck);
    free(players_list);
    check_pairs(players_list[0].player_hands, LENGTH_HANDS_5DRAW);
    return 0;
}