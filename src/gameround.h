#include "player.h"

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

Game_round create_game_round(int num_players);

void round_position_increment(Game_round * round);

void place_ante(Game_round * round, Player * player);

void add_chips(Player * player, int chipsToAdd);

void withdraw_chips(Player * player, int chipsToWithdraw);

void bet(Game_round * round, Player * player, int chips);

void call(Game_round * round, Player * player);

void raise(Game_round * round, Player * player, int chips);

void fold(Game_round * round, Player * player);

void check(Game_round * round, Player * player);

void allIn(Game_round * round, Player * player);