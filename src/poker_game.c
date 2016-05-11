#include <time.h>
#include <ncurses.h>
#include <signal.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "display.h"

static void init_screen();
static void finish(int sig);
void set_up_player_seat(int num_players);
void start_game();

Deck * deck;
Player * players_list;
WINDOW ** player_seat;

int main(int argc, char *argv[]) {

    struct timespec delay = {0, 500000000L},
            rem;

    setlocale(LC_ALL, "");
    Stage current_stage = create_stage();
    int c = 0;
    int selection = 0;
    int is_game_start = 0;

    //mouse event
    MEVENT event;
    init_screen();
    assume_default_colors(MYCOLOR_BLUE,MYCOLOR_WHITE);

    for(int i=0;i<30;i++) {
        printf("%d\n\r",i);
        refresh();
    }

    //create window
    WINDOW *my_wins[2];

    my_wins[0] = newwin(MENU_HEIGHT, MENU_WIDTH, (getmaxy(stdscr) - MENU_HEIGHT)/2 + 7, (getmaxx(stdscr) - MENU_WIDTH)/2);
    my_wins[1] = newwin(MENU_HEIGHT/2 + 3, MENU_WIDTH/2, getbegy(my_wins[0])+3,
                                  getbegx(my_wins[0]) + MENU_WIDTH/2 + 6);
    WINDOW *current_win = my_wins[0];

    display_title(current_win);
    display_menu(current_win, &current_stage);
    //wchar_t *clubs = (wchar_t *) L"\u2663 \u2667";
    //printw("%ls\n", clubs);

    while(1) {

        c = wgetch(stdscr);//get mouse ad key event

        mvprintw(1, 3, "%i", getmaxy(stdscr));
        mvprintw(25, 3, "keystroke: %i ", c);
        mvprintw(26, 3, "term height: %i ", getmaxy(stdscr));

        mvprintw(27, 3, "Stage: %i ,Selection: %i", current_stage.num, current_stage.selection);
        mvprintw(28, 3, "mode: %i", get_mode());

        if(current_stage.num == IN_GAME) // Start game
        {
            if(is_game_start == 0)
            {
                start_game();
                is_game_start = 1;
            }
            display_player_seat(player_seat, players_list);
            display_deck(player_seat[0],players_list[0]);
            //display_deck(player_seat[1],players_list[1]);
            switch (c)
            {
                case KEY_MOUSE:
                    if(getmouse(&event) == OK && event.bstate & BUTTON1_CLICKED) {
                        mvprintw(29, 3, "%i , %i", event.x, event.y);
                        process_change_card(deck, players_list);
                        display_deck(player_seat[0], players_list[0]);
                    }
                    break;
                case 49:
                    select_card_to_change(1);
                    break;
                case 50:
                    select_card_to_change(2);
                    break;
                case 51:
                    select_card_to_change(3);
                    break;
                case 52:
                    select_card_to_change(4);
                    break;
                case 53:
                    select_card_to_change(5);
                    break;
                case 'q':
                    current_stage.num = MAIN_MENU;
                    current_win = my_wins[0];
                    clear();
                    display_title(current_win);
                    change_stage(current_win, &current_stage);
                    break;
                default:
                    break;
            }

        }
        // process the command keystroke
        else{// Menu
            mvwin(my_wins[0], (getmaxy(stdscr) - MENU_HEIGHT)/2 + 7, (getmaxx(stdscr) - MENU_WIDTH)/2);
            display_menu(current_win, &current_stage);
            is_game_start = 0;
            switch(c)
            {
                case KEY_MOUSE:
                    mvprintw(29, 3, "%i , %i", event.x, event.y);
                    if(getmouse(&event) == OK && event.bstate & BUTTON1_CLICKED)
                    {
                        if(current_stage.num == SINGLE_PLAYER && event.y == 2 + getbegy(current_win)
                           && event.x == getbegx(current_win) + (getmaxx(current_win) - 10)/2)
                        {
                            add_cur_up_down(-get_step_up_down());
                        }
                        else if(current_stage.num == SINGLE_PLAYER && event.y == 2 + getbegy(current_win)
                                && event.x == getbegx(current_win) + (getmaxx(current_win) - 10)/2 + 10)
                        {
                            add_cur_up_down(get_step_up_down());
                        }
                        display_menu(current_win, &current_stage);
                        if(pointed_item(current_win, event.x, event.y, current_stage) >= 0)
                        {
                            current_stage.selection = pointed_item(current_win, event.x, event.y, current_stage);
                            display_menu(current_win, &current_stage);
                            if(current_stage.num == NEW_GAME && (current_stage.selection == 0 || current_stage.selection == 2))
                            {
                                current_win = my_wins[1];
                            }
                            else if(current_stage.num == MODE || (current_stage.num == SINGLE_PLAYER && current_stage.selection == 1))
                            {
                                current_win = my_wins[0];
                            }
                            change_stage(current_win, &current_stage);
                        }

                        if(event.x == 0)
                        {
                            goto end;
                        }
                    }
                    break;
                case KEY_DOWN:
                    if(current_stage.selection < current_stage.num_selections - 1)
                    {
                        current_stage.selection++;
                    }
                    display_menu(current_win, &current_stage);
                    break;
                case KEY_UP:
                    if(current_stage.selection > 0)
                    {
                        current_stage.selection--;
                    }
                    display_menu(current_win, &current_stage);
                    break;
                case KEY_RIGHT:
                    if(current_stage.num == SINGLE_PLAYER )
                    {
                        add_cur_up_down(get_step_up_down());
                    }
                    display_menu(current_win, &current_stage);
                    break;
                case KEY_LEFT:
                    if(current_stage.num == SINGLE_PLAYER )
                    {
                        add_cur_up_down(-get_step_up_down());
                    }
                    display_menu(current_win, &current_stage);
                    break;
                case 13://ENTER
                case 343://ENTER
                    if(current_stage.num == NEW_GAME && (current_stage.selection == 0 || current_stage.selection == 2))
                    {
                        current_win = my_wins[1];
                    }
                    else if(current_stage.num == MODE || (current_stage.num == SINGLE_PLAYER && current_stage.selection == 1))
                    {
                        current_win = my_wins[0];
                    }
                    change_stage(current_win, &current_stage);
                    break;
                case 410:
                    clear();
                    display_menu(current_win, &current_stage);
                    display_title(current_win);
                    break;
                case 'q':
                    finish(0);
                default:
                    break;
            }
        }
    }
    end:
    finish(0);
}


