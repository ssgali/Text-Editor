#include <iostream>
#include "classes.h"
#include "functions.h"
#include <curses.h>

using namespace std;

int main()
{
	BST<BST_Node<string>>* tree = new BST<BST_Node<string>>;
	dll content;
	Queue<Q_node> last_word;
	prepare_bst(tree);
	initscr();           // Initialize PDCurses
	raw();               // Disable line buffering
	keypad(stdscr, TRUE); // Enable keypad input (for handling special keys)
	noecho();            // Don't echo input to the screen
	curs_set(1);         // Show the cursor
	endwin();  // Clean up and exit PDCurses

	delete tree;
}
