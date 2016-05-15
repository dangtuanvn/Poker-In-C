
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "display.h"

int num_players = 4;
int cur_up_down = 0;
int max_up_down = 10;
int min_up_down = 1;
int step_up_down = 1;
Player_type mode = AI_NORMAL;

char * num_player_title = "NUMBER OF PLAYERS";

int card_to_change[LENGTH_HANDS] = {0,0,0,0,0}; // hold card to change

char * player_status[] = {"BUSTED OUT", "FOLD", "ALL IN", "ACTIVE", "CHECK", "BET", "CALL", "RAISE"};

char * main_menu_items[] = {
        "NEW-GAME",
        "LOAD-GAME",
        "CREDIT",
        "EXIT"
};

char * new_game_menu_items[] = {
        "SINGLE-PLAYER",
        "MULTI-PLAYER",
        "MODE",
        "BACK"
};

char * mode_menu_items[] = {
        "EASY",
        "NORMAL",
};


char * credit_menu_items[] = {
        "s3500286 - NguyenThanhDuc",
        "s3500291 - NguyenDangTuan",
        "COSC2451-2016A - ProgrammingTechnique",
        "Lecturer - DenisRinfret",
        "OK"
};

char * SPlay_menu_items[] = {
        "OK",
        "CANCEL"
};

char * title[] = {
        ".._____. .______. ..     _. ..______. ..______.",
        "||     | ||     | ||   _/   ||        ||      |",
        "||     | ||     | || _/     ||        ||      |",
        "||_____| ||     | ||/       ||______. ||______|",
        "||       ||     | ||\\_      ||        ||\\_   ",
        "||       ||     | ||  \\_    ||        ||  \\_ ",
        "||       ||_____| ||    \\_. ||______. ||    \\_.",
        "\n",
        "..___.    ..___   ..____.     .     ..    ..   .\n",
        "||        ||   \\  ||    |    //\\    ||   /||   /\n",
        "||___. == ||    | ||____|   //__\\   ||  / ||  /\n",
        "     |    ||    | ||\\_     //----\\  || /  || /\n",
        ".____|    ||___/  ||  \\_. //      \\ ||/   ||/"
};



Stage create_stage()
{
    Stage s;
    s.num = MAIN_MENU;
    s.selection = 0;
    s.num_selections = MENU_MAIN_NUM_SELECTIONS;
    return s;
}

//print game title
void display_title()
{
    attron(COLOR_PAIR(1));
    for(int i = 0; i < 8; ++i) {
        mvprintw(i + 1, (getmaxx(stdscr) - TITLE_WIDTH) / 2, title[i]);

    }
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(2));
    for(int i = 8; i < 13; ++i) {
        mvprintw(i + 1, (getmaxx(stdscr) - TITLE_WIDTH) / 2, title[i]);

    }
    attroff(COLOR_PAIR(2));
}

//print up_down_menu
void display_up_down_menu(WINDOW *win, Stage *stage, int min, int max, int step, char * title)
{
    wclear(win);
    wattron(win, COLOR_PAIR(3));
    wattron(win, A_BOLD);
    int x = 2;
    int y = 2;
    if(stage != NULL) {
        y = (getmaxy(win) - stage->num_selections) / 2 + 1;
    }
    max_up_down = max;
    min_up_down = min;
    step_up_down = step;

    for(int i = 0; i < getmaxy(win)*getmaxx(win); i++)
    {
        wprintw(win, " ");

    }
    mvwprintw(win, 1, (int) ((getmaxx(win) - strlen(title)) / 2), title);
    wattron(win, A_REVERSE);
    mvwprintw(win, 2, 4, "<");
    mvwprintw(win, 2, getmaxx(win) - 5, ">");
    wattroff(win, A_REVERSE);
    if(cur_up_down < 10){
        mvwprintw(win, 2, (getmaxx(win) - 10)/2 + 5, "%d", cur_up_down);
    }
    else if(cur_up_down < 1000){
        mvwprintw(win, 2, (getmaxx(win) - 10)/2 + 4, "%d", cur_up_down);
    }
    else{
        mvwprintw(win, 2, (getmaxx(win) - 10)/2 + 3, "%d", cur_up_down);
    }


    if(stage != NULL && stage->num != IN_GAME) {
        for (int i = 0; i < stage->num_selections; ++i) {
            if (stage->selection == i) {
                wattron(win, A_REVERSE);
                mvwprintw(win, y, x, "%s", SPlay_menu_items[i]);
                wattroff(win, A_REVERSE);
            }
            else {
                mvwprintw(win, y, x, SPlay_menu_items[i]);
            }
            ++y;
        }
    }
    box(win, 0, 0);
    wrefresh(win);
}

