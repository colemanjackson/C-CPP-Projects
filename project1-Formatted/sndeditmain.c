
#include <stdio.h>
#include <stdlib.h>
#include "keyvaluefinder.h"
#include "keyvaluefinderaiff.h"
#include "atocs.h"
#include "cstoa.h"
#include "sndchecklib.h"
#include <ncurses.h>

int main(int argc, char **argv) {
initscr();
int rows;
int columns;
int i;
getmaxyx(stdscr, rows, columns);
move(2, 0);
for( i =0; i <columns; i++){
	mvprintw(2, i, "-");

}
refresh();
getch();

endwin();
}
