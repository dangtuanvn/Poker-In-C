//
// Created by bit on 4/27/16.
//

#include <stdio.h>
#include "card.h"

void swap(Card *x, Card *y) {
    Card tmp = *x;
    *x = *y;
    *y = tmp;
}


void print_cards(Card *a, int length) {
    for (int j = 0; j < length; j++) {
        if (a[j].number == 14) {
            printf("A");
        }
        else if (a[j].number == 11) {
            printf("J");
        }
        else if (a[j].number == 12) {
            printf("Q");
        }
        else if (a[j].number == 13) {
            printf("K");
        }
        else {
            printf("%d", a[j].number);
        }

        if (a[j].suit == 0) {
            printf(" \u2665");
        }
        else if (a[j].suit == 1) {
            printf(" \u2666");
        }
        else if (a[j].suit == 2) {
            printf(" \u2663");
        }
        else {
            printf(" \u2660");
        }
        printf("  ");
    }
    printf("\n");
}

void sort_hands(Card *a, int length) {
    int min_pos;

    for (int i = 0; i < length; i++) {
        min_pos = i;
        for (int j = i + 1; j < length; j++) {
            if (a[j].number < a[min_pos].number) {
                min_pos = j;
            }
        }
        swap(&a[i], &a[min_pos]);
    }

    for (int i = 0; i < length; i++) {
        min_pos = i;
        for (int j = i + 1; j < length; j++) {
            if (a[j].number == a[min_pos].number) {
                if (a[j].suit < a[min_pos].suit) {
                    min_pos = j;
                }
            }
        }
        swap(&a[i], &a[min_pos]);
    }
}