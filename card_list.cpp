// card_list.cpp
// Author: John Yang
// Implementation of the classes defined in card_list.h
#include "card_list.h"
card card_list::iterator::operator*(){
    return this -> current -> data; 
}

card_list::iterator& card_list::iterator::operator--(){
    if(current == nullptr) {
        return *this; 
    }
    if(current && current -> left){
        current = current -> left;
        while(current -> right){
        current = current -> right;
        }
    }
    else if(!(current -> left) && current -> parent){
        while(current -> parent != nullptr &&  current -> parent -> left == current){
            current = current -> parent;
        }
            current = current -> parent;
    }
    else {
        current = nullptr;
    }
        return *this;
    }


card_list::iterator& card_list::iterator::operator++(){
    if(current == nullptr) {
        return *this; 
    }
    if(current && current -> right){
        current = current -> right;
        while(current -> left){
            current = current -> left;
        }
    }
    else if(!(current -> right) && current -> parent){
        while(current -> parent != nullptr &&  current -> parent -> right == current){
            current = current -> parent;
        }
        current = current -> parent;
    }
    else {
        current = nullptr;
    }
    return *this;
}

bool card_list::iterator::operator==(const iterator& other){
        if(current == other.current ){
            return true;
        }else {
            return false;
        }
        
}

bool card_list::iterator::operator!=(const iterator& other){
        if( current != other.current){
            return true;
        }else {
            return false;
        }
        
}

card_list::iterator card_list::begin(){
    Node* curr = root;
    if(root == nullptr){
        return iterator(nullptr);
    }
    while(curr -> left){
        curr = curr -> left;
    }
    return iterator(curr);
}

card_list::iterator card_list::end(){
    return iterator(nullptr);
}

card_list::iterator card_list::rbegin(){
    Node* curr = root;
    if(root == nullptr){
        return iterator(nullptr);
    }
    while(curr -> right){
        curr = curr -> right;
    }
    return iterator(curr);
}

card_list::iterator card_list::rend(){
    return iterator(nullptr);
}

void card_list::remove(card rem_card){
    //case 0 dne
    // case root node
    // case 1 leaf node? we want to just remove that and its fine
    // case 2 we have a parent and child node? so the we just connect the child to its parent right.
    // case 3 we have a parent and 2 child. 
    // We find predcessor. copy predcessor value to target. 
    if (!contains(rem_card)){
        return;
    }
    Node* curr = root;
    while(curr -> data != rem_card){
        if(curr -> data > rem_card){
            curr = curr -> left;
        }
        if(curr -> data < rem_card){
            curr = curr -> right;
        }
    }
    if(curr -> left && curr -> right){
        auto it = iterator(curr);
        --it;
        Node* prede = it.current;
        curr -> data = prede -> data;
        curr = prede;
    }
    if(!(curr -> left) && !(curr -> right)){
        Node* del = curr;
        if(curr == root){
            root = nullptr;
        } 
        if(curr -> parent){
            if(curr -> parent -> right == curr){
                curr -> parent -> right = nullptr;
            }
            else{
                curr -> parent -> left = nullptr;
            }
        }
        delete curr;
        return;
    }
    else if(!(curr->left) || !(curr->right)){
        if(!(curr->left)){
            Node* del = curr;
            if(curr -> parent){
                if(curr -> parent -> left == curr){
                    curr -> parent -> left = curr -> right;
                    curr -> right -> parent = curr -> parent;
                } else {
                    curr -> parent -> right = curr -> right;
                    curr -> right -> parent = curr -> parent;
                }
            }
            if(curr == root){
                root = curr -> right;
                root -> parent = nullptr;
            }
            delete curr;
            return;
        } 
        else if (!(curr->right)){
            Node* del = curr;
            if(curr -> parent){
                if(curr -> parent -> left == curr){
                    curr -> parent -> left = curr -> left;
                    curr -> left -> parent = curr -> parent;
                } else {
                    curr -> parent -> right = curr -> left;
                    curr -> left -> parent = curr -> parent;
                }
            }
            if(curr == root){
                root = curr -> left;
                root -> parent = nullptr;
            }
            delete curr;
            return;
        }
    }
}

void card_list::insert(card ins_card){
    Node* ins_node = new Node(ins_card);
    Node* curr = root;
    bool isInserted = false;
    if(root == nullptr){
        root = ins_node;
        return;
    }
    while(!isInserted){
        if(ins_node -> data < curr -> data){
            if(!(curr -> left)){
                curr -> left = ins_node;
                ins_node -> parent = curr;
                isInserted = true;
                return;
            }
            if(curr -> left){
                curr = curr -> left;
            }
        }
        else if(ins_node -> data > curr -> data){
            if(!(curr -> right)){
                curr -> right = ins_node;
                ins_node -> parent = curr;
                isInserted = true;
                return;
            }
            if(curr -> right){
                curr = curr -> right;
            }
        }
        else {
            delete ins_node;
            return;
        }
    }
}

void card_list::delTree(Node* node){
    if(node == nullptr){
        return;
    }
    if(node -> left){
        delTree(node -> left);
    }
    if(node -> right){
        delTree(node -> right);
    }
    delete node;
}

card_list::~card_list(){
    if(root != nullptr){
        delTree(root);
    }
}

bool card_list::contains(card con_card){
    Node* curr = root;
    
    while(curr != nullptr){
        if(curr->data == con_card){
            return true;  
        }
        else if(con_card < curr->data){
            curr = curr->left; 
        }
        else {
            curr = curr->right;  
        }
    }
    return false; 
}
