// card_list.h
// Author: John Yang
// All class declarations related to defining a BST that represents a player's hand

#ifndef CARD_LIST_H
#define CARD_LIST_H
#include "card.h"
using namespace std;

class card_list {
    private:
        struct Node {
        card data;
        Node* left;
        Node* right;
        Node* parent;
        Node(card c) : data(c), left(nullptr), right(nullptr), parent(nullptr) {}
        };
        Node* root;
        void delTree(Node* node);

    public:
    class iterator {
        friend class card_list;
        public:
            iterator(Node* pcurr): current(pcurr) {}
            iterator& operator++();
            iterator& operator--();
            bool operator==(const iterator& other);
            bool operator!=(const iterator& other);
            card operator*();

        private:
            Node* current;
    };
    card_list(Node* rootn): root(rootn) {}
    ~card_list();
    iterator begin();
    iterator end();
    iterator rend();
    iterator rbegin();
    void insert(card ins_card);
    void remove(card rem_card);
    bool contains(card con_card);
    
    

};

#endif