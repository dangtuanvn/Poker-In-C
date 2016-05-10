#include "card.h"

#define     LENGTH_DECK         52

/* Struct deck with integer top and an array of cards
 */
typedef struct {
    int top;
    Card *cards;
} Deck;

/* Create a deck of 52 cards with 13 numbers and 4 suits
 */
Deck * create_deck();

/* Free the resources allocated for a deck of card
 * @param deck is the deck to be released
 */
void free_deck(Deck * deck);

/* Shuffle a deck of cards Fisher and Yates algorithm
 * @param deck is the deck to be shuffled
 * @param length is the number of cards in the deck, which is the length of the array
 */
void shuffle_deck(Deck * deck, int length);



