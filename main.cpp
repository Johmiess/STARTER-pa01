#include <iostream>
#include <fstream>
#include <string>
#include "card.h"
#include "card_list.h"

using namespace std;

int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  card_list list1(nullptr);
  card_list list2(nullptr);
  string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }

  while (getline (cardFile1, line) && (line.length() > 0)){
    list1.insert(card(line.substr(0,1), line.substr(2,2)));
  }
  cardFile1.close();

  while (getline (cardFile2, line) && (line.length() > 0)){
    list2.insert(card(line.substr(0,1), line.substr(2,2)));
  }
  cardFile2.close();

  bool alice_match = false;
  bool bob_match = false;
  while(true){
    alice_match = false;
    for(auto it = list1.begin(); it != list1.end(); ++it){
      if(list2.contains(*it)){
        card c = *it;
        cout << "Alice picked matching card " << c << endl;
        list1.remove(c);
        list2.remove(c);
        alice_match = true;

        break;
      }
    }

    bob_match = false;

     for(auto it = list2.rbegin(); it != list2.rend(); --it){
      if(list1.contains(*it)){
        card c = *it;
        cout << "Bob picked matching card " << c << endl;
        list1.remove(c);
        list2.remove(c);
        bob_match = true;

        break;
      }
    }
    
    if (!alice_match && !bob_match) {
        break;
    }
  }


  cout << endl;
  cout << "Alice's cards:" << endl;
  for(auto it = list1.begin(); it != list1.end(); ++it){
    cout << *it << endl;
  }

  cout << endl;
  cout << "Bob's cards:" << endl;
  for(auto it = list2.begin(); it != list2.end(); ++it){
    cout << *it << endl;
  }

  return 0;
}