//numplayer += 1
void add_cur_up_down(int a)
{
    cur_up_down += a;
    if(cur_up_down > max_up_down)
    {
        cur_up_down = max_up_down;
    }
    else if(cur_up_down < min_up_down)
    {
        cur_up_down = min_up_down;
    }
    mvprintw(5,3, "%i", cur_up_down);
}

int get_step_up_down()
{
    return  step_up_down;
}

int get_cur_up_down()
{
    return  cur_up_down;
}

//print menu
void display_menu(WINDOW *win, Stage *stage)
{
    wclear(win);
    wattron(win, COLOR_PAIR(3));
    wattron(win, A_BOLD);
    int x = 2;
    int y = (getmaxy(win) - stage->num_selections)/2;

    for(int i = 0; i < getmaxy(win)*getmaxx(win); i++)
    {
        wprintw(win, " ");

    }

    switch (stage->num)
    {
        case MAIN_MENU:
            for(int i = 0; i < stage->num_selections; ++i)
            {
                if(stage->selection == i)
                {	wattron(win, A_REVERSE);
                    mvwprintw(win, y, x, "%s", main_menu_items[i]);
                    wattroff(win, A_REVERSE);
                }
                else
                {
                    mvwprintw(win, y, x, main_menu_items[i]);
                }
                ++y;
            }

            break;
        case NEW_GAME:
            for(int i = 0; i < stage->num_selections; ++i)
            {
                if(stage->selection == i)
                {	wattron(win, A_REVERSE);
                    mvwprintw(win, y, x, "%s", new_game_menu_items[i]);
                    wattroff(win, A_REVERSE);
                }
                else
                {
                    mvwprintw(win, y, x, new_game_menu_items[i]);
                }
                ++y;
            }
            break;
        case MODE:
            for(int i = 0; i < stage->num_selections; ++i)
            {
                if(stage->selection == i)
                {	wattron(win, A_REVERSE);
                    mvwprintw(win, y, x, "%s", mode_menu_items[i]);
                    wattroff(win, A_REVERSE);
                }
                else
                {
                    mvwprintw(win, y, x, mode_menu_items[i]);
                }
                ++y;
            }
            break;
        case SINGLE_PLAYER:
            display_up_down_menu(win, stage, 2, 4, 1, num_player_title);
            break;
        case CREDIT:
            for(int i = 0; i < 4; ++i)
            {
                mvwprintw(win, i + 2, x, credit_menu_items[i]);
            }
            wattron(win, A_REVERSE);
            mvwprintw(win, 7, x, "%s", credit_menu_items[4]);
            wattroff(win, A_REVERSE);
            break;
        case IN_GAME:
            clear();
            break;
        default:
            break;
    }

    box(win, 0, 0);
    wattroff(win, COLOR_PAIR(3));
    wattroff(win, A_BOLD);
    wrefresh(win);
}


