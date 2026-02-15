// This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"

using namespace std;

int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  set<card> set1;
  set<card> set2;
  set<card> remove;
  string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }

  //Read each file
  while (getline (cardFile1, line) && (line.length() > 0)){
    set1.insert(card(line.substr(0,1), line.substr(2,2)));
  }
  cardFile1.close();


  while (getline (cardFile2, line) && (line.length() > 0)){
    set2.insert(card(line.substr(0,1), line.substr(2,2)));
  }
  cardFile2.close();

  auto it1 = set1.begin();
  auto it2 = set2.end();
  --it2;
  for(int i = 0; i < set1.size() + set2.size(); i ++){
    if( it1 == set1.end()){
      break;
    }
    if(it2 == set2.end()){
      break;
    }
    if(i % 2 == 0){
      auto find = set2.find(*it1);
      if(find != set2.end()){
        cout << "Alice picked matching card " << *it1 << endl;
        auto temp = it1;
        ++it1;
        set1.erase(temp);
        if(find == it2){
        --it2;
        }
        set2.erase(find);
      } else{
        ++it1;
      }
  
    }
     if(i % 2 != 0){
      auto find = set1.find(*it2);
      if(find != set1.end()){
        cout << "Bob picked matching card " << *it2 << endl;
         auto temp = it2;
        --it2;
        if(find == it1){
        it1++;
        }
        set1.erase(find);
        set2.erase(temp);
      } else {
        --it2;
      }
     
    }
  }
 
it1 = set1.begin();
it2 = set2.begin();
cout << "Alice's cards:"<< endl;
while(it1 != set1.end()){
  cout << *it1 << endl;
  it1++;
}
cout << "Bob's cards:"<< endl;
while(it2 != set2.end()){
  cout << *it2 << endl;
  it2++;
}

  
}
