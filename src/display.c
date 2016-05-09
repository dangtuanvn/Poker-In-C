
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "display.h"


int numplayer = 2;
int cur_up_down = 0;
int max_up_down = 10;
int min_up_down = 1;
int step_up_down = 1;

//TODO free memory
char * num_player_title = "NUMBER OF PLAYERS";
char * bet_title = "BET AMOUNT";
char * raise_title = "RAISE AMOUNT";

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
        "NORMAL",
        "HARD"
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

    init_pair(1, COLOR_BLUE, COLOR_WHITE);
    init_pair(2, COLOR_RED, COLOR_WHITE);
    wclear(win);
    attron(COLOR_PAIR(1));
    for(int i = 0; i < 8; ++i) {
        mvprintw(i + 1, (TERM_MAX_WIDTH - TITLE_WIDTH) / 2, title[i]);

    }
    attron(COLOR_PAIR(2));
    for(int i = 8; i < 13; ++i) {
        mvprintw(i + 1, (TERM_MAX_WIDTH - TITLE_WIDTH) / 2, title[i]);

    }
}
//print up_down_menu
void display_up_down_menu(WINDOW *win, Stage *stage, int min, int max, int step, char * title)
{
    init_pair(3, COLOR_WHITE, COLOR_MAGENTA);
    wclear(win);
    wattron(win, COLOR_PAIR(3));
    wattron(win, A_BOLD);
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
    init_pair(3, COLOR_WHITE, COLOR_MAGENTA);
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
                    cur_up_down = 2;
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
                    stage->selection = 0;
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
                    display_menu(win, stage);
                    break;
                case 1:
                    stage->num = NEW_GAME;
                    stage->selection = 0;
                    stage->num_selections = MENU_NEW_NUM_SELECTIONS;
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
                    numplayer = cur_up_down;
                    display_menu(win, stage);
                    break;
                case 1:
                    stage->num = NEW_GAME;
                    stage->selection = 0;
                    stage->num_selections = MENU_NEW_NUM_SELECTIONS;
                    cur_up_down = numplayer;
                    display_menu(win, stage);
                    break;
                default:
                    break;
            }
        default:
            break;
    }
}







