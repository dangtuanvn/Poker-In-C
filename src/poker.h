#ifndef COSC2451_A2_S3500286_S3500291_POKER_H
#define COSC2451_A2_S3500286_S3500291_POKER_H

#define     LENGTH_DECK         52
#define     LENGTH_HANDS        5
#define     NUM_PLAYERS         4
#define     STARTING_CHIPS      3000

// TYPEDEF, ENUM and STRUCT

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

/* Struct deck with integer top and an array of cards
 */
typedef struct {
    int top;
    Card *cards;
} Deck;

/* Using enum to define poker hands
 */
enum hands_type {
    HIGH_CARD, PAIR, TWO_PAIRS, THREE_OF_A_KIND, STRAIGHT, FLUSH, FULL_HOUSE, FOUR_OF_A_KIND, STRAIGHT_FLUSH, ROYAL_FLUSH
};
typedef enum hands_type Hands_type;

/* Struct poker_hands to store variables
 */
typedef struct {
    Hands_type hands;
    Number high_card;
    Number pair_1;
    Number pair_2;
    int rank;
} Poker_hands;

/* Using enum to define player' type
 */
enum player_type {
    HUMAN, AI_NORMAL, AI_EASY
};
typedef enum player_type Player_type;

/* Using enum to define player' status
 */
enum status {
    BUST, FOLD, ACTIVE, CHECKED, BET, RAISE
};
typedef enum status Status;

/* Struct player with unique variables
 */
typedef struct {
    Status status;
    int rank;
    int length;
    int bet_amount;
    Card * player_hands;
    Poker_hands result;
    int chips;
    char name[20];
    Player_type type;
} Player;

/* Struct game_round with unique variables
 */
typedef struct {
    int round_number;
    int position_turn;
    int pot;
    int call_amount;
    int ante;
    int num_players;
} Game_round;

// FUNCTIONS

/* Create a deck of 52 cards with 13 numbers and 4 suits
 */
Deck * create_deck();

/* Free the resources allocated for a deck of card
 * @param deck is the deck to be released
 */
void free_deck(Deck * deck);

/* Create a player
 * @param length_hands is the number of cards in the player's hands
 */
Player create_player(int length_hands);

/* Create a list of players
 * @param num_players is the number of players
 * @param length_hands is the number of cards in each player's hands
 */
Player * create_players_list(int num_players, int length_hands);

/* Free the resources allocated for each player and the player list
 * @param list is the list of players
 * @param num_players is the number of players
 */
void free_players_list(Player * list, int num_players);

/* Swap the position of the cards
 * @param x is the first card to be swapped
 * @param y is the second card to be swapped with the first card
 */
void swap(Card * x, Card * y);

/* Shuffle a deck of cards Fisher and Yates algorithm
 * @param deck is the deck to be shuffled
 * @param length is the number of cards in the deck, which is the length of the array
 */
void shuffle_deck(Deck * deck, int length);

/* Print out the cards in a deck or hands
 * @param a is the cards to be printed on the screen
 * @param length is the number of cards to be printed
 */
void print_cards(Card * a, int length);

/* Deal a card to a player
 * @param deck is the deck used to deal the card
 * @param target is the player to receive the card
 * @param n is the number of card to give out
 */
void deal_card(Deck * deck, Player target, int n);

/* Sort the cards in the hands of a player
 * @param hands is the cards in the hands to be sorted
 * @param length is the number of cards, which is the length of the array
 */
void sort_hands(Card * hands, int length);

/* Change the card that the player wishes to change in change phase
 * @param deck is the deck used to deal cards
 * @param target is the player who wishes to change card
 * @param position_card is the position of the card in the player's hand
 */
void change_card(Deck * deck, Player target, int position_card);

/* Check the cards of a player for straight, flush, straight flush or royal flush
 * The cards musts be already sorted
 * @param player is the player to be checked
 */
void check_straight_flush(Player * player);

/* Check the cards of a player for pair, three of a kind, four of a kind, full house
 * The cards musts be already sorted
 * @param player is the player to be checked
 */
void check_pairs(Player * player);

/* Determine the hands of each player, then pick the best hands
 * @param list is the list of players
 */
void showdown(Player * list);

/* Compare a list of hands and choose the player with the best hands
 * The hands should already be checked with check_straight_flush and check_pairs
 * @param list is the list of the player
 * @param length is the number of players
 */
int compare_hands(Player * list, int length);

void add_chips(Player player, int chipsToAdd);

void withdraw_chips(Player player, int chipsToWithdraw);

void bet(Game_round round, Player player, int chips);

void fold(Player player);

void call( Game_round round, Player player);

void check(Game_round round, Player player);

void allIn(Player player);

void raise(Player player, int chips);

void AI_change_cards(Deck * deck, Player * list);

void AI_normal_change(Deck * deck, Player player);

void AI_easy_change(Deck * deck, Player player);

#endif //COSC2451_A2_S3500286_S3500291_POKER_H

