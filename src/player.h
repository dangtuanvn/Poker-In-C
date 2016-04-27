//
// Created by bit on 4/27/16.
//

#ifndef COSC2451_A2_S3500286_S3500291_PLAYER_H
#define COSC2451_A2_S3500286_S3500291_PLAYER_H

#endif //COSC2451_A2_S3500286_S3500291_PLAYER_H
#include "deck.h"

#define     STARTING_CHIPS      3000
#define     LENGTH_HANDS        5

/* Using enum to define player' status
 */
enum status {
    BUST, FOLD, ACTIVE, CHECKED, BET, RAISE
};
typedef enum status Status;

/* Using enum to define player' type
 */
enum player_type {
    HUMAN, AI_NORMAL, AI_EASY
};
typedef enum player_type Player_type;

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

/* Change the card that the player wishes to change in change phase
 * @param deck is the deck used to deal cards
 * @param target is the player who wishes to change card
 * @param position_card is the position of the card in the player's hand
 */
void change_card(Deck * deck, Player target, int position_card);

/* Deal a card to a player
 * @param deck is the deck used to deal the card
 * @param target is the player to receive the card
 * @param n is the number of card to give out
 */
void deal_card(Deck * deck, Player target, int n);

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
/* Compare a list of hands and choose the player with the best hands
 * The hands should already be checked with check_straight_flush and check_pairs
 * @param list is the list of the player
 * @param length is the number of players
 */
int compare_hands(Player * list, int length);

