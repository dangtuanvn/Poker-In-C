#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "poker.h"

int deck_position = 0;

void swap(struct card * x, struct card * y) {
    struct card tmp = *x;
    *x = *y;
    *y = tmp;
}

void shuffle_deck(struct card * a, int length) {
    deck_position = 0;
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
        swap(&a[j], &a[r]);
    }
    // printf("\n");
}

void sort_hands(struct card * a, int length) {
    int min_pos;

    /* find the min value in a[i] to a[length-1], and swap it with a[i] */
    for (int i = 0; i < length; i++) {
        min_pos = i;

        swap(&a[i], &a[min_pos]);
    }
}

struct card * create_deck() {
    struct card * deck = malloc(sizeof(struct card) * LENGTH_DECK);

    int position = 0;
    for (int card_number = 1; card_number < 14; card_number++) {
        for(int card_suit = 0; card_suit < 4; card_suit++) {
            deck[position].number = (Number) card_number;
            deck[position].suit = (Suit) card_suit;
            position++;
        }
    }

    return deck;
}

struct card * create_player(int length_hands) {
    struct card * player = malloc(sizeof(struct card) * length_hands);
    for (int j = 0; j < length_hands; j++){
        player[j].number = (Number) 0;
    }

    return player;
}

void print_cards(struct card * a, int length) {
    for (int j = 0; j < length; j++) {
        printf("%d %d", a[j].number, a[j].suit);
        printf("\n");
    }
}

void deal_card(struct card * deck, struct card * player, int length_hands){
    for(int j = 0; j < length_hands; j++) {
        if (player[j].number == 0) {
            player[j] = deck[deck_position];
            deck_position++;
        }
    }
}



