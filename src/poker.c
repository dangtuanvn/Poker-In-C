#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "poker.h"

int position_deck = 0;

struct card * create_deck() {
    srand(time(NULL));
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

void swap(struct card * x, struct card * y) {
    struct card tmp = *x;
    *x = *y;
    *y = tmp;
}

void shuffle_deck(struct card * a, int length) {
    position_deck = 0;
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

void print_cards(struct card * a, int length) {
    for (int j = 0; j < length; j++) {
        printf("%d %d", a[j].number, a[j].suit);
        printf("\n");
    }
    printf("\n");
}

void deal_card(struct card * deck, struct card * target, int length_hands){
    for(int j = 0; j < length_hands; j++) {
        if (target[j].number == 0) {
            target[j] = deck[position_deck];
            position_deck++;
        }
    }
}

void sort_hands(struct card * a, int length) {
    int min_pos;

    /* find the min value in a[i] to a[length-1], and swap it with a[i] */
    for (int i = 0; i < length; i++) {
        min_pos = i;

        swap(&a[i], &a[min_pos]);
    }
}

struct player_5draw create_player_5draw(int length_hands) {
    struct player_5draw player;
    for (int j = 0; j < length_hands; j++){
        player.player_hands[j].number = (Number) 0;
    }
    return player;
}

struct player_5draw * create_players_list_5draw(int num_players, int length_hands)
{
    struct player_5draw * players_list = malloc(sizeof(struct player_5draw)*num_players);
    for(int j = 0; j < num_players; j++)
    {
        players_list[j] = create_player_5draw(length_hands);
    }
    return players_list;
}

void change_card(struct card * deck, struct card * hands, int position_card){
    hands[position_card].number = (Number) 0;
    deal_card(deck, hands, LENGTH_HANDS_5DRAW);
}