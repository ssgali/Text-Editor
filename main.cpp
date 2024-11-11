#include <iostream>
#include "classes.h"
#include "functions.h"
#include <curses.h>

using namespace std;

int main()
{
	initscr();           // Initialize PDCurses
	raw();               // Disable line buffering
	keypad(stdscr, TRUE); // Enable keypad input (for handling special keys)
	noecho();            // Don't echo input to the screen
	curs_set(1);         // Show the cursor

	endwin();  // Clean up and exit PDCurses
}
