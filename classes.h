//
// Created by Ali Rauf on 11/11/2024.
//

#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>

using namespace std;

class dllnode
{
public:
    char data;
    dllnode *next;
    dllnode *prev ;
    explicit dllnode(const char n = ''): data(n), next(nullptr), prev(nullptr)
    {}
};

class dll // head
{
public:
    dllnode *head = nullptr;
    dllnode *tail = nullptr;
    void insert(const char d)
    {
        // Adds a song to the end of a head
        dllnode *temp = new dllnode(d);
        if (head == nullptr)
        {
            head = temp;
            tail = temp;
            temp->next = nullptr;
            temp->prev = nullptr;
        }
        else
        {
            // insertion at the end
            tail->next = temp;
            temp->prev = tail;
            tail = temp;
        }
    }
    void removesong(const char d, const int i = -1)
    {
        if(i == -1)         //delete from last
        {
            dllnode *temp = tail->prev;
            delete tail;
            tail = temp;
        }
        else
        {
            const dllnode *temp2 = head;
            while (temp2 != nullptr && temp2->data != d)
                temp2 = temp2->next;
            if (temp2 == nullptr)
                return;
            temp2->prev->next = temp2->next;
            temp2->next->prev = temp2->prev;
            delete temp2;
        }
    }
    string get_as_string() const            // returns whole DLL as a single string
    {
        const dllnode *temp = head;
        string content;
        while (temp != nullptr)
        {
            content += temp->data;
            temp = temp->next;
        }
        return content;
    }
    ~dll()
    {
        while (head != nullptr)
        {
            dllnode *temp = head;
            head = head->next;
            delete temp;
        }
    }
};

template <class T>
class BST_Node
{
    public:
    T data;
    int height;
    int level;
    BST_Node* left;
    BST_Node* right;
    explicit BST_Node(T d = "") : data(d),height(0),level(0), left(nullptr), right(nullptr)
    {}
    T get_id()
    {
        return data;
    }
};

class Q_node
{
public:
    char data;
    Q_node* next;

    explicit Q_node(const char d = ''):data(d), next(nullptr)
    {}
};

template <class T>
class Queue
{
public:
    Q_node* head;
    Q_node* tail;

    explicit Queue(): head(nullptr), tail(nullptr)
    {}

    bool is_empty() const
    {
        return head == nullptr;
    }

    void enqueue(T data)
    {
        Q_node* n = new Q_node(data);
        if (is_empty())
            head = tail = n;
        else
        {
            tail->next = n;
            tail = n;
        }
    }

    void dequeue()
    {
        if (is_empty())
            return;
        const Q_node* temp = head;
        head = head->next;
        delete temp;
    }