//return the selected item
int pointed_item(WINDOW * win, int posX, int posY, Stage stage)
{
    int x = getbegx(win) + 2;
    int y = getbegy(win) + (getmaxy(win) - stage.num_selections)/2;

    switch(stage.num)
    {
        case MAIN_MENU:
            for(int i = 0; i < stage.num_selections; i++)
            {
                if(posY == y + i && posX >= x  && posX < x + strlen(main_menu_items[i]))
                {
                    return i;
                }
            }
            break;
        case NEW_GAME:
            for(int i = 0; i < stage.num_selections; i++)
            {
                if(posY == y + i && posX >= x  && posX < x + strlen(new_game_menu_items[i]))
                {
                    return i;
                }
            }
            break;
        case MODE:
            for(int i = 0; i < stage.num_selections; i++)
            {
                if(posY == y + i && posX >= x  && posX < x + strlen(mode_menu_items[i]))
                {
                    return i;
                }
            }
            break;
        case SINGLE_PLAYER:
            x = getbegx(win) + 2;
            y = getbegy(win) + (getmaxy(win) - stage.num_selections)/2 + 1;
            for(int i = 0; i < stage.num_selections; i++)
            {
                if(posY == y + i && posX >= x  && posX < x + strlen(SPlay_menu_items[i]))
                {
                    return i;
                }
            }
            break;
        default:
            break;
    }
    return -1;
}


