#include <iostream>
#include "classes.h"
#include "functions.h"
#include <curses.h>

using namespace std;

int initialize_window()
{
    initscr(); // Initialize the screen
    cbreak(); // Disable line buffering
    echo(); // Disable echo to allow manual character handling
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    keypad(stdscr, TRUE); // Enable arrow keys and other special keys
    // Instructions
    mvprintw(0, 0, "Simple Notepad-like Program - Press ESC to exit");
    mvprintw(5, 0, "Choose one of the following options for Misspelled Words: ");
    mvprintw(6, 0, "1. Substitution Technique");
    mvprintw(7, 0, "2. Omission Technique");
    mvprintw(8, 0, "3. Insertion Technique");
    mvprintw(9, 0, "4. Reversal Technique");
    mvprintw(10, 0, "Your Choice: ");
    int ch = getch() - '0';
    clear();
    refresh();
    noecho();
    return ch;
}

int main()
{

    BST<BST_Node<string>>* tree = new BST<BST_Node<string>>;
    dll content;
    Stack<int_node> prev_line_track;
    Queue<D_node> last_word;
    prepare_bst(tree);
    int ch;
    int x = 0, y = 0,bx = -1,by = -1;                               // Starting cursor position
    int choice = 0;
    while(true)
    {
        if(choice > 0 && choice < 5)
            break;
        choice = initialize_window();
    }
    move(0,0);
    while ((ch = getch()) != 27)                    // ESC key ASCII
    {
        int distance = 0;                           // for getting the new words length
        bool changed = false,edited = false;        // status of words changed
        if (ch == 8)
        {
            // Backspace
            // if the cursor is missplaced on the screen
            // place it back to the backup of x and y
            if(bx != -1)
                x = bx;
            if(by != -1)
                y = by;
            move(y, x);
            // reseting x and y
            bx = by = -1;

            // deleting from queue and linked list
            content.remove();
            last_word.delete_from_end();
            if (x > 0)
            {
                x--; // Move cursor back
            }
            else if (y > 0)
            {
                // If at the start of a line but not the topmost line
                y--; // Move to the previous line
                x = prev_line_track.get_last_x(); // Move to the end of the previous line
                prev_line_track.pop();
            }
        }
        // Getting one time backup of Bx and By when any of the key is pressed
        else if (ch == KEY_LEFT)
        {
            if (bx == -1)
                bx = x;
            if (x > 0) x--; // Move cursor left
        }
        else if (ch == KEY_RIGHT)
        {
            if (bx == -1)
                bx = x;
            x++; // Move cursor right
        }
        else if (ch == KEY_UP)
        {
            if (by == -1)
                by = y;
            if (y > 0) y--;
        }
        else if (ch == KEY_DOWN)
        {
            if (by == -1)
                by = y;
            y++; // Move cursor down
        }
        else if (ch == 0x13)
        {
            // CTRL + S functionality
            save_to_file(content);
        }
        else if (ch == 0x0C)
        {
            // Ctrl+L (ASCII 12)
            prev_line_track.push(int_node(x));
            load_from_file(content,prev_line_track);
            by = bx = -1;
        }
        else if (ch == '\n')
        {
            // Newline
            content.insert(ch);
            y++;
            // pushing the x coordinates of x into stack so that when backspace is pressed
            // we move it to that location of x by popping from stack
            prev_line_track.push(int_node(x));
            x = 0;
        }
        else
        {
            // Setting positions to the front of the inserted character
            if(bx != -1)
                x = bx;
            if(by != -1)
                y = by;
            move(y, x);
            bx = by = -1;

            // Handling the new insertion
            if(ch == ' ' && !last_word.is_empty())
            {
                string word = last_word.get_word_as_string();
                last_word.delete_queue();
                if(!tree->search(word))
                {
                    edited = true;
                    string new_word = get_suitable_word(word,tree,choice);
                    if(new_word == word)
                        changed = false;
                    else
                        changed = true;
                    distance = new_word.length() + 1;
                    update_last_word(content,new_word);
                }
            }
            else if(ch != ' ')
            {
                last_word.enqueue(D_node(ch));
            }
            content.insert(ch);
            x++;
        }
        clear();
        if(ch != KEY_LEFT && ch != KEY_RIGHT && ch != KEY_UP && ch != KEY_DOWN)
            move(0,0);
        printw(content.get_as_string().c_str());
        if(ch != KEY_LEFT && ch != KEY_RIGHT && ch != KEY_UP && ch != KEY_DOWN)
            getyx(stdscr, y, x);
        move(y, x); // Update cursor position
        // changing the color of the new word inserted
        if(edited)
        {
            move(y,x-distance);
            if(changed)
                chgat(distance, A_NORMAL, 2, nullptr);
            else
                chgat(distance, A_NORMAL, 1, nullptr);
            move(y,x);
            edited = false;
        }
        refresh();
    }
    endwin(); // End curses mode
    delete tree;
}
