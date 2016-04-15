#include <stdio.h>
#include <stdlib.h>

#include "poker.h"

int main(){
    struct card * deck = create_deck();
    // print_cards(deck, LENGTH_DECK);
    shuffle_deck(deck, LENGTH_DECK);
    // print_cards(deck, LENGTH_DECK);

    struct player_5draw * players_list = create_players_list_5draw(NUM_PLAYERS, LENGTH_HANDS_5DRAW);

for(int j = 0; j < LENGTH_HANDS_5DRAW; j++){
    for(int i = 0; i < NUM_PLAYERS; i++) {
        deal_card(deck, players_list[i].player_hands, LENGTH_HANDS_5DRAW);
    }
}

for(int j = 0; j < 1; j++)
{
    print_cards(players_list[j].player_hands, LENGTH_HANDS_5DRAW);
}
    change_card(deck, players_list[0].player_hands, 0);
print_cards(players_list[0].player_hands, LENGTH_HANDS_5DRAW);


    free(deck);
    free(players_list);
    return 0;
}