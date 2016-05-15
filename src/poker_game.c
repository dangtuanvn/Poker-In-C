#include <time.h>
#include <ncurses.h>
#include <signal.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "display.h"
#include "player.h"
#include "gameround.h"

#define START_Y_PHASE       -3
#define INPUT_WIN_HEIGHT    4
#define INPUT_WIN_WIDTH     18


static void init_screen();
static void finish(int sig);
void set_up_player_seat(int num_players);


Deck * deck;
Player ** players_list;
WINDOW ** player_seat;
Game_round * game_round;

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

    /*for(int i=0;i<30;i++) {
        printf("%d\n\r",i);
        refresh();
    }*/

    //create window
    WINDOW *my_wins[2];

    my_wins[0] = newwin(MENU_HEIGHT, MENU_WIDTH, (getmaxy(stdscr) - MENU_HEIGHT)/2 + 7, (getmaxx(stdscr) - MENU_WIDTH)/2);
    my_wins[1] = newwin(MENU_HEIGHT/2 + 3, MENU_WIDTH/2 + 1, getbegy(my_wins[0]) + 1,
                                  getbegx(my_wins[0]) + MENU_WIDTH/2 - 3);
    WINDOW *current_win = my_wins[0];

    display_title(current_win);
    display_menu(current_win, &current_stage);
    //wchar_t *clubs = (wchar_t *) L"\u2663 \u2667";
    //printw("%ls\n", clubs);

    while(1) {
        c = wgetch(stdscr);//get mouse ad key event
        if(current_stage.num == IN_GAME) // Start game
        {
            if(is_game_start == 0) {
                is_game_start = 1;
                int check_input0 = 0;
                int check_input1 = 0;
                int check_input2 = 0;
                int check_input3 = 0;
                deck = create_deck();
                int in = 0;

                WINDOW * input_win = newwin(INPUT_WIN_HEIGHT, INPUT_WIN_WIDTH, getmaxy(stdscr) - 9, getmaxx(stdscr) / 2 - (CARD_WIDTH * 5 + 6) / 2 - 35);
                shuffle_deck(deck, LENGTH_DECK);

                game_round = create_game_round(get_num_players());//create gameround

                set_up_player_seat(game_round->num_players);

                players_list = create_players_list(get_num_players(), LENGTH_HANDS, get_mode());


                while(game_round->remaining_players != 1 && players_list[0]->status > 0) {
                    // ROUND START
                    deck->top = LENGTH_DECK - 1;
                    shuffle_deck(deck, LENGTH_DECK);

                    for (int j = 0; j < LENGTH_HANDS; j++) {
                        for (int i = 0; i < game_round->num_players; i++) {
                            if (players_list[i]->status != BUSTED) {
                                deal_card(deck, *players_list[i], LENGTH_HANDS);
                            }
                        }
                    }
                    display_player_seat(player_seat, players_list, 0);
                    display_chips_rank(players_list);
                    display_pot(game_round->pot);
                    display_deck(player_seat[0], *players_list[0]);

                    place_ante(game_round, players_list);
                    //printf("Players places initial ante of %d\n", game_round->ante);

                    /*players_list[3]->player_hands[0].number = (Number) 14;
                    players_list[3]->player_hands[0].suit = (Suit) 1;
                    players_list[3]->player_hands[1].number = (Number) 10;
                    players_list[3]->player_hands[1].suit = (Suit) 1;
                    players_list[3]->player_hands[2].number = (Number) 13;
                    players_list[3]->player_hands[2].suit = (Suit) 1;
                    players_list[3]->player_hands[3].number = (Number) 11;
                    players_list[3]->player_hands[3].suit = (Suit) 1;
                    players_list[3]->player_hands[4].number = (Number) 12;
                    players_list[3]->player_hands[4].suit = (Suit) 1;
*/
                    // players_list[3]->status = BUSTED;

                    //mvprintw(25,3,"DEAL CARD!~\n");
                    for (int j = 1; j < get_num_players(); j++) {
                        sort_hands(players_list[j]->player_hands, LENGTH_HANDS);
                    }
                    // BETTING PHASE 1
                    attron(COLOR_PAIR(2));
                    mvprintw(getmaxy(stdscr)/2 + START_Y_PHASE, (int) (getmaxx(stdscr) - strlen("BETTING-PHASE-1"))/2, "BETTING-PHASE-1");
                    attroff(COLOR_PAIR(2));

                    // print_player_info(players_list[0]);
                    /*
                    action_bet(&round, &players_list[0], 20);
                    action_call(&round, &players_list[1]);
                    action_raise(&round, &players_list[2], 70);
                    action_call(&round, &players_list[3]);

                    AI_bet_phase1(&round, &players_list[1]);
                    AI_bet_phase1(&round, &players_list[2]);
                    AI_bet_phase1(&round, &players_list[3]);
                    */
                    int check_fold = 0;

                    int position = 0;

                    while (game_round->position_turn > 0) {
                        if(players_list[position]->status <2){
                            position++;
                            if (position == get_num_players()) {
                                position = 0;
                            }
                            game_round->position_turn--;
                            continue;
                        }
                        update(input_win, player_seat, players_list, game_round, position);
                        waitFor(2);

                        if (players_list[position]->type == HUMAN) {
                            if (players_list[position]->status > 2) {
                                check_input0 = 1;
                                while (check_input0) {
                                    in = wgetch(stdscr);
                                    switch (in) {
                                        case KEY_MOUSE:
                                            if (getmouse(&event) == OK && event.bstate & BUTTON1_CLICKED) {


                                            }
                                            check_input0 = 0;
                                            break;
                                        case 'z':
                                            if(players_list[position]->bet_amount == game_round->call_amount){
                                                action_check(game_round, players_list[position]);
                                            }
                                            else{
                                                action_call(game_round, players_list[position]);
                                            }
                                            check_input0 = 0;
                                            break;
                                        case 'x':
                                            if(players_list[position]->bet_amount == game_round->call_amount){
                                                action_bet(game_round, players_list[position], get_cur_up_down());
                                            }
                                            else{
                                                action_raise(game_round, players_list[position], get_cur_up_down());
                                            }
                                            check_input0 = 0;
                                            break;
                                        case 'c':
                                            action_fold(game_round, players_list[position]);
                                            check_input0 = 0;
                                            break;
                                        case 'v':
                                            if(players_list[position]->bet_amount == game_round->call_amount){
                                                action_bet(game_round, players_list[position], players_list[position]->chips);
                                            }
                                            else{
                                                action_raise(game_round, players_list[position], players_list[position]->chips);
                                            }
                                            check_input0 = 0;
                                            break;
                                        case KEY_LEFT:
                                            add_cur_up_down(-get_step_up_down());
                                            display_in_game_stuff(input_win, players_list, game_round, position);
                                            break;
                                        case KEY_RIGHT:
                                            add_cur_up_down(get_step_up_down());
                                            display_in_game_stuff(input_win, players_list, game_round, position);
                                            break;
                                        case 'q':
                                            current_stage.num = MAIN_MENU;
                                            current_win = my_wins[0];
                                            clear();
                                            display_title(current_win);
                                            change_stage(current_win, &current_stage);
                                            goto stop;
                                        default:
                                            break;
                                    }
                                }
                            }
                        }
                        else {
                            if (players_list[position]->status > 2) {
                                AI_bet_phase1(game_round, players_list[position]);
                                //action_fold(round,players_list[position]);
                            }
                        }

                        check_fold = check_fold_count(game_round, players_list);

                        update(input_win, player_seat, players_list, game_round, position);

                        position++;
                        if (position == get_num_players()) {
                            position = 0;
                        }
                        game_round->position_turn--;
                    }

                    // EXCHANGE CARDS PHASE
                    attron(COLOR_PAIR(2));
                    mvprintw(getmaxy(stdscr)/2 + START_Y_PHASE, (int) (getmaxx(stdscr) - strlen("CHANGE-CARD-PHASE"))/2, "CHANGE-CARD-PHASE");
                    attroff(COLOR_PAIR(2));
                    position = 5;
                    update(input_win, player_seat, players_list, game_round, position);
                    if (!check_fold) {
                        AI_change_cards(deck, players_list, get_num_players());

                        if (players_list[0]->status > 1) {
                            check_input1 = 1;
                            while (check_input1) {
                                in = wgetch(stdscr);
                                switch (in) {
                                    case KEY_MOUSE:
                                        if (getmouse(&event) == OK && event.bstate & BUTTON1_CLICKED) {
                                            mvprintw(29, 3, "%i , %i", event.x, event.y);
                                            process_change_card(deck, players_list);
                                            display_deck(player_seat[0], *players_list[0]);
                                            check_input0 = 1;
                                        }
                                        break;
                                    case '1':
                                        select_card_to_change(0, 1);
                                        display_deck(player_seat[0], *players_list[0]);
                                        break;
                                    case '2':
                                        select_card_to_change(0, 2);
                                        display_deck(player_seat[0], *players_list[0]);
                                        break;
                                    case '3':
                                        select_card_to_change(0, 3);
                                        display_deck(player_seat[0], *players_list[0]);
                                        break;
                                    case '4':
                                        select_card_to_change(0, 4);
                                        display_deck(player_seat[0], *players_list[0]);
                                        break;
                                    case '5':
                                        select_card_to_change(0, 5);
                                        display_deck(player_seat[0], *players_list[0]);
                                        break;
                                    case 13://ENTER
                                    case 343://ENTER
                                        process_change_card(deck, players_list);
                                        display_deck(player_seat[0], *players_list[0]);
                                        check_input1 = 0;
                                        break;
                                    case 'q':
                                        current_stage.num = MAIN_MENU;
                                        current_win = my_wins[0];
                                        clear();
                                        display_title(current_win);
                                        change_stage(current_win, &current_stage);
                                        goto stop;
                                    default:
                                        break;
                                }
                            }
                        }
                    }

                    // BETTING PHASE 2
                    mvprintw(getmaxy(stdscr)/2 + START_Y_PHASE, (int) (getmaxx(stdscr) - strlen("CHANGE-CARD-PHASE"))/2, "                    ");
                    attron(COLOR_PAIR(2));
                    mvprintw(getmaxy(stdscr)/2 + START_Y_PHASE, (int) (getmaxx(stdscr) - strlen("BETTING-PHASE-2"))/2, "BETTING-PHASE-2");
                    attroff(COLOR_PAIR(2));
                    if (!check_fold) {
                        position = 0;
                        game_round->position_turn = game_round->num_players;
                        while (game_round->position_turn > 0) {
                            if(players_list[position]->status <2){
                                position++;
                                if (position == get_num_players()) {
                                    position = 0;
                                }
                                game_round->position_turn--;
                                continue;
                            }
                            update(input_win, player_seat, players_list, game_round, position);
                            waitFor(2);
                            if (players_list[position]->type == HUMAN) {
                                if (players_list[position]->status > 2) {
                                    check_input2 = 1;
                                    while (check_input2) {
                                        in = wgetch(stdscr);
                                        switch (in) {
                                            case KEY_MOUSE:
                                                if (getmouse(&event) == OK && event.bstate & BUTTON1_CLICKED) {


                                                }
                                                check_input2 = 0;
                                                break;
                                            case 'z':
                                                if(players_list[position]->bet_amount == game_round->call_amount){
                                                    action_check(game_round, players_list[position]);
                                                }
                                                else{
                                                    action_call(game_round, players_list[position]);
                                                }
                                                check_input2 = 0;
                                                break;
                                            case 'x':
                                                if(players_list[position]->bet_amount == game_round->call_amount){
                                                    action_bet(game_round, players_list[position], get_cur_up_down());
                                                }
                                                else{
                                                    action_raise(game_round, players_list[position], get_cur_up_down());
                                                }
                                                check_input2 = 0;
                                                break;
                                            case 'c':
                                                action_fold(game_round, players_list[position]);
                                                check_input2 = 0;
                                                break;
                                            case 'v':
                                                if(players_list[position]->bet_amount == game_round->call_amount){
                                                    action_bet(game_round, players_list[position], players_list[position]->chips);
                                                }
                                                else{
                                                    action_raise(game_round, players_list[position], players_list[position]->chips);
                                                }
                                                check_input2 = 0;
                                                break;
                                            case KEY_LEFT:
                                                add_cur_up_down(-get_step_up_down());
                                                display_in_game_stuff(input_win, players_list, game_round, position);
                                                break;
                                            case KEY_RIGHT:
                                                add_cur_up_down(get_step_up_down());
                                                display_in_game_stuff(input_win, players_list, game_round, position);
                                                break;
                                            case 'q':
                                                current_stage.num = MAIN_MENU;
                                                current_win = my_wins[0];
                                                clear();
                                                display_title(current_win);
                                                change_stage(current_win, &current_stage);
                                                goto stop;
                                            default:
                                                break;
                                        }
                                    }
                                }
                            }
                            else {
                                if (players_list[position]->status > 2) {
                                    AI_bet_phase2(game_round, players_list[position]);
                                    //action_fold(round,players_list[position]);
                                }
                            }

                            check_fold = check_fold_count(game_round, players_list);
                            update(input_win, player_seat, players_list, game_round, position);
                            position++;
                            if (position == get_num_players()) {
                                position = 0;
                            }
                            game_round->position_turn--;
                        }
                    }

                    // SHOWDOWN PHASE
                    if (!check_fold) {
                        for (int j = 0; j < get_num_players(); j++) {
                            sort_hands(players_list[j]->player_hands, LENGTH_HANDS);

                        }
                        int top_rank = showdown(*game_round, players_list);
                        get_pot(game_round, players_list, top_rank);
                    }

                    update(input_win, player_seat, players_list, game_round, position);
                    for (int i = 0; i < get_num_players(); i++) {

                        display_deck(player_seat[i], *players_list[i]);
                    }
                    reset_round(game_round, players_list);

                    mvprintw(getmaxy(stdscr)/2 + START_Y_PHASE, (int) (getmaxx(stdscr) - strlen("CHANGE-CARD-PHASE"))/2, "                    ");
                    attron(COLOR_PAIR(3));
                    attron(A_BOLD);
                    mvprintw(getmaxy(stdscr)/2 + START_Y_PHASE, (int) (getmaxx(stdscr) - strlen(" NEXT-ROUND(N) "))/2, " NEXT-ROUND(N) ");
                    attroff(A_BOLD);
                    attroff(COLOR_PAIR(3));
                    check_input3 = 1;
                    if(players_list[0]->status == BUSTED)
                    {
                        check_input3 = 0;
                    }
                    while (check_input3) {
                        in = wgetch(stdscr);
                        switch (in) {
                            case KEY_MOUSE:
                                if (getmouse(&event) == OK && event.bstate & BUTTON1_CLICKED) {

                                }
                                //check_input3 = 0;
                                break;
                            case 'n':
                                check_input3 = 0;
                                break;
                            case 'q':
                                current_stage.num = MAIN_MENU;
                                current_win = my_wins[0];
                                clear();
                                display_title(current_win);
                                change_stage(current_win, &current_stage);
                                goto stop;
                            default:
                                break;
                        }
                    }
                }
                attron(COLOR_PAIR(3));
                attron(A_BOLD);

                if(players_list[0]->status == BUSTED){
                    mvprintw(getmaxy(stdscr)/2 + START_Y_PHASE - 1, (int) (getmaxx(stdscr) - strlen(" GAME-OVER! "))/2, " GAME-OVER! ");
                    mvprintw(getmaxy(stdscr)/2 + START_Y_PHASE, (int) (getmaxx(stdscr) - strlen(" ENTER TO RETURN TO MENU "))/2, " ENTER TO RETURN TO MENU ");

                }
                else{
                    mvprintw(getmaxy(stdscr)/2 + START_Y_PHASE - 1, (int) (getmaxx(stdscr) - strlen(" YOU-WIN! "))/2, " YOU-WIN! ");
                    mvprintw(getmaxy(stdscr)/2 + START_Y_PHASE, (int) (getmaxx(stdscr) - strlen(" ENTER TO RETURN TO MENU "))/2, " ENTER TO RETURN TO MENU ");
                }
                attroff(A_BOLD);
                attroff(COLOR_PAIR(3));

                while (1) {
                    in = wgetch(stdscr);
                    switch (in) {
                        case KEY_MOUSE:
                            if (getmouse(&event) == OK && event.bstate & BUTTON1_CLICKED) {

                            }
                            //check_input3 = 0;
                            break;
                        case 13://ENTER
                        case 343://ENTER
                        case 'q':
                            current_stage.num = MAIN_MENU;
                            current_win = my_wins[0];
                            clear();
                            display_title(current_win);
                            change_stage(current_win, &current_stage);
                            goto stop;
                        default:
                            break;
                    }
                }
            }
            stop:
            continue;
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
    free_deck(deck);
    free_players_list(players_list, get_num_players());
    free_game_round(game_round);
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
        player_seat[1] = newwin(seat_height, seat_width, (getmaxy(stdscr) - seat_height)/2, 2);
        player_seat[2] = newwin(seat_height, seat_width, (getmaxy(stdscr) - seat_height)/2,
                                getmaxx(stdscr) - seat_width - 2);
    }
    else if (num_players == 4)
    {
        player_seat[1] = newwin(seat_height, seat_width, (getmaxy(stdscr) - seat_height)/2, 2);
        player_seat[2] = newwin(seat_height, seat_width, 1, (getmaxx(stdscr) - seat_width)/2);
        player_seat[3] = newwin(seat_height, seat_width, (getmaxy(stdscr) - seat_height)/2,
                                getmaxx(stdscr) - seat_width - 2);
    }
}

