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
    keypad(stdscr, TRUE); // Enable arrow keys and other special keys
    // Instructions
    mvprintw(0, 0, "Simple Notepad-like Program - Press ESC to exit");
    mvprintw(5, 0, "Choose one of the following options for Misspelled Words: ");
    mvprintw(6, 0, "1. Substitution Technique");
    mvprintw(7, 0, "2. Omission Technique");
    mvprintw(8, 0, "3. Insertion Technique");
    mvprintw(9, 0, "4. Reversal Technique");
    getch();
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
    int choice = initialize_window();
    move(0,0);
    while ((ch = getch()) != 27)
    {
        // 27 is the ASCII code for ESC
        if (ch == 8)
        {
            // Backspace
            if(bx != -1)
                x = bx;
            if(by != -1)
                y = by;
            move(y, x);
            bx = by = -1;
            content.remove();
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
        else if (ch == 0x1A)
        {
            // Ctrl+Z Undo Functionality
            printf("Z");
        }
        else if (ch == 0x0C)
        {
            // Ctrl+L (ASCII 12)
            int_node n(x);
            prev_line_track.push(n);
            load_from_file(content,prev_line_track);
            by = bx = -1;
        }
        else if (ch == '\n')
        {
            // Newline
            content.insert(ch);
            y++;
            prev_line_track.push(int_node(x));
            x = 0;
        }
        else
        {
            if(bx != -1)
                x = bx;
            if(by != -1)
                y = by;
            move(y, x);
            bx = by = -1;
            if(ch == ' ' && !last_word.is_empty())
            {
                string word = last_word.get_word_as_string();
                last_word.delete_queue();
                if(!tree->search(tree->root,word))
                {
                    word = get_suitable_word(word,tree,choice);
                    update_last_word(content,word);
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
        printw(content.get_as_string().c_str());
        if(ch == 0x0C)
            getyx(stdscr, y, x);
        move(y, x); // Update cursor position
        refresh();
    }
    endwin(); // End curses mode
    delete tree;
}
