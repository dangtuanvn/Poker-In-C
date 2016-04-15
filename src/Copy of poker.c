#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

#define UNO_COLOR_BACKGROUND    0
#define UNO_COLOR_RED           1
#define UNO_COLOR_BLUE          2
#define UNO_COLOR_TEXT          7

static void init_screen();
static void finish(int sig);



int main(int argc, char *argv[]) {

    int x = 0, y = 0, maxx, maxy;
    chtype c;

    struct timespec delay = {0, 500000000L},
            rem;

    init_screen();
    
    for (int i = 1; ; i++) {
        c = (chtype) getch();     /* refresh, accept single keystroke of input */
        
        /* process the command keystroke */
        if (c == 'q') {
            break;
        }

        getmaxyx(stdscr, maxy, maxx);
        if (c == KEY_DOWN && y < maxy-1) {
            y++;
        } else if (c == KEY_RIGHT && x < maxx-1) {
            x++;
        } else if (c == ' ' || c == -1) {
            attrset(COLOR_PAIR(i%3+1));
            c = mvinch(y, x);
            mvaddch(y, x, c+1);
        }
        move(y, x);

        //nanosleep(&delay, &rem);
    }

    finish(0);               /* we're done */
}


static void init_screen() {
    (void) signal(SIGINT, finish);      /* arrange interrupts to terminate */
    (void) initscr();      /* initialize the curses library */
    keypad(stdscr, TRUE);  /* enable keyboard mapping */
    (void) nonl();         /* tell curses not to do NL->CR/NL on output */
    (void) cbreak();       /* take input chars one at a time, don't wait for \n */
    (void) noecho();       /* do not echo input */
    timeout(500);          /* wait maximum 500ms for a character */
    /* Use timeout(-1) for blocking mode */
    
    if (has_colors()) {
    
        start_color();
        // initialise you color pairs (foreground, background)
        init_pair(1, UNO_COLOR_TEXT, UNO_COLOR_BACKGROUND);
        init_pair(2, UNO_COLOR_RED, UNO_COLOR_BACKGROUND);
        init_pair(3, UNO_COLOR_BLUE, UNO_COLOR_BACKGROUND);
    }
    /* set default color pair */
    attrset(COLOR_PAIR(1));
}

static void finish(int sig) {
    endwin();

    /* do your non-curses wrap up here, like freeing the memory allocated */


    exit(sig);
}
