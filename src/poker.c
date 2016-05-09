#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "poker.h"

void showdown(Player *list) {
    for (int j = 0; j < NUM_PLAYERS; j++) {
        printf("%s:\n", list[j].name);
        list[j].result.hands = HIGH_CARD;
        list[j].result.high_card = list[j].player_hands[LENGTH_HANDS - 1].number;

        check_straight_flush(&list[j]);
        check_pairs(&list[j]);

        printf("High card - %d\n", list[j].result.high_card);

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
            printf("Three of a kind - %d\n", list[j].result.high_card);
        }
        else if (list[j].result.hands == TWO_PAIRS) {
            printf("Two pairs - %d and %d\n", list[j].result.pair_1, list[j].result.pair_2);
        }
        else if (list[j].result.hands == PAIR) {
            printf("A pair - %d\n", list[j].result.pair_1);
        }
        printf("\n");
    }
    int top_rank = compare_hands(list, NUM_PLAYERS);

    printf("Player(s) with the best hands:");
    for (int j = 0; j < NUM_PLAYERS; j++) {
        if (list[j].rank == top_rank) {
            printf(" %s", list[j].name);
        }
    }
    printf("\n");
}

void AI_change_cards(Deck *deck, Player *list) {
    for (int j = 0; j < list->length; j++) {
        if (list[j].type == AI_NORMAL) {
            AI_normal_change(deck, list[j]);
        }
        else if (list[j].type == AI_EASY) {
            AI_easy_change(deck, list[j]);
        }
    }
}

void AI_normal_change(Deck * deck, Player player) {
    int position[LENGTH_HANDS];
    int index = 0;
    memset(position, -1, sizeof(int) * LENGTH_HANDS);
    check_straight_flush(&player);
    check_pairs(&player);
    if (player.result.hands < 4) {
        if (player.result.hands == THREE_OF_A_KIND) {
            for (int i = 0; i < LENGTH_HANDS; i++) {
                if (player.player_hands[i].number != player.result.high_card) {
                    position[index] = i;
                    index++;
                }
            }
        }
        else if (player.result.hands == TWO_PAIRS) {
            for (int i = 0; i < LENGTH_HANDS; i++) {
                if (player.player_hands[i].number != player.result.pair_1 &&
                    player.player_hands[i].number != player.result.pair_2) {
                    position[index] = i;
                    index++;
                }
            }
        }
        else if (player.result.hands == PAIR) {
            for (int i = 0; i < LENGTH_HANDS; i++) {
                if (player.player_hands[i].number != player.result.pair_1) {
                    position[index] = i;
                    index++;
                }
            }
        }
        else {
            // Check if the hands has 4 cards of the same suit
            int index_suit = 0;
            int check[] = {1, 1};
            int suit[] = {-1, -1};
            suit[0] = player.player_hands[0].suit;
            for (int z = 1; z < LENGTH_HANDS; z++) {
                if (player.player_hands[z].suit == suit[0]) {
                    check[0]++;
                }
                else if (suit[1] != -1  && player.player_hands[z].suit == suit[1]) {
                    check[1]++;
                }
                else {
                    index_suit++;
                    if (index < 2) {
                        suit[index_suit] = player.player_hands[z].suit;
                    }
                    else {
                        break;
                    }
                }
            }
            if (check[0] == LENGTH_HANDS - 1) {
                for (int i = 0; i < LENGTH_HANDS; i++) {
                    if (player.player_hands[i].suit != suit[0]) {
                        position[index] = i;
                        index++;
                        break;
                    }
                }
            }
            else if (check[1] == LENGTH_HANDS - 1) {
                for (int i = 0; i < LENGTH_HANDS; i++) {
                    if (player.player_hands[i].suit != suit[1]) {
                        position[index] = i;
                        index++;
                        break;
                    }
                }
            }
            else {
                for (int i = 0; i < LENGTH_HANDS - 1; i++) {
                    position[index] = i;
                    index++;
                }
            }
        }
    }

    for (int n = 0; n < index; n++) {
        change_card(deck, player, position[n]);
        // printf("%d ", position[n]);
    }
    printf("\n");
}

void AI_easy_change(Deck *deck, Player player) {
    srand((unsigned) time(NULL));
    for (int n = 0; n < LENGTH_HANDS; n++) {
        int r = rand() % 2;
        if (r == 1) {
            change_card(deck, player, n);
        }
    }
}


