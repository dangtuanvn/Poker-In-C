#ifndef COSC2451_A2_S3500286_S3500291_PLAYER_H
#define COSC2451_A2_S3500286_S3500291_PLAYER_H

#include "deck.h"

#define     STARTING_CHIPS      3000
#define     LENGTH_HANDS        5

/** Define player' status
 */
enum status {
    BUSTED, FOLD, ALLIN, ACTIVE, CHECK, BET, CALL, RAISE
};
typedef enum status Status;

/** Define player' type
 */
enum player_type {
    AI_EASY, AI_NORMAL, AI_CHEATER, HUMAN
};
typedef enum player_type Player_type;

/** Define poker hands
 */
enum hands_type {
    HIGH_CARD, PAIR, TWO_PAIRS, THREE_OF_A_KIND, STRAIGHT, FLUSH, FULL_HOUSE, FOUR_OF_A_KIND, STRAIGHT_FLUSH, ROYAL_FLUSH
};
typedef enum hands_type Hands_type;

/** Define poker hands with values used to compare with other hands
 */
typedef struct {
    Hands_type hands; /**< Which type of hands */
    Number high_card; /**< The high card of this hands */
    Number pair_1; /**< The first pair */
    Number pair_2; /**< The second pair */
} Poker_hands;

/** Define player
 */
typedef struct {
    Status status; /**< Status of the player: RAISE, FOLD, etc... */
    int rank; /**< Rank used to compare which player has the best hands */
    int length; /**< The number of cards in the player hands */
    int bet_amount; /**< The number of chips the player have bet in this round */
    Card * player_hands; /**< The current cards in the player hands */
    Poker_hands result; /**< The result of the hands the player has */
    int chips; /**< The number of chips the player has */
    char name[20]; /**< Name of the player */
    Player_type type; /**< Type of the player: HUMAN, AI */
} Player;


/** Create a player
 * @param length_hands is the number of cards in the player's hands
 */
Player * create_player(int length_hands);

/** Create a list of players
 * @param num_players is the number of players
 * @param length_hands is the number of cards in each player's hands
 * @param mode is the player's type
 */
Player ** create_players_list(int num_players, int length_hands, Player_type mode);

/** Free the resources allocated for each player and the player list
 * @param list is the list of players
 * @param num_players is the number of players
 */
void free_players_list(Player **list, int num_players);

/** Change the card that the player wishes to change in change phase
 * @param deck is the deck used to deal cards
 * @param target is the player who wishes to change card
 * @param position_card is the position of the card in the player's hand
 */
void change_card(Deck * deck, Player target, int position_card);

/** Deal a card to a player
 * @param deck is the deck used to deal the card
 * @param target is the player to receive the card
 * @param n is the number of card to give out
 */
void deal_card(Deck * deck, Player target, int n);

/** Check the cards of a player for straight, flush, straight flush or royal flush
 * The cards musts be already sorted
 * @param player is the player to be checked
 */
void check_straight_flush(Player * player);

/** Check the cards of a player for pair, three of a kind, four of a kind, full house
 * The cards musts be already sorted
 * @param player is the player to be checked
 */
void check_pairs(Player * player);

/** Compare a list of hands and choose the player with the best hands
 * The hands should already be checked with check_straight_flush and check_pairs
 * @param list is the list of the player
 * @param length is the number of players
 */
int compare_hands(Player ** list, int length);

/** Print the player info
 * @param player is the player to be printed
 */
void print_player_info(Player player);

/** Swap the players
 * @param x is the first player to be swapped
 * @param y is the second player to be swapped
 */
void swap_players(Player *x, Player *y);

/** Sort the player ranking based on their chips
 * @param a is the player list
 * @param length is the number of players
 */
void sort_players(Player **a, int length);

/** Copy an array of players
 * @param src is the array to be copied
 * @param dst is the array to be pasted to
 * @param length is the number of players
 */
void copy_Player_array(Player **src, Player **dst, int length);

/** Clone an array of players
 * @param a is the array to be cloned
 * @param length is the number of players
 */
Player ** clone_Player_array(Player **a, int length);

#endif //COSC2451_A2_S3500286_S3500291_PLAYER_H
