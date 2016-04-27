#include <stdlib.h>
#include <time.h>
#include "deck.h"

Deck *create_deck() {
    srand((unsigned) time(NULL));
    Deck *deck = malloc(sizeof(Deck));
    deck->cards = malloc(sizeof(Card) * LENGTH_DECK);
    deck->top = LENGTH_DECK - 1;

    // Create cards
    int position = 0;
    for (int card_number = 2; card_number < 15; card_number++) {
        for (int card_suit = 0; card_suit < 4; card_suit++) {
            deck->cards[position].number = (Number) card_number;
            deck->cards[position].suit = (Suit) card_suit;
            position++;
        }
    }
    return deck;
}

void free_deck(Deck *deck) {
    free(deck->cards);
    free(deck);
}


void shuffle_deck(Deck *a, int length) {
    a->top = LENGTH_DECK - 1;
    for (int j = length - 1; j > 0; j--) {
        /* Generate a random number r
         * with 0 <= r <= j
         * http://stackoverflow.com/questions/2509679/how-to-generate-a-random-number-from-within-a-range
         */
        int r;
        unsigned int num_bins = (unsigned int) j + 1;
        unsigned int num_rand = (unsigned int) RAND_MAX + 1;
        unsigned int bin_size = num_rand / num_bins;
        unsigned int defect = num_rand % num_bins;
        int x;
        do {
            x = rand();
        }
        while (num_rand - defect <= (unsigned int) x);
        r = x / bin_size;
        // printf("%ld ", r);
        swap(&a->cards[j], &a->cards[r]);
    }
    // printf("\n");
}