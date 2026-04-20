/*
 * Flash Cards v0.04
 *
 * TUI interface for the flashcards program
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <curses.h>

#include "dict.h"
#include "io.h"
#include "test.h"
#include "bool.h"

int all, succ;

#ifndef BS
#define BS	8
#endif
#ifndef ENTER
#define ENTER	13
#endif
#define ESC	27

/* Reset terminal. */
void
close_curses(void)
{
	refresh();
	endwin();
}

void
readln(char *buf, int len)
{
	int i=0, x, y;
	int ch;

	memset(buf, 0, len);
	getyx(stdscr, y, x);
	while (1) {
		ch = getch();
		switch (ch) {
		case ENTER: goto done_readln;
		case ESC: ch = -1; goto done_readln;
		case BS:
			if (i > 0) {
				buf[--i] = '\0';
				move(y, x+i);
				erasechar();
				refresh();
			}
			break;
		default:
			if (i >= len)
				break;
			buf[i++] = (char)ch;
			addch(ch);
			refresh();
			break;
		}
	}
done_readln:
	if (ch < 0) {
		close_curses();
		printf("\nRunning away? I won't update your score.\n");
		exit(0);
	}
	buf[i] = '\0';
}

int
continue_or_exit(void)
{
	printw("Press \"q\" to finish or any other key to continue.\n");
	refresh();
	return(getch());
}

int
test_body(void)
{
	struct record *r;
	char buf[MAXLEN];
	char ch;
	BOOL first_time = TRUE;

	init_test();
	r = roll();
	move(0, 0);
	printw("Round %d\n", all+1);
	do {
		printw("%s: ", r->a);
		refresh();
		readln(buf, MAXLEN-1);
		refresh();
		move(1, 0);
		if (test(r, buf, first_time)) { /* record if first time passed */
			clear();
			printw("Correct!\n");
			if (first_time)
				succ++;
			ch = continue_or_exit();
			break;
		} else {
			first_time = FALSE;
			clear();
			printw("Wrong! Correct answer for %s: %s\n", r->a, r->b);
			beep();
			ch = continue_or_exit();
			if ('q' == ch)
				break;
			printw("Try again. ");
			refresh();
		}
	} while (!first_time);
	clear();
	refresh();
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
}

/* Set terminal to raw mode. */
void
init_curses(void)
{
	initscr();
	raw();
	noecho();
	clear();
	refresh();
}

void
summary(void)
{
	printf("Success/all: %d/%d, accuracy=%.1f%%\n",
	       succ, all, 100.*succ/all);
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
	if (!read_file(fname)) {
		return(-1);
	}

	init_curses();
	test_loop();
	close_curses();

	summary();

	if (write_file(fname))
		return(0);
	return -1;
}
