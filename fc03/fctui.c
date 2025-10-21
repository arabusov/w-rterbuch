/*
 * Flash Cards v0.02
 *
 * TUI interface for the flashcards program
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <curses.h>

#include "dict.h"
#include "io.h"
#include "test.h"

int all, succ;

int
test_body(void)
{
        struct record *r;
        char buf[MAXLEN];
        char ch;

        init_test();
        r = roll();
        move(0, 0);
	printw("Round %d\n", all+1);
        printw("%s: ", r->a);
        scanw("%31s", buf);
        move(1, 0);
        if (test(r, buf)) {
        	printw("Succ.\n");
		succ++;
        } else {
        	printw("Fail. Correct answer: %s\n", r->b);
        	beep();
        }
	printw("press \"q\" to finish");
	refresh();
        ch = getch();
        clear();
        return(ch);
}

void
test_loop(void)
{
	int ch = 0;
	while('q' != ch) {
		ch = test_body();
		all++;
	}
	printw("Success/all: %d/%d, accuracy=%.1f%%\n",
	       succ, all, 100.*succ/all);
	printw("press \"q\" to exit");
	ch = getch();
	clear();
}

void
init_curses(void)
{
	initscr();
	keypad(stdscr, TRUE);
	echo();
	nl();
}

void
close_curses(void)
{
	endwin();
}

char usage[] = "fctui DICTIONARY";

int
main(int argc, char **argv)
{
	const char *fname = argv[1];

        if (argc != 2) {
                fprintf(stderr, "Wrong number of parameters.\n");
                fprintf(stderr, "Usage: %s\n", usage);
                return(-1);
        }
	if (!read_file(fname))
		return(-1);

        init_curses();
        test_loop();
	close_curses();

	if (write_file(fname))
		return(0);
	return -1;
}
