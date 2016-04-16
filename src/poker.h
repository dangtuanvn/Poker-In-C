#ifndef COSC2451_A2_S3500286_S3500291_POKER_H
#define COSC2451_A2_S3500286_S3500291_POKER_H

#define     LENGTH_DECK         52
#define     LENGTH_HANDS_5DRAW  5
#define     NUM_PLAYERS         4

/* Using enum to define card numbers with names
 */
enum numbers {
    JACK = 11,
    QUEEN = 12,
    KING = 13,
    ACE = 14,

};

/* Using enum to define suits
 */
typedef enum numbers Number;

enum suits {
    HEART, DIAMOND, CLUB, SPADE
};
typedef enum suits Suit;

/* Data type card with two variables: number and suit
 */
struct card {
    Number number;
    Suit suit;
};

enum hands_type {
    HIGH_CARD, PAIR, TWO_PAIRS, THREE_OF_A_KIND, STRAIGHT, FLUSH, FULL_HOUSE, FOUR_OF_A_KIND, STRAIGHT_FLUSH, ROYAL_FLUSH
};

typedef enum hands_type Hands_type;

struct poker_hands{
    Hands_type hands;
    Number high_card;
    Number three_of_a_kind;
    Number pair_1;
    Number pair_2;
};

struct deck_52 {
    int position_deal;
    struct card cards[LENGTH_HANDS_5DRAW];
};

struct player_5draw {
    struct card player_hands[LENGTH_HANDS_5DRAW];
};




/* Create a deck of 52 cards
 */
struct deck_52 * create_deck_52();

/* Shuffle a deck of cards Fisher and Yates algorithm
 * @param deck is the deck to be shuffled
 * @param length is the number of cards in the deck, which is the length of the array
 */
void shuffle_deck(struct deck_52 * deck, int length);

/* Swap the cards
 * @param x is the first card to be swapped
 * @param y is the second card to be swapped with the first card
 */
void swap(struct card * x, struct card * y);

/* Print out the cards in a deck or hands
 * @param a is the cards to be printed on the screen
 * @param length is the number of cards to be printed
 */
void print_cards(struct card * a, int length);

/* Deal a card to a player
 * @param deck is the deck used to deal the card
 * @param target is the player to receive the card
 * @param n is the number of card to give out
 */
void deal_card(struct card * deck, struct card * target, int n);

/*
 *
 */
void change_cards(struct card * a, int length);

/* Sort the cards in the hands of a player
 * @param hands is the cards in the hands to be sorted
 * @param length is the number of cards, which is the length of the array
 */
void sort_hands(struct card * hands, int length);

/* Check the cards in the player's hands
 * @param hands is the cards in the hands to be checked
 * @param length is the number of cards, which is the length of the array
 */
struct poker_hands showdown(struct card * hands, int length);

/* Create a player
 * @param length_hands is the number of cards in the player's hands
 */

struct player_5draw create_player_5draw(int length_hands);

struct player_5draw * create_players_list_5draw(int num_players, int length_hands);

void change_card(struct card * deck, struct card * hands, int position_card);

struct poker_hands check_pairs(struct card * hands, int length);

#endif //COSC2451_A2_S3500286_S3500291_POKER_H