    void delete_queue()
    {
        while (head != nullptr)
        {
            const Q_node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    char get_head() const
    {
        return head->data;
    }
    ~Queue()
    {
        delete_queue();
    }
};

// Main Class
template <class T>
class BST
{
public:
    T* root;

    BST(): root(nullptr)
    {
    }

    // Basic functions of Tree ADT

    int Height(T* P)
    {
        if (P == nullptr)
            return -1;
        else
            return P->height;
    }

    T* rotate_left(T* Node)
    {
        T* temp = Node->right;
        Node->right = temp->left;
        temp->left = Node;
        Node->height = max(Height(Node->left), Height(Node->right)) + 1;
        temp->height = max(Height(temp->right), Node->height) + 1;
        return temp;
    }

    T* rotate_right(T* Node)
    {
        T* temp = Node->left;
        Node->left = temp->right;
        temp->right = Node;
        Node->height = max(Height(Node->left), Height(Node->right)) + 1;
        temp->height = max(Height(temp->left), Node->height) + 1;
        return temp;
    }

    T* rotate_right_left(T* Node)
    {
        Node->right = rotate_right(Node->right);
        return rotate_left(Node);
    }

    T* rotate_left_right(T* Node)
    {
        Node->left = rotate_left(Node->left);
        return rotate_right(Node);
    }

    int cal_bf(T* Node)
    {
        return Height(Node->left) - Height(Node->right);
    }

    // Updates the levels of each root, i.e. height from the root
    void update_levels(T* root, int current_level = 0)
    {
        if (root == nullptr)
            return;
        root->level = current_level; // Update the current node's level
        update_levels(root->left, current_level + 1); // Update left subtree
        update_levels(root->right, current_level + 1); // Update right subtree
    }

    T* insert(T* root_ptr, T*& data)
    {
        if (root_ptr == nullptr)
        {
            root_ptr = data;
        }
        else
        {
            if (root_ptr->get_id() < data->get_id())
            {
                root_ptr->right = insert(root_ptr->right, data);
                if (cal_bf(root_ptr) == -2)
                {
                    if (cal_bf(root_ptr->right) <= 0)
                        root_ptr = rotate_left(root_ptr);
                    else
                        root_ptr = rotate_right_left(root_ptr);
                }
            }
            else if (root_ptr->get_id() > data->get_id())
            {
                root_ptr->left = insert(root_ptr->left, data);
                if (cal_bf(root_ptr) == 2)
                {
                    if (cal_bf(root_ptr->left) >= 0)
                        root_ptr = rotate_right(root_ptr);
                    else
                        root_ptr = rotate_left_right(root_ptr);
                }
            }
            else
            {
                cout << "Found Duplicate!\n" << endl;
                delete data;
                return root_ptr;
            }
        }
        root_ptr->height = max(Height(root_ptr->left), Height(root_ptr->right)) + 1;
        return root_ptr;
    }

    // a function which accepts an allias of a pointer and if that ptr is nullptr at the end, it means no node was found
    bool search(T*& node_ptr, string p_key) const
    // Functions accepts a nullptr and if that nullptr is not nullptr at the end of the function it means node was found
    {
        node_ptr = root;
        while (node_ptr != nullptr)
        {
            if (node_ptr->get_id() == p_key)
                return true;
            if (p_key < node_ptr->get_id())
                node_ptr = node_ptr->left;
            else
                node_ptr = node_ptr->right;
        }
        return false;
    }

    T* delete_node(T*& root_ptr, string p_key)
    {
        if (root_ptr == nullptr)
            return root_ptr;
        if (root_ptr->get_id() > p_key)
        {
            root_ptr->left = delete_node(root_ptr->left, p_key);
        }
        else if (root_ptr->get_id() < p_key)
        {
            root_ptr->right = delete_node(root_ptr->right, p_key);
        }
        else
        {
            if (root_ptr->left == nullptr && root_ptr->right == nullptr)
            {
                delete root_ptr;
                cout << "Node Deleted Successfully!\n";
                root_ptr = nullptr;
            }
            else if (root_ptr->left == nullptr)
            {
                T* temp = root_ptr->right;
                cout << "Node Deleted Successfully!\n";
                delete root_ptr;
                root_ptr = temp;
            }
            else if (root_ptr->right == nullptr)
            {
                T* temp = root_ptr->left;
                cout << "Node Deleted Successfully!\n";
                delete root_ptr;
                root_ptr = temp;
            }
            else
            {
                T* temp = root_ptr->find_min(root_ptr->right);
                temp->swap_data(root_ptr);
                root_ptr->right = delete_node(root_ptr->right, p_key);
            }
        }
        // If the tree had only one node, return
        if (root_ptr == nullptr)
            return root_ptr;

        // Step 2: Update height of the current node
        root_ptr->height = max(Height(root_ptr->left), Height(root_ptr->right)) + 1;

        // Step 3: Balance the tree
        const int balance = cal_bf(root_ptr);

        // Left-Left Case
        if (balance > 1 && cal_bf(root_ptr->left) >= 0)
            return rotate_right(root_ptr);

        // Left-Right Case
        if (balance > 1 && cal_bf(root_ptr->left) < 0)
        {
            root_ptr->left = rotate_left(root_ptr->left);
            return rotate_right(root_ptr);
        }

        // Right-Right Case
        if (balance < -1 && cal_bf(root_ptr->right) <= 0)
            return rotate_left(root_ptr);

        // Right-Left Case
        if (balance < -1 && cal_bf(root_ptr->right) > 0)
        {
            root_ptr->right = rotate_right(root_ptr->right);
            return rotate_left(root_ptr);
        }
        return root_ptr;
    }

    void delete_bst(T* root)
    {
        if (root != nullptr)
        {
            delete_bst(root->left);
            delete_bst(root->right);
            delete root;
        }
    }

    unsigned long int total_number_of_nodes(T* root)
    {
        if (root == nullptr)
            return 0;
        return total_number_of_nodes(root->left) + total_number_of_nodes(root->right) + 1;
    }

    ~BST()
    {
        delete_bst(root);
    }
};


#endif //CLASSES_H
