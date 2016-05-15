#ifndef COSC2451_A2_S3500286_S3500291_DISPLAY_H
#define COSC2451_A2_S3500286_S3500291_DISPLAY_H

#include "poker.h"

#define MENU_HEIGHT 10
#define MENU_WIDTH 40
#define MENU_MAIN_NUM_SELECTIONS  4
#define MENU_NEW_NUM_SELECTIONS  4
#define MENU_MODE_NUM_SELECTIONS  3
#define MENU_SINGLE_NUM_SELECTIONS  2
#define TITLE_WIDTH  47
#define CARD_HEIGHT  5
#define CARD_WIDTH  8
#define MYCOLOR_WHITE 0
#define MYCOLOR_RED 1
#define MYCOLOR_GREEN 2
#define MYCOLOR_YELLOW 3
#define MYCOLOR_BLUE 4
#define MYCOLOR_MAGNETA 5
#define MYCOLOR_BLACK 7

/** Define stage numbers
 */
enum stage_num {
    MAIN_MENU = 0, /**< Main menu stage */
    NEW_GAME = 1, /**< New game menu stage */
    LOAD_GAME = 2, /**< Load game menu stage */
    HOW_TO_PLAY = 3, /**< How to play menu stage */
    SINGLE_PLAYER = 4, /**< Single player menu stage */
    MULTI_PLAYER = 5,  /**< Multi player menu stage */
    MODE = 6, /**< Mode menu stage */
    IN_GAME = 7 /**< In game menu stage */
};
typedef enum stage_num Stage_Num;


typedef struct display {
    Stage_Num num; /**< Stage number */
    int selection; /**< Current selection */
    int num_selections; /**< Total number of selections*/
} Stage;

/** Change the stage of the game
 * @param win is the window to be drawn on
 * @param stage is the next stage to change to
 */
void change_stage(WINDOW *win, Stage *stage);

/** Display the game title
 */
void display_title();

/** Display game menu
 * @param win is the window to be drawn on
 * @param stage is the current stage of the game
 */
void display_menu(WINDOW *win, Stage *stage);

/** Display player seat
 * @param seats is an array holding all players' seat, each seat is a window
 * @param players is an array holding all player
 * @param turn is the current turn of the game
 */
void display_player_seat(WINDOW ** seats, Player ** players, int turn);

/** Update the display of player information
 * @param seats is an array holding all players' seat, each seat is a window
 * @param players is an array holding all player
 * @param turn is the current turn of the game
 */
void update_player_info(WINDOW ** seats, Player ** players, int turn);

/** Display deck of a specific player
 * @param win is a window of player whose deck need to be displayed
 * @param player is a player whose deck need to be displayed
 */
void display_deck(WINDOW *win, Player player);

/** Create game stage
 */
Stage create_stage();

/** Return the current chosen item in a window using mouse
 * @param win is a window that need to work on
 * @param posX is the X coordinate of mouse event
 * @param posY is the Y coordinate of the mouse event
 * @param stage is the game stage
 */
int pointed_item(WINDOW * win, int posX, int posY, Stage stage);

/** Display input menu that have increase and decrease function
 * @param win is a window that need to work on
 * @param stage is the game stage
 * @param min is the minimum value
 * @param max is maximum value
 * @param step is increase and decrease value
 * @param title is title of the menu
 */
void display_up_down_menu(WINDOW *win, Stage *stage, int min, int max, int step, char *title);

/** Change the current value of the up down menu
 * @param a is the value to add
 */
void add_cur_up_down(int a);

/** Get the step of up down menu
 */
int get_step_up_down();

/** Get the mode of the game
 */
Player_type get_mode();

/** Get the number of players of the game
 */
int get_num_players();

/** Change the display of the selected card using card position
 * @param position is the position of the card
 */
void select_card_to_change(int position);

/** Change the card of players
 * @param deck is the main deck of the poker game
 * @param players is an array holding all players
 */
void process_change_card(Deck * deck, Player ** players);

/** Display the rank of players based on their chips
 * @param players is an array holding all players
 */
void display_chips_rank(Player ** players);

/** Display the pot of the game
 * @param amount is the amount to be displayed
 */
void display_pot(int amount);

/** Display game stuff such as button and input menu
 * @param input_win is input window
 * @param players is an array holding all players
 * @param game_round is current game round
 * @param turn is the current position turn of the game
 */
void display_in_game_stuff(WINDOW * input_win, Player ** players, Game_round * game_round, int turn);

/** Reset the temporary array holding selected card to change of player
 */
void reset_select_card();

/** Get the current value in the up down menu
 */
int get_cur_up_down();

/** Update the display of all information of players
 * @param input_win is input window
 * @param seats is an array hold all players' seat, each seat is a window
 * @param players is an array holding all players
 * @param game_round is current game round
 * @param turn is the current position turn of the game
 */
void update(WINDOW * input_win,WINDOW ** seats, Player ** players, Game_round * game_round, int turn);


#endif //COSC2451_A2_S3500286_S3500291_DISPLAY_H
