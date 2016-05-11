
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "display.h"


int num_players = NUM_PLAYERS;
int cur_up_down = 0;
int max_up_down = 10;
int min_up_down = 1;
int step_up_down = 1;
Player_type mode = AI_NORMAL;

//TODO free memory
char * num_player_title = "NUMBER OF PLAYERS";
char * bet_title = "BET AMOUNT";
char * raise_title = "RAISE AMOUNT";

int card_to_change[LENGTH_HANDS] = {0,0,0,0,0};

char * main_menu_items[] = {
        "NEW-GAME",
        "LOAD-GAME",
        "HOW-TO-PLAY",
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
        "NORMAL"
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
void display_title(WINDOW * win)
{
    wclear(win);
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
    wrefresh(win);
}
//print up_down_menu
void display_up_down_menu(WINDOW *win, Stage *stage, int min, int max, int step, char * title)
{
    wclear(win);
    int x = 2;
    int y = (getmaxy(win) - stage->num_selections)/2 + 1;
    max_up_down = max;
    min_up_down = min;
    step_up_down = step;

    for(int i = 0; i < getmaxy(win)*getmaxx(win); i++)
    {
        wprintw(win, " ");

    }

    mvwprintw(win, 1, (int) ((getmaxx(win) - strlen(title)) / 2) + 1, title);
    wattron(win, A_REVERSE);
    mvwprintw(win, 2, (getmaxx(win) - 10)/2, "<");
    mvwprintw(win, 2, (getmaxx(win) - 10)/2 + 10, ">");
    wattroff(win, A_REVERSE);
    mvwprintw(win, 2, (getmaxx(win) - 10)/2 + 5, "%d", cur_up_down);

    for(int i = 0; i < stage->num_selections; ++i)
    {
        if(stage->selection == i)
        {	wattron(win, A_REVERSE);
            mvwprintw(win, y, x, "%s", SPlay_menu_items[i]);
            wattroff(win, A_REVERSE);
        }
        else
        {
            mvwprintw(win, y, x, SPlay_menu_items[i]);
        }
        ++y;
    }
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
}

int get_step_up_down()
{
    return  step_up_down;
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
                    card_to_change[0] = 0;
                    card_to_change[1] = 0;
                    card_to_change[2] = 0;
                    card_to_change[3] = 0;
                    card_to_change[4] = 0;
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
        default:
            break;
    }
}
void select_card_to_change(int position)
{
    if(card_to_change[position - 1] == 1)
    {
        card_to_change[position - 1] = 0;
    }
    else
    {
        card_to_change[position - 1] = 1;
    }

}

void display_deck(WINDOW *win, Player player)
{
    wclear(win);
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

        if(strcmp(player.name, "YOU") == 0 && card_to_change[x] == 1)
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
void display_player_seat(WINDOW ** seats, Player * players)
{
    for(int i = 0; i < num_players; i++)
    {
        wattron(seats[i], COLOR_PAIR(1));

        mvprintw(getbegy(seats[i]) + getmaxy(seats[i]), getbegx(seats[i]) + 5, "%s", players[i].name);
        mvprintw(getbegy(seats[i]) + getmaxy(seats[i]), getbegx(seats[i]) + 30, "Chips: %i", players[i].chips);

        wattron(seats[i], A_BOLD);
        box(seats[i], 0, 0);
        for(int x = 0; x < LENGTH_HANDS; x++) {
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
        wattroff(seats[i], COLOR_PAIR(4));
        wattroff(seats[i], COLOR_PAIR(5));
        wattroff(seats[i], COLOR_PAIR(1));
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

void process_change_card(Deck * deck, Player * players)
{
    for(int i = 0; i < LENGTH_HANDS; i++)
    {
        if(card_to_change[i] == 1)
        {
            change_card(deck, players[0], i);
        }
    }
}





