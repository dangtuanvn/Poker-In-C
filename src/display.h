#ifndef COSC2451_A2_S3500286_S3500291_DISPLAY_H
#define COSC2451_A2_S3500286_S3500291_DISPLAY_H

#include "poker.h"

#define MENU_HEIGHT 10
#define MENU_WIDTH 40
#define MENU_MAIN_NUM_SELECTIONS  4
#define MENU_NEW_NUM_SELECTIONS  4
#define MENU_MODE_NUM_SELECTIONS  2
#define MENU_SINGLE_NUM_SELECTIONS  2
#define TITLE_WIDTH  47
#define TERM_MAX_WIDTH  135
#define TERM_MAX_HEIGHT  30
#define CARD_HEIGHT  5
#define CARD_WIDTH  8

enum stage_num {
    MAIN_MENU = 0,
    NEW_GAME = 1,
    LOAD_GAME = 2,
    HOW_TO_PLAY = 3,
    SINGLE_PLAYER = 4,
    MULTI_PLAYER = 5,
    MODE = 6,
    IN_GAME = 7
};
typedef enum stage_num Stage_Num;


typedef struct display {
    Stage_Num previous;
    Stage_Num num;
    int selection;
    int num_selections;
} Stage;

void change_stage(WINDOW *win, Stage *stage);
void display_title(WINDOW * win);
void display_menu(WINDOW *win, Stage *stage);
void display_player_seat(WINDOW ** seats, Player * players);
void display_deck(WINDOW *win, Player player);
Stage create_stage();
int pointed_item(WINDOW * win, int posX, int posY, Stage stage);

void display_up_down_menu(WINDOW *win, Stage *stage, int min, int max, int step, char *title);
void add_cur_up_down(int a);
int get_step_up_down();
Player_type get_mode();
int get_num_players();
void select_card_to_change(int position);
void process_change_card(Deck * deck, Player * players);



#endif //COSC2451_A2_S3500286_S3500291_DISPLAY_H