static void init_screen() {
    (void) signal(SIGINT, finish);      /* arrange interrupts to terminate */
    (void) initscr();      /* initialize the curses library */
    clear();
    keypad(stdscr, TRUE);  /* enable keyboard mapping */
    (void) nonl();         /* tell curses not to do NL->CR/NL on output */
    (void) cbreak();       /* take input chars one at a time, don't wait for \n */
    (void) noecho();       /* do not echo input */
    (void) curs_set(0);
    keypad(stdscr, TRUE);

    /* Get all the mouse events */
    mousemask(ALL_MOUSE_EVENTS, NULL);
    start_color();
    timeout(500);          /* wait maximum 500ms for a character */
    /* Use timeout(-1) for blocking mode */
    /* set default color pair */

    init_pair(1, MYCOLOR_BLUE, MYCOLOR_WHITE);
    init_pair(2, MYCOLOR_RED, MYCOLOR_WHITE);
    init_pair(3, MYCOLOR_WHITE, MYCOLOR_MAGNETA);
    init_pair(4, MYCOLOR_RED, MYCOLOR_GREEN);
    init_pair(5, MYCOLOR_RED, MYCOLOR_YELLOW);
    init_pair(6, MYCOLOR_BLACK, MYCOLOR_YELLOW);

}

static void finish(int sig) {
    endwin();
    /* do your non-curses wrap up here, like freeing the memory allocated */

    exit(sig);
}

void set_up_player_seat(int num_players)//set up position of players based on numbers of players
{
    int seat_height = CARD_HEIGHT + 2;
    int seat_width = CARD_WIDTH*5 + 6;
    player_seat = malloc(sizeof(WINDOW)*num_players);

    player_seat[0] = newwin(seat_height, seat_width, getmaxy(stdscr) - seat_height - 2,
                              (getmaxx(stdscr)- seat_width)/2);
    if(num_players == 2)
    {
        player_seat[1] = newwin(seat_height, seat_width, 1, (getmaxx(stdscr) - seat_width)/2);
    }
    else if (num_players == 3)
    {
        player_seat[1] = newwin(seat_height, seat_width, 1, 2);
        player_seat[2] = newwin(seat_height, seat_width, 1, getmaxx(stdscr) - seat_width - 2);
    }
    else if (num_players == 4)
    {
        player_seat[1] = newwin(seat_height, seat_width, 1, (getmaxx(stdscr) - seat_width)/2);
        player_seat[2] = newwin(seat_height, seat_width, (getmaxy(stdscr) - seat_height)/2, 2);
        player_seat[3] = newwin(seat_height, seat_width, (getmaxy(stdscr) - seat_height)/2,
                                getmaxx(stdscr) - seat_width - 2);
    }
}

void start_game()
{
    deck = create_deck();

    shuffle_deck(deck, LENGTH_DECK);

    Game_round round = create_game_round(get_num_players());//create gameround

    set_up_player_seat(round.num_players);

    players_list = create_players_list(NUM_PLAYERS, LENGTH_HANDS, get_mode());
    strcpy(players_list[0].name , "YOU");
    strcpy(players_list[1].name , "BOB");
    strcpy(players_list[2].name , "KEVIN");
    strcpy(players_list[3].name , "SARAH");

    for(int j = 0; j < LENGTH_HANDS; j++){
        for(int i = 0; i < NUM_PLAYERS; i++) {
            deal_card(deck, players_list[i], LENGTH_HANDS);
        }
    }
    display_player_seat(player_seat, players_list);

    display_deck(player_seat[0], players_list[0]);
    //display_deck(player_seat[1], players_list[1]);
    //display_deck(player_seat[2], players_list[2].player_hands);
    //display_deck(player_seat[3], players_list[3].player_hands);
}
