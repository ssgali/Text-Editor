//
// Created by ali rauf on 11/11/2024.
//

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <fstream>
#include <iostream>

#include "classes.h"

using namespace std;


void prepare_bst(BST<BST_Node<string>> *&bst)
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

#endif //FUNCTIONS_H