//change the display
void change_stage(WINDOW *win, Stage *stage)
{
    switch(stage->num)
    {
        case MAIN_MENU://in Main menu
            switch(stage->selection)
            {
                case 0://select new game item
                    stage->num = NEW_GAME;
                    stage->selection = 0;
                    stage->num_selections = MENU_NEW_NUM_SELECTIONS;
                    display_menu(win, stage);
                    break;
                case 1:
                    display_menu(win, stage);
                    break;
                case 2:
                    stage->num = CREDIT;
                    stage->selection = 0;
                    stage->num_selections = 0;
                    display_menu(win, stage);
                    break;
                case 3:
                    endwin();
                    exit(0);
                default:
                    break;
            }
            break;
        case NEW_GAME://in New Game menu
            switch(stage->selection)
            {
                case 0:
                    cur_up_down = num_players;
                    stage->num = SINGLE_PLAYER;
                    stage->selection = 0;
                    stage->num_selections = MENU_SINGLE_NUM_SELECTIONS;
                    display_menu(win, stage);
                    break;
                case 1:
                    display_menu(win, stage);
                    break;
                case 2:
                    stage->num = MODE;
                    stage->selection = mode;
                    stage->num_selections = MENU_MODE_NUM_SELECTIONS;
                    display_menu(win, stage);
                    break;
                case 3://back to main menu
                    stage->num =MAIN_MENU;
                    stage->selection = 0;
                    stage->num_selections = MENU_MAIN_NUM_SELECTIONS;
                    display_menu(win, stage);
                    break;
                default:
                    break;
            }
            break;
        case MODE://in Mode menu
            switch(stage->selection) {
                case 0:
                    stage->num = NEW_GAME;
                    stage->num_selections = MENU_NEW_NUM_SELECTIONS;
                    mode = AI_EASY;
                    display_menu(win, stage);
                    break;
                case 1:
                    stage->num = NEW_GAME;
                    stage->selection = 0;
                    stage->num_selections = MENU_NEW_NUM_SELECTIONS;
                    mode = AI_NORMAL;
                    display_menu(win, stage);
                    break;
                case 2:
                    stage->num = NEW_GAME;
                    stage->selection = 0;
                    stage->num_selections = MENU_NEW_NUM_SELECTIONS;
                    mode = AI_CHEATER;
                    display_menu(win, stage);
                    break;
                default:
                    break;
            }
            break;
        case SINGLE_PLAYER:
            switch(stage->selection) {
                case 0:
                    stage->num = IN_GAME;
                    stage->selection = 0;
                    num_players = cur_up_down;
                    display_menu(win, stage);
                    reset_select_card();
                    break;
                case 1:
                    stage->num = NEW_GAME;
                    stage->selection = 0;
                    stage->num_selections = MENU_NEW_NUM_SELECTIONS;
                    cur_up_down = num_players;
                    display_menu(win, stage);
                    break;
                default:
                    break;
            }
            break;
        case CREDIT:
            switch(stage->selection) {
                case 0:
                    stage->num = MAIN_MENU;
                    stage->selection = 0;
                    stage->num_selections = MENU_MAIN_NUM_SELECTIONS;
                    display_menu(win, stage);
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}
void select_card_to_change(int position)
{
    int check = 0;
    for(int i = 0; i < LENGTH_HANDS; i++){
        if(card_to_change[i] == 1){
            check++;
        }
    }

    if(card_to_change[position - 1] == 1)
    {
        card_to_change[position - 1] = 0;
    }
    else if (check < 3)
    {
        card_to_change[position - 1] = 1;
    }

}

void display_deck(WINDOW *win, Player player)
{
    wclear(win);
    if(player.status != BUSTED)
    {
        wattron(win, COLOR_PAIR(1));
        wattron(win, A_BOLD);
        box(win, 0, 0);
        wattroff(win, COLOR_PAIR(1));
        wattroff(win, A_BOLD);

        for(int x = 0; x < LENGTH_HANDS; x++) {
            int startX = 1 + x * (CARD_WIDTH + 1);
            int startY = 1;

            char number_suit[6];

            if(player.player_hands[x].number == 2) strcpy(number_suit, "2");
            else if(player.player_hands[x].number == 3) strcpy(number_suit, "3");
            else if(player.player_hands[x].number == 4) strcpy(number_suit, "4");
            else if(player.player_hands[x].number == 5) strcpy(number_suit, "5");
            else if(player.player_hands[x].number == 6) strcpy(number_suit, "6");
            else if(player.player_hands[x].number == 7) strcpy(number_suit, "7");
            else if(player.player_hands[x].number == 8) strcpy(number_suit, "8");
            else if(player.player_hands[x].number == 9) strcpy(number_suit, "9");
            else if(player.player_hands[x].number == 10) strcpy(number_suit, "10");
            else if(player.player_hands[x].number == 11) strcpy(number_suit, "J");
            else if(player.player_hands[x].number == 12) strcpy(number_suit, "Q");
            else if(player.player_hands[x].number == 13) strcpy(number_suit, "K");
            else strcpy(number_suit, "A");

            if(player.player_hands[x].suit == 0) strcat(number_suit, "\u2665");
            else if(player.player_hands[x].suit == 1) strcat(number_suit, "\u2666");
            else if(player.player_hands[x].suit == 2) strcat(number_suit, "\u2663");
            else strcat(number_suit, "\u2660");

            if(player.type == HUMAN && card_to_change[x] == 1)
            {
                startY--;
            }

            for (int i = 0; i < CARD_HEIGHT; i++) {
                if(i == CARD_HEIGHT/2 - 1)
                {
                    wattron(win, COLOR_PAIR(5));
                }
                else
                {
                    wattron(win, COLOR_PAIR(4));
                }
                for (int j = 0; j < CARD_WIDTH; j++) {
                    mvwprintw(win, startY + i, startX + j, " ");
                }
            }

            if(player.player_hands[x].suit == 0 || player.player_hands[x].suit == 1)
            {
                wattron(win, COLOR_PAIR(5));
            }
            else{
                wattron(win, COLOR_PAIR(6));
            }
            mvwprintw(win, startY + 1, startX + (CARD_WIDTH - 2)/2, number_suit);
        }
        wattroff(win, COLOR_PAIR(4));
        wattroff(win, COLOR_PAIR(5));
        wattroff(win, COLOR_PAIR(6));
        wrefresh(win);
    }


}

void update_player_info(WINDOW ** seats, Player ** players, int turn){

    for(int i = 0; i < num_players; i++)
    {
        wattron(seats[i], A_BOLD);
        box(seats[i], 0, 0);

        wattron(seats[i], COLOR_PAIR(1));
        for(int a = 0; a < CARD_WIDTH * 5 + 6; a++)
        {
            mvprintw(getbegy(seats[i]) + getmaxy(seats[i]), getbegx(seats[i]) + a, " ");
        }

        if(i == turn)
        {
            attron(COLOR_PAIR(2));
        }
        mvprintw(getbegy(seats[i]) + getmaxy(seats[i]), getbegx(seats[i]) + 5, "%s", players[i]->name);
        mvprintw(getbegy(seats[i]) + getmaxy(seats[i]), getbegx(seats[i]) + 30, "Chips: %i", players[i]->chips);
        mvprintw(getbegy(seats[i]) + getmaxy(seats[i]) + 1, getbegx(seats[i]) + 42, "          ");
        mvprintw(getbegy(seats[i]) + getmaxy(seats[i]) + 1, getbegx(seats[i]) + 30, "Bet Amount: %i", players[i]->bet_amount);
        mvprintw(getbegy(seats[i]) + getmaxy(seats[i]), getbegx(seats[i]) + 17, "[%s]", player_status[players[i]->status]);

        attroff(COLOR_PAIR(2));
        wattroff(seats[i], COLOR_PAIR(1));
        wattroff(seats[i], A_BOLD);
    }
    refresh();
}

void display_player_seat(WINDOW ** seats, Player ** players, int turn)
{
    for(int i = 1; i < num_players; i++)
    {
        update_player_info(seats, players, turn);

        if(players[i]->status != BUSTED) {
            for (int x = 0; x < LENGTH_HANDS; x++) {
                int startX = 1 + x * (CARD_WIDTH + 1);
                int startY = 1;
                for (int j = 0; j < CARD_HEIGHT; j++) {
                    for (int k = 0; k < CARD_WIDTH; k++) {
                        if (j == 1) {
                            wattron(seats[i], COLOR_PAIR(4));
                        }
                        else {
                            wattron(seats[i], COLOR_PAIR(5));
                        }
                        mvwprintw(seats[i], startY + j, startX + k, " ");
                    }
                }

            }
        }
        else
        {
            wclear(seats[i]);
        }

        wattroff(seats[i], COLOR_PAIR(4));
        wattroff(seats[i], COLOR_PAIR(5));
        wattroff(seats[i], COLOR_PAIR(1));
        box(seats[i],0,0);
        wattroff(seats[i], A_BOLD);

        wrefresh(seats[i]);
    }
}



Player_type get_mode(){
    return mode;
}

int get_num_players()
{
    return num_players;
}

void process_change_card(Deck * deck, Player ** players)
{
    for(int i = 0; i < LENGTH_HANDS; i++)
    {
        if(card_to_change[i] == 1)
        {
            change_card(deck, *players[0], i);
        }
    }
    reset_select_card();
}

void display_chips_rank(Player ** players)
{
    Player ** chips_rank = clone_Player_array(players, num_players);
    sort_players(chips_rank, num_players);

    int startX = 8;
    int startY = 3;
    mvprintw(startY, startX, "%s", "RANKING");
    mvprintw(startY + 1, startX, "%s", "_______________");

    for(int i = num_players - 1; i >= 0; i--)
    {
        if(chips_rank[i]->status == BUSTED)
        {
            mvprintw(startY + 2 + num_players - i, startX, "%s\t[%s]", chips_rank[i]->name, player_status[chips_rank[i]->status]);
            continue;
        }
        mvprintw(startY + 2 + num_players - i, startX, "                         ");
        mvprintw(startY + 2 + num_players - i, startX, "%s\t%i", chips_rank[i]->name, chips_rank[i]->chips);
    }
    free(chips_rank);
}

void display_pot(int a)
{
    mvprintw(getmaxy(stdscr)/2, getmaxx(stdscr)/2 - 3, "POT");
    mvprintw(getmaxy(stdscr)/2 + 2, getmaxx(stdscr)/2 - 3, "          ");
    mvprintw(getmaxy(stdscr)/2 + 2, getmaxx(stdscr)/2 - 3, "%i", a);

}

void display_in_game_stuff(WINDOW * input_win, Player ** players, Game_round * game_round, int turn)
{

    if(turn < 0 || turn > 4)
    {
        return;
    }

    mvprintw(2, getmaxx(stdscr) - 20, "         ");
    mvprintw(4, getmaxx(stdscr) - 20, "                      ");
    mvprintw(getmaxy(stdscr) - 4, getmaxx(stdscr) / 2 - (CARD_WIDTH * 5 + 6) / 2 - 50, "                                                  ");

    if(turn == 0 && (players[turn]->bet_amount == game_round->call_amount)) {
        attron(COLOR_PAIR(3));
        attron(A_BOLD);
        mvprintw(2, getmaxx(stdscr) - 20, " QUIT(Q) ");
        mvprintw(4, getmaxx(stdscr) - 20, " SAVE-AND-QUIT(S) ");
        mvprintw(getmaxy(stdscr) - 4, getmaxx(stdscr) / 2 - (CARD_WIDTH * 5 + 6) / 2 - 47, " CHECK(Z) ");
        mvprintw(getmaxy(stdscr) - 4, getmaxx(stdscr) / 2 - (CARD_WIDTH * 5 + 6) / 2 - 35, " BET(X) ");
        mvprintw(getmaxy(stdscr) - 4, getmaxx(stdscr) / 2 - (CARD_WIDTH * 5 + 6) / 2 - 25, " FOLD(C) ");
        mvprintw(getmaxy(stdscr) - 4, getmaxx(stdscr) / 2 - (CARD_WIDTH * 5 + 6) / 2 - 14, " ALL-IN(V) ");
        display_up_down_menu(input_win, NULL, game_round->call_amount, players[turn]->chips, 10 , "CHIPS AMOUNT");
    }
    else if(turn == 0){
        attron(COLOR_PAIR(3));
        attron(A_BOLD);
        mvprintw(2, getmaxx(stdscr) - 20, " QUIT(Q) ");
        mvprintw(4, getmaxx(stdscr) - 20, " SAVE-AND-QUIT(S) ");
        mvprintw(getmaxy(stdscr) - 4, getmaxx(stdscr) / 2 - (CARD_WIDTH * 5 + 6) / 2 - 48, " CALL(Z) ");
        mvprintw(getmaxy(stdscr) - 4, getmaxx(stdscr) / 2 - (CARD_WIDTH * 5 + 6) / 2 - 37, " RAISE(X) ");
        mvprintw(getmaxy(stdscr) - 4, getmaxx(stdscr) / 2 - (CARD_WIDTH * 5 + 6) / 2 - 25, " FOLD(C) ");
        mvprintw(getmaxy(stdscr) - 4, getmaxx(stdscr) / 2 - (CARD_WIDTH * 5 + 6) / 2 - 14, " ALL-IN(V) ");
        display_up_down_menu(input_win, NULL, game_round->call_amount, players[turn]->chips, 10 , "CHIPS AMOUNT");
    }
    else{
        for(int i = 0; i < 18; i++)
        {
            for(int j = 0; j < 4; j++){
                mvprintw(getmaxy(stdscr) - 9 + j, getmaxx(stdscr) / 2 - (CARD_WIDTH * 5 + 6) / 2 - 35 + i, " ");
            }

        }

    }


    refresh();
    attroff(A_BOLD);
    attroff(COLOR_PAIR(3));
}

void reset_select_card()
{
    for(int j = 0; j < LENGTH_HANDS; j++){
        card_to_change[j] = 0;
    }

}

void update(WINDOW * input_win, WINDOW ** seats, Player ** players, Game_round * game_round, int turn){
    cur_up_down = game_round->call_amount;
    display_chips_rank(players);
    display_pot(game_round->pot);
    display_in_game_stuff(input_win, players, game_round, turn);
    display_player_seat(seats, players, turn);
}

