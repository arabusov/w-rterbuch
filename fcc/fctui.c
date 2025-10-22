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
	refresh();
	readln(buf, MAXLEN-1);
	refresh();
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
