#ifndef COSC2451_A2_S3500286_S3500291_CARD_H
#define COSC2451_A2_S3500286_S3500291_CARD_H

#endif //COSC2451_A2_S3500286_S3500291_CARD_H

/* Using enum to define card numbers with names
 */
enum numbers {
    JACK = 11,
    QUEEN = 12,
    KING = 13,
    ACE = 14,
};
typedef enum numbers Number;

/* Using enum to define suits
 */
enum suits {
    HEART, DIAMOND, CLUB, SPADE
};
typedef enum suits Suit;


/* Struct card with two variables: number and suit
 */
typedef struct {
    Number number;
    Suit suit;
} Card;


/* Swap the position of the cards
 * @param x is the first card to be swapped
 * @param y is the second card to be swapped with the first card
 */
void swap(Card * x, Card * y);

/* Print out the cards in a deck or hands
 * @param a is the cards to be printed on the screen
 * @param length is the number of cards to be printed
 */
void print_cards(Card * a, int length);

/* Sort the cards in the hands of a player
 * @param hands is the cards in the hands to be sorted
 * @param length is the number of cards, which is the length of the array
 */
void sort_hands(Card * hands, int length);

