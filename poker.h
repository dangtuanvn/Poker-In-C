#ifndef COSC2451_A2_S3500286_S3500291_POKER_H
#define COSC2451_A2_S3500286_S3500291_POKER_H

#define     LENGTH_DECK         52
#define     LENGTH_HANDS_5DRAW  5

enum numbers {
    ACE = 1,
    JACK = 11,
    QUEEN = 12,
    KING = 13
};

typedef enum numbers Number;
enum suits {
    HEART, DIAMOND, CLUB, SPADE
};
typedef enum suits Suit;

struct card {
    Number number;
    Suit suit;
};

/* Shuffle a deck of cards Fisher and Yates algorithm
 * @param a is the deck, which is an array of integer
 * @param length is the number of cards in the deck, which is the length of the array
 */
void shuffle_deck(struct card * a, int length);

/* Sort the cards in the hands of a player
 * @param a is the cards, which is an array of integer
 * @param length is the number of cards, which is the length of the array
 */
void sort_hands(struct card * a, int length);

/* Check the cards in the player's hands
 * @param a is the cards, which is an array of integer
 * @param length is the number of cards, which is the length of the array
 */
void showdown(struct card * a, int length);

/* Create a deck of 52 cards
 */
struct card * create_deck();

/*
 *
 */
void print_cards(struct card * a, int length);

/*
 *
 */
void deal_card(struct card * deck, struct card * player, int length_hands);


void swap_cards(struct card * a, int length);

struct card * create_player(int length_hands);


#endif //COSC2451_A2_S3500286_S3500291_POKER_H
