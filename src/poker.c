#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "poker.h"

int position_deck = 0;

struct deck_52 * create_deck_52() {
    srand((unsigned)time(NULL));
    struct deck_52 * deck = malloc(sizeof(struct card) * LENGTH_DECK);

    int position = 0;
    for (int card_number = 2; card_number < 15; card_number++) {
        for(int card_suit = 0; card_suit < 4; card_suit++) {
            deck->cards[position].number = (Number) card_number;
            deck->cards[position].suit = (Suit) card_suit;
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

void shuffle_deck(struct deck_52 * a, int length) {
    a->position_deal = 0;
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

void print_cards(struct card * a, int length) {
    for (int j = 0; j < length; j++) {
        if(a[j].number == 14){
            printf("A");
        }
        else if(a[j].number == 11){
            printf("J");
        }
        else if(a[j].number == 12){
            printf("Q");
        }
        else if(a[j].number == 13){
            printf("K");
        }
        else{
            printf("%d", a[j].number);
        }

        if(a[j].suit == 0){
            printf(" \u2665");
        }
        else if(a[j].suit == 1){
            printf(" \u2666");
        }
        else if(a[j].suit == 2){
            printf(" \u2663");
        }
        else{
            printf(" \u2660");
        }
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

    for(int i = 0; i < length; i++) {
        min_pos = i;
        for (int j = i+1; j < length; j++) {
            if (a[j].number < a[min_pos].number) {
                min_pos = j;
            }
        }
        swap(&a[i], &a[min_pos]);
    }

    for(int i = 0; i < length; i++) {
        min_pos = i;
        for (int j = i+1; j < length; j++) {
            if(a[j].number == a[min_pos].number){
                if (a[j].suit < a[min_pos].suit) {
                    min_pos = j;
                }
            }
        }
        swap(&a[i], &a[min_pos]);
    }
}

struct player_5draw create_player_5draw(int length_hands) {
    struct player_5draw player;
    for (int j = 0; j < length_hands; j++){
        player.player_hands[j].number = (Number) 0;
    }
    return player; // WARNING
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

int check_flush(struct card * hands, int length){
    int check = 0;
    for(int j = 1; j < length; j++){
        if(hands[j].suit == hands[j - 1].suit){
            check = 1;
        }
        else{
            check = 0;
        }
    }
    return check;
}

int check_straight(struct card * hands, int length){
    int check = 0;
    for(int j = 1; j < length; j++){
        if(j == length - 1 && hands[j].number == ACE){
            if(hands[0].number == 2 && check == 1){
                return check;
            }
            else{
                check = 0;
            }
        }

        if(hands[j].number - 1 == hands[j-1].number){
            check = 1;
        }
        else{
            check = 0;
        }
    }
    return check;
}


int check_four(struct card * hands, int length){

}

int check_three(struct card * hands, int length){

}

struct poker_hands check_pairs(struct card * hands, int length){
    int temp[length];
    memset(temp, 0, sizeof(int) * length);
    int count[length];
    memset(count, 0, sizeof(int) * length);
    int position = 1;
    for(int j = 0; j < length; j++) {
        if (j == 0) {
            temp[0] = hands[j].number;
            count[0]++;
        }
        else{
            int check = 0;
            for(int i = 0; i < j; i ++){
                if(hands[j].number == temp[i]){
                    check = 1;
                    count[i]++;
                    break;
                }
            }
            if(check == 0){
                temp[position] = hands[j].number;
                count[position]++;
                position++;
            }
        }
    }

    // Print
    for(int i = 0; i < length; i++){
        printf("%d %d\n", temp[i], count[i]);
    }

    int num_pair = 0;
    for( int j = 0; j < length; j++){
        if(j[0] == 2){

        }
    }
}

int check_high_card(struct card * hands, int length){

}

struct poker_hands showdown(struct card * hands, int length){
    int flush = check_flush(hands, length);
    int straight = check_straight(hands, length);
    struct poker_hands result;
    if(flush){
        result.hands = FLUSH;
        printf("flush");
    }

    if(straight){
        result.hands = STRAIGHT;
        printf("straight");
    }

    if(flush && straight) {
        if (hands[5].number == ACE) {
            result.hands = ROYAL_FLUSH;
        }
        else {
            result.hands = STRAIGHT_FLUSH;
        }
        return result;
    }


    return result;
}