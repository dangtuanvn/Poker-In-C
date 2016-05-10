#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"

Player create_player(int length_hands) {
    Player *player = malloc(sizeof(Player));
    player->length = length_hands;
    player->rank = 0;
    player->chips = STARTING_CHIPS;
    player->status = ACTIVE;
    player->player_hands = malloc(sizeof(Card) * length_hands);
    memset(player->player_hands, 0, sizeof(Card) * length_hands);
    /*for (int j = 0; j < length_hands; j++){
        player->player_hands[j].number = (Number) 0;
    }*/
    return *player;
}

Player *create_players_list(int num_players, int length_hands) {
    Player *players_list = malloc(sizeof(Player) * num_players);
    for (int j = 0; j < num_players; j++) {
        players_list[j] = create_player(length_hands);
        if (j == 0) {
            players_list[j].type = HUMAN;
        }
        else if (j == 1) { // WARNING TODO: FIX
            players_list[j].type = AI_NORMAL;
        }
        else {
            players_list[j].type = AI_NORMAL; //TODO: Change to easy
        }
    }
    return players_list;
}

void free_players_list(Player *list, int num_players) {
    for (int j = 0; j < num_players; j++) {
        free(list->player_hands);
        free(&list[j]);
    }
    free(list); // WARNING: double free? TODO: FIX
}



void change_card(Deck *deck, Player target, int position_card) {
    target.player_hands[position_card].number = (Number) 0;
    if (position_card != -1) {
        deal_card(deck, target, LENGTH_HANDS);
    }
}

void deal_card(Deck *deck, Player target, int length_hands) {
    for (int j = 0; j < length_hands; j++) {
        if (target.player_hands[j].number == 0) {
            target.player_hands[j] = deck->cards[deck->top];
            deck->top--;
        }
    }
}

void check_straight_flush(Player * player) {
    int check_straight = 0;
    for (int j = 1; j < LENGTH_HANDS; j++) {
        if (j == LENGTH_HANDS - 1 && player->player_hands[j].number == ACE) {
            if (player->player_hands[0].number != 2 && player->player_hands[0].number != 10) {
                check_straight = 0;
            }
        }
        else if (player->player_hands[j].number - 1 == player->player_hands[j - 1].number) {
            check_straight = 1;
        }
        else {
            check_straight = 0;
            break;
        }
    }

    if (check_straight == 1) {
        player->result.hands = STRAIGHT;
    }

    int check_flush = 0;
    for (int j = 1; j < LENGTH_HANDS; j++) {
        if (player->player_hands[j].suit == player->player_hands[j - 1].suit) {
            check_flush = 1;
        }
        else {
            check_flush = 0;
            break;
        }
    }
    if (check_flush == 1 && player->result.hands == STRAIGHT) {
        if (player->player_hands[0].number == 10) {
            player->result.hands = ROYAL_FLUSH;
        }
        else {
            player->result.hands = STRAIGHT_FLUSH;
        }
    }
    else if (check_flush == 1) {
        player->result.hands = FLUSH;
    }
}

void check_pairs(Player * player) {
    int temp[LENGTH_HANDS];
    memset(temp, 0, sizeof(int) * LENGTH_HANDS);
    int count[LENGTH_HANDS];
    memset(count, 0, sizeof(int) * LENGTH_HANDS);
    int position = 1;

    for (int j = 0; j < LENGTH_HANDS; j++) {
        if (j == 0) {
            temp[0] = player->player_hands[j].number;
            count[0]++;
        }
        else {
            int check = 0;
            for (int i = 0; i < j; i++) {
                if (player->player_hands[j].number == temp[i]) {
                    check = 1;
                    count[i]++;
                    break;
                }
            }
            if (check == 0) {
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
    for (int j = 0; j < LENGTH_HANDS; j++) {
        if (count[j] == 2) {
            if (count_pair == 0) {
                player->result.hands = PAIR;
                player->result.pair_1 = (Number) temp[j];
                count_pair++;
            }
            else {
                player->result.hands = TWO_PAIRS;
                player->result.pair_2 = (Number) temp[j];
                count_pair++;
            }
        }
        if (count[j] == 3) {
            player->result.high_card = (Number) temp[j];
            player->result.hands = THREE_OF_A_KIND;
            three_of_a_kind++;
        }
        if (count[j] == 4) {
            player->result.high_card = (Number) temp[j];
            player->result.hands = FOUR_OF_A_KIND;
        }
    }
    if (three_of_a_kind == 1 && count_pair == 1) {
        player->result.hands = FULL_HOUSE;
    }
}

int compare_hands(Player *list, int length) {
    int max = 0;
    list[0].rank = 1;
    for (int j = 1; j < length; j++) {
        if (list[max].result.hands < list[j].result.hands) {
            list[j].rank = list[max].rank + 1;
            max = j;
        }
        else if (list[max].result.hands == list[j].result.hands) {
            if (list[max].result.hands == PAIR) {
                if (list[max].result.pair_1 < list[j].result.pair_1) {
                    list[j].rank = list[max].rank + 1;
                    max = j;
                }
                else if (list[max].result.pair_1 == list[j].result.pair_1) {
                    if (list[max].result.high_card < list[j].result.high_card) {
                        list[j].rank = list[max].rank + 1;
                        max = j;
                    }
                    else if (list[max].result.high_card == list[j].result.high_card) {
                        list[j].rank = list[max].rank;
                    }
                }
            }

            if (list[max].result.hands == TWO_PAIRS) {
                if (list[max].result.pair_2 < list[j].result.pair_2) {
                    list[j].rank = list[max].rank + 1;
                    max = j;
                }
                else if (list[max].result.pair_2 == list[j].result.pair_2) {
                    if (list[max].result.pair_1 < list[j].result.pair_1) {
                        list[j].rank = list[max].rank + 1;
                        max = j;
                    }
                    else if (list[max].result.pair_1 == list[j].result.pair_1) {
                        if (list[max].result.high_card < list[j].result.high_card) {
                            list[j].rank = list[max].rank + 1;
                            max = j;
                        }
                        else if (list[max].result.high_card == list[j].result.high_card) {
                            list[j].rank = list[max].rank;
                        }
                    }
                }
            }

            if (list[max].result.hands == THREE_OF_A_KIND) {
                if (list[max].result.high_card < list[j].result.high_card) {
                    list[j].rank = list[max].rank + 1;
                    max = j;
                }
                else if (list[max].result.high_card == list[j].result.high_card) {
                    list[j].rank = list[max].rank;
                }
            }

            if (list[max].result.hands == FOUR_OF_A_KIND) {
                if (list[max].result.high_card < list[j].result.high_card) {
                    list[j].rank = list[max].rank + 1;
                    max = j;
                }
                else if (list[max].result.high_card == list[j].result.high_card) {
                    list[j].rank = list[max].rank;
                }
            }

            if (list[max].result.hands == STRAIGHT) {
                if (list[max].result.high_card < list[j].result.high_card) {
                    list[j].rank = list[max].rank + 1;
                    max = j;
                }
                else if (list[max].result.high_card == list[j].result.high_card) {
                    if (list[max].result.high_card == ACE) {
                        if (list[max].player_hands[0].number < list[j].player_hands[0].number) {
                            list[j].rank = list[max].rank + 1;
                            max = j;
                        }
                    }
                    else {
                        list[j].rank = list[max].rank;
                    }
                }
            }

            if (list[max].result.hands == FLUSH) {
                if (list[max].result.high_card < list[j].result.high_card) {
                    list[j].rank = list[max].rank + 1;
                    max = j;
                }
                else if (list[max].result.high_card == list[j].result.high_card) {
                    list[j].rank = list[max].rank;
                }
            }

            if (list[max].result.hands == FULL_HOUSE) {
                if (list[max].result.high_card < list[j].result.high_card) {
                    list[j].rank = list[max].rank + 1;
                    max = j;
                }
                else if (list[max].result.high_card == list[j].result.high_card) {
                    list[j].rank = list[max].rank;
                }
            }

            if (list[max].result.hands == STRAIGHT_FLUSH) {
                if (list[max].result.high_card < list[j].result.high_card) {
                    list[j].rank = list[max].rank + 1;
                    max = j;
                }
                else if (list[max].result.high_card == list[j].result.high_card) {
                    list[j].rank = list[max].rank;
                }
            }

            if (list[max].result.hands == ROYAL_FLUSH) {
                list[j].rank = list[max].rank;
            }
        }
    }
    // printf("Rank: %d  \n", list[max].rank);
    // printf("Position: %d  \n", max);
    return list[max].rank;
}

void print_player_info(Player player){
    printf("%s\n", player.name);
    printf("Status: %d\n", player.status);
    printf("Bet amount: %d\n", player.bet_amount);
    printf("Chips: %d\n", player.chips);
    print_cards(player.player_hands, player.length);

}