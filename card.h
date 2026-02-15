// card.h
// Author: Your name
// All class declarations related to defining a single card go here

#ifndef CARD_H
#define CARD_H
#include <string>
#include <iostream>
using namespace std;
class card {
    public:
    card(string Psuit, string Prank);

    bool operator > (const card& other) const;
    bool operator < (const card& other) const;
    bool operator== (const card& other) const;
    friend ostream& operator<<(ostream& os, const card& card);
    // string operator<<() const;
    private:
    string suit;
    string rank;
};
#endif
