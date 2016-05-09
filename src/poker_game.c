#include <time.h>
#include <ncurses.h>
#include <signal.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "display.h"
#include "poker.h"


static void init_screen();
static void finish(int sig);
void start_game();

Deck * deck;
Player * players_list;

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
    refresh();
    box(stdscr, 1, 0);

    assume_default_colors(COLOR_BLUE,COLOR_WHITE);

    for(int i=0;i<30;i++) {
        printf("%d\n\r",i);
        refresh();
    }

    //create window
    WINDOW *my_wins[2];

    my_wins[0] = newwin(MENU_HEIGHT, MENU_WIDTH, (getmaxy(stdscr) - MENU_HEIGHT)/2 + 5, (getmaxx(stdscr) - MENU_WIDTH)/2);
    my_wins[1] = newwin(MENU_HEIGHT/2 + 3, MENU_WIDTH/2, getbegy(my_wins[0]) + 1,
                                  getbegx(my_wins[0]) + MENU_WIDTH/2 - 1);
    WINDOW *current_win = my_wins[0];

    display_title(my_wins[0]);
    display_menu(my_wins[0], &current_stage);
    //wchar_t *clubs = (wchar_t *) L"\u2663 \u2667";
    //printw("%ls\n", clubs);

    while(1) {
        c = wgetch(stdscr);//get mouse ad key event

        mvprintw(18, 3, "keystroke: %i ", c);
        mvprintw(17, 3, "term height: %i ", getmaxy(stdscr));
        mvprintw(20, 3, "Stage: %i ,Selection: %i", current_stage.num, current_stage.selection);

        if(current_stage.num == IN_GAME)
        {
            if(is_game_start == 0)
            {
                WINDOW *in_game_wins[2];
                in_game_wins[0] = newwin(MENU_HEIGHT, MENU_WIDTH, (getmaxy(stdscr) - MENU_HEIGHT)/2 + 5, (getmaxx(stdscr) - MENU_WIDTH)/2);

                start_game();
                mvprintw(10, 10, players_list[0].name);
                is_game_start = 1;
            }
        }
        // process the command keystroke
        else{
            switch(c)
            {
                case KEY_MOUSE:
                    if(getmouse(&event) == OK)
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
                        mvprintw(19, 1, "%i , %i", event.x, event.y);
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
                    display_title(current_win);
                    display_menu(current_win, &current_stage);
                    break;
                case 'q':
                    finish(0);
                default:
                    break;
            }
        }

    }
    end:
    finish(0);// we're done
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
    //init_pair(1, COLOR_RED, COLOR_BLUE);

}

static void finish(int sig) {
    endwin();
    /* do your non-curses wrap up here, like freeing the memory allocated */

    exit(sig);
}

void start_game()
{
    deck = create_deck();

    shuffle_deck(deck, LENGTH_DECK);

    players_list = create_players_list(NUM_PLAYERS, LENGTH_HANDS);
    strcpy(players_list[0].name , "Duck");
    strcpy(players_list[1].name , "Bob");
    strcpy(players_list[2].name , "Kevin");
    strcpy(players_list[3].name , "Sarah");
}
