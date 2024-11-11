//
// Created by ali rauf on 11/11/2024.
//

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <fstream>
#include <iostream>
#include "classes.h"

using namespace std;

inline void prepare_bst(BST<BST_Node<string>> *&bst)
{
    fstream dict("dictionary.txt", ios::in);
    if (!dict.is_open())
    {
        cout << "Error opening file" << endl;
        return;
    }
    string content;
    while (getline(dict, content))
    {
        BST_Node<string> *temp = new BST_Node<string>(content);
        bst->root = bst->insert(bst->root, temp);
    }
    dict.close();
    bst->update_levels(bst->root);
    cout << "Dictionary AVL BST created" << endl;
}

void save_to_file(const dll& content)
{
    fstream dict("save.txt", ios::out);
    if (!dict.is_open())
    {
        cout << "Error opening file" << endl;
        return;
    }
    dict << content.get_as_string();
    dict.close();
}

void load_from_file(dll& content)
{
    string filename;
    cout << "Enter File name(alongwith extension) to load from or the whole path(C:/Documents...): ";
    cin >> filename;
    fstream read_file(filename, ios::in);
    if (!read_file.is_open())
    {
        cout << "Error opening file" << endl;
        return;
    }
    char ch;
    while(read_file.get(ch))
        content.insert(ch);
    read_file.close();
}

string substitution(BST<BST_Node<string>> *&bst,const string& word)
{
    string new_word = word;             // word size * 26 = k*26
    for (int j = 0; j < word.size(); j++)
    {
        for(int i = 0; i < 26; i++)
        {
            new_word[j] = 'a' + i;
            if(bst->search(bst->root,new_word))
                return new_word;
        }
    }
    return word;
}

string omission(BST<BST_Node<string>> *&bst,const string& word)
{
    const int modifications = word.size();
    string new_word = word;
    for(int i = 0; i < modifications; i++)
    {
        new_word.erase(i,1);
        if(bst->search(bst->root,new_word))
            return new_word;
        new_word = word;
    }
    return word;
}

string insertion(BST<BST_Node<string>> *&bst,const string& word)
{
    const int modifications = word.size()+1;
    string new_word = word;
    for (int j = 0; j < modifications; j++)
    {
        for(int i = 0; i < 26; i++)
        {
            new_word.insert(j,1,'a' + i);
            if(bst->search(bst->root,new_word))
                return new_word;
            new_word = word;
        }
    }
    return word;
}

string reversal(BST<BST_Node<string>> *&bst,const string& word)
{
    const int modifications = word.size() - 1;
    string new_word = word;
    for(int i = 0; i < modifications; i++)
    {
        swap(new_word[i],new_word[i+1]);
        if(bst->search(bst->root,new_word))
            return new_word;
        new_word = word;
    }
    return word;
}

string get_suitable_word(const string& word,BST<BST_Node<string>> *&bst,const int choice)
{
    string new_word;
    if (choice == 1)
    {
        new_word = substitution(bst,word);
    }
    else if (choice == 2)
    {
        new_word = omission(bst,word);
    }
    else if (choice == 3)
    {
        new_word = insertion(bst,word);
    }
    else if (choice == 4)
    {
        new_word = reversal(bst,word);
    }
    return new_word;
}

string undo();


#endif //FUNCTIONS_H
