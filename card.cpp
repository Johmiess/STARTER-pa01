// card.cpp
// Author: John Yang
// Implementation of the classes defined in card.h
#include "card.h" // <--- Crucial!
using namespace std; 
const string suitO[] = {"c","d","s","h"};
const string rankO[] = {"a", "2", "3", "4", "5", "6", "7", "8", "9", "10", "j", "q", "k"};
card::card(string Psuit, string Prank){
    suit = Psuit;
    rank = Prank;
}
bool card::operator==(const card& other)const{
    if (this -> suit == other.suit && this -> rank == other.rank){
        return true;
    }
    else {
        return false;
    }
}

bool card::operator<(const card& other) const{
    int this_index = -1;
    int other_index = -1;
    int this_s_index = -1;
    int other_s_index = -1;
    for(int i = 0; i < sizeof(suitO) / sizeof(suitO[0]); i++){
        if(suitO[i] == other.suit){
            other_s_index = i;
        }
        if(suitO[i] == this -> suit){
            this_s_index = i;
        }
    }
    for(int i = 0; i < sizeof(rankO) / sizeof(rankO[0]); i++){
          if(rankO[i] == other.rank){
            other_index = i;
        }

         if(rankO[i] == this -> rank){
            this_index = i;
        }
    }

    if(other_s_index != this_s_index){
        return this_s_index < other_s_index;
    } 
    else {
        return this_index < other_index;
    }
}

bool card::operator>(const card& other) const{
    int this_index = -1;
    int other_index = -1;
    int this_s_index = -1;
    int other_s_index = -1;
    for(int i = 0; i < sizeof(suitO) / sizeof(suitO[0]); i++){
        if(suitO[i] == other.suit){
            other_s_index = i;
        }
        if(suitO[i] == this -> suit){
            this_s_index = i;
        }
    }
    for(int i = 0; i < sizeof(rankO) / sizeof(rank[0]); i++){
          if(rankO[i] == other.rank){
            other_index = i;
        }

         if(rankO[i] == this -> rank){
            this_index = i;
        }
    }

    if(other_s_index != this_s_index){
        return this_s_index > other_s_index;
    } 
    else {
        return this_index > other_index;
    }
}

ostream& operator<<(ostream& os, const card& card){
    os << card.suit << " " << card.rank;
    return os;
}




