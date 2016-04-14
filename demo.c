#include <stdio.h>
#include <stdlib.h>

#include "poker.h"

int main(){
    struct card *deck = create_deck();
    // print_cards(deck, LENGTH_DECK);
    shuffle_deck(deck, LENGTH_DECK);
    // print_cards(deck, LENGTH_DECK);

    struct card *player1 = create_player(LENGTH_HANDS_5DRAW);
    struct card *player2 = create_player(LENGTH_HANDS_5DRAW);
    struct card *player3 = create_player(LENGTH_HANDS_5DRAW);
    struct card *player4 = create_player(LENGTH_HANDS_5DRAW);



for(int i = 0; i < LENGTH_HANDS_5DRAW; i++){
    deal_card(deck, player1, LENGTH_HANDS_5DRAW);
}

    print_cards(player1, LENGTH_HANDS_5DRAW);



    free(deck);
    free(player1);
    free(player2);
    free(player3);
    free(player4);
    return 0;
}