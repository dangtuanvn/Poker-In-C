#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "poker.h"

struct deck * create_deck() {
    srand((unsigned)time(NULL));
    struct deck * deck = malloc(sizeof(struct deck));
    deck->cards = malloc(sizeof(struct card) * LENGTH_DECK);
    deck->top = LENGTH_DECK - 1;
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

void shuffle_deck(struct deck * a, int length) {
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
        printf("  ");
    }
    printf("\n");
}

void deal_card(struct deck * deck, struct player target, int length_hands){
    for(int j = 0; j < length_hands; j++) {
        if (target.player_hands[j].number == 0) {
            target.player_hands[j] = deck->cards[deck->top];
            deck->top--;
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

struct player create_player(int length_hands) {
    struct player * player = malloc(sizeof(struct player));
    player->length = length_hands;
    player->rank = 0;
    player->chips = STARTING_CHIPS;
    player->player_hands = malloc(sizeof(struct card) * length_hands);
    memset(player->player_hands, 0, sizeof(struct card) * length_hands);
    /*for (int j = 0; j < length_hands; j++){
        player->player_hands[j].number = (Number) 0;
    }*/
    return * player; // WARNING
}

struct player * create_players_list(int num_players, int length_hands)
{
    struct player * players_list = malloc(sizeof(struct player)*num_players);
    for(int j = 0; j < num_players; j++)
    {
        players_list[j] = create_player(length_hands);
    }
    return players_list;
}

void change_card(struct deck * deck, struct player target, int position_card){
    target.player_hands[position_card].number = (Number) 0;
    deal_card(deck, target, LENGTH_HANDS);
}

 void check_straight_flush(struct player * player){
    int check_straight = 0;
    for(int j = 1; j < LENGTH_HANDS; j++){
        if(j == LENGTH_HANDS - 1 && player->player_hands[j].number == ACE)
        {
            if(player->player_hands[0].number != 2 && player->player_hands[0].number != 10){
                check_straight = 0;
            }
        }
        else if(player->player_hands[j].number - 1 == player->player_hands[j-1].number){
            check_straight = 1;
        }
        else{
            check_straight = 0;
            break;
        }
    }

    if(check_straight == 1)
    {
        player->result.hands = STRAIGHT;
    }

     int check_flush = 0;
     for(int j = 1; j < LENGTH_HANDS; j++){
         if(player->player_hands[j].suit == player->player_hands[j - 1].suit){
             check_flush = 1;
         }
         else{
             check_flush = 0;
             break;
         }
     }
     if(check_flush == 1 && player->result.hands == STRAIGHT)
     {
         if (player->player_hands[0].number == 10) {
             player->result.hands = ROYAL_FLUSH;
         }
         else{
             player->result.hands = STRAIGHT_FLUSH;
         }
     }
     else if (check_flush == 1)
     {
         player->result.hands = FLUSH;
     }
}

void check_pairs(struct player * player){
    int temp[LENGTH_HANDS];
    memset(temp, 0, sizeof(int) * LENGTH_HANDS);
    int count[LENGTH_HANDS];
    memset(count, 0, sizeof(int) * LENGTH_HANDS);
    int position = 1;

    for(int j = 0; j < LENGTH_HANDS; j++) {
        if (j == 0) {
            temp[0] = player->player_hands[j].number;
            count[0]++;
        }
        else{
            int check = 0;
            for(int i = 0; i < j; i ++){
                if(player->player_hands[j].number == temp[i]){
                    check = 1;
                    count[i]++;
                    break;
                }
            }
            if(check == 0){
                temp[position] = player->player_hands[j].number;
                count[position]++;
                position++;
            }
        }
    }

    // Print
/*
    for(int i = 0; i < LENGTH_HANDS; i++){
        printf("%d %d,", temp[i], count[i]);
    }
*/
    int count_pair = 0;
    int three_of_a_kind = 0;
    for(int j = 0; j < LENGTH_HANDS; j++)
    {
        if(count[j] == 2)
        {
            if(count_pair == 0){
                player->result.hands = PAIR;
                player->result.pair_1 = (Number) temp[j];
                count_pair++;
            }
            else{
                player->result.hands = TWO_PAIRS;
                player->result.pair_2 = (Number) temp[j];
                count_pair++;
            }
        }
        if(count[j] == 3) {
            player->result.high_card = (Number) temp[j];
            player->result.hands = THREE_OF_A_KIND;
            three_of_a_kind++;
        }
        if(count[j] == 4){
            player->result.high_card = (Number) temp[j];
            player->result.hands = FOUR_OF_A_KIND;
        }
    }
    if(three_of_a_kind == 1 && count_pair == 1){
            player->result.hands = FULL_HOUSE;
    }
}

void showdown(struct player * list){
    for(int j = 0; j < NUM_PLAYERS; j++) {
        list[j].result.hands = HIGH_CARD;
        list[j].result.high_card = list[j].player_hands[LENGTH_HANDS - 1].number;

        check_straight_flush(&list[j]);
        check_pairs(&list[j]);

        printf("High card: %d\n", list[j].result.high_card);

        if (list[j].result.hands == ROYAL_FLUSH) {
            printf("Royal flush\n");
        }
        else if (list[j].result.hands == STRAIGHT_FLUSH) {
            printf("Straight flush\n");
        }
        else if (list[j].result.hands == FOUR_OF_A_KIND) {
            printf("Four of a kind\n");
        }
        else if (list[j].result.hands == FULL_HOUSE) {
            printf("Full house\n");
        }
        else if (list[j].result.hands == FLUSH) {
            printf("Flush\n");
        }
        else if (list[j].result.hands == STRAIGHT) {
            printf("Straight\n");
        }
        else if (list[j].result.hands == THREE_OF_A_KIND) {
            printf("Three of a kind: %d\n", list[j].result.high_card);
        }
        else if (list[j].result.hands == TWO_PAIRS) {
            printf("Two pairs: %d and %d\n", list[j].result.pair_1, list[j].result.pair_2);
        }
        else if (list[j].result.hands == PAIR) {
            printf("A pair: %d\n", list[j].result.pair_1);
        }
    }
    int max = compare_hands(list, NUM_PLAYERS);

    for(int j = 0; j < NUM_PLAYERS; j++){
        if(list[j].rank == max){
            printf("%d", j);
        }
    }

}

int compare_hands(struct player * list, int length){
    int max = 0;
    list[0].rank = 1;
    for (int j  = 1; j < length; j++){
        if(list[max].result.hands < list[j].result.hands){
            list[j].rank = list[max].rank + 1;
            max = j;
            printf("a");
        }
        else if(list[max].result.hands == list[j].result.hands){
            if(list[max].result.hands == PAIR){
                if(list[max].result.pair_1 < list[j].result.pair_1){
                    list[j].rank = list[max].rank + 1;
                    max = j;
                    printf("b");
                }
                else if(list[max].result.pair_1 == list[j].result.pair_1){
                    if(list[max].result.high_card < list[j].result.high_card){
                        list[j].rank = list[max].rank + 1;
                        max = j;
                        printf("c");
                    }
                    else if(list[max].result.high_card == list[j].result.high_card){
                        list[j].rank = list[max].rank;
                        printf("d");
                    }
                }
            }

            if(list[max].result.hands == TWO_PAIRS){
                if(list[max].result.pair_2 < list[j].result.pair_2){
                    list[j].rank = list[max].rank + 1;
                    max = j;
                    printf("e");
                }
                else if(list[max].result.pair_2 == list[j].result.pair_2){
                    if(list[max].result.pair_1 < list[j].result.pair_1){
                        list[j].rank = list[max].rank + 1;
                        max = j;
                        printf("f");
                    }
                    else if(list[max].result.pair_1 == list[j].result.pair_1){
                        if(list[max].result.high_card < list[j].result.high_card){
                            list[j].rank = list[max].rank + 1;
                            max = j;
                            printf("g");
                        }
                        else if(list[max].result.high_card == list[j].result.high_card){
                            list[j].rank = list[max].rank;
                            printf("h");
                        }
                    }
                }
            }

            if(list[max].result.hands == THREE_OF_A_KIND){
                if(list[max].result.high_card < list[j].result.high_card){
                    list[j].rank = list[max].rank + 1;
                    max = j;
                }
                else if(list[max].result.high_card == list[j].result.high_card){
                    list[j].rank = list[max].rank;
                }
            }

            if(list[max].result.hands == FOUR_OF_A_KIND){
                if(list[max].result.high_card < list[j].result.high_card){
                    list[j].rank = list[max].rank + 1;
                    max = j;
                }
                else if(list[max].result.high_card == list[j].result.high_card){
                    list[j].rank = list[max].rank;
                }
            }

            if(list[max].result.hands == STRAIGHT){
                if(list[max].result.high_card < list[j].result.high_card){
                    list[j].rank = list[max].rank + 1;
                    max = j;
                }
                else if(list[max].result.high_card == list[j].result.high_card){
                    list[j].rank = list[max].rank;
                } // WARNING 12345 and 10JQKA
            }

            if(list[max].result.hands == FLUSH){
                if(list[max].result.high_card < list[j].result.high_card){
                    list[j].rank = list[max].rank + 1;
                    max = j;
                }
                else if(list[max].result.high_card == list[j].result.high_card){
                    list[j].rank = list[max].rank;
                }
            }

            if(list[max].result.hands == FULL_HOUSE){
                if(list[max].result.high_card < list[j].result.high_card){
                    list[j].rank = list[max].rank + 1;
                    max = j;
                }
                else if(list[max].result.high_card == list[j].result.high_card){
                    list[j].rank = list[max].rank;
                }
            }

            if(list[max].result.hands == STRAIGHT_FLUSH){
                if(list[max].result.high_card < list[j].result.high_card){
                    list[j].rank = list[max].rank + 1;
                    max = j;
                }
                else if(list[max].result.high_card == list[j].result.high_card){
                    list[j].rank = list[max].rank;
                }
            }

            if(list[max].result.hands == ROYAL_FLUSH){
                list[j].rank = list[max].rank;
            }
        }
    }
    printf("Rank: %d  ", list[max].rank);
    printf("Position: %d  ", max);
    return list[max].rank;
}

void free_deck(struct deck * deck){
    free(deck->cards);
    free(deck);
}