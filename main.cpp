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

  auto it1 = list1.begin();
  auto it2 = list2.rbegin();
  int size1 = 0, size2 = 0;
  for(auto it = list1.begin(); it != list1.end(); ++it) size1++;
  for(auto it = list2.begin(); it != list2.end(); ++it) size2++;

  for(int i = 0; i < size1 + size2; i++){
    if(it1 == list1.end()){
      break;
    }
    if(it2 == list2.rend()){
      break;
    }
    if(i % 2 == 0){
      if(list2.contains(*it1)){
        cout << "Alice picked matching card " << *it1 << endl;
        card temp = *it1;
        ++it1;
        list1.remove(temp);
        list2.remove(temp);
      } else {
        ++it1;
      }
    }
    if(i % 2 != 0){
      if(list1.contains(*it2)){
        cout << "Bob picked matching card " << *it2 << endl;
        card temp = *it2;
        --it2;
        list1.remove(temp);
        list2.remove(temp);
      } else {
        --it2;
      }
    }
  }

  cout << "Alice's cards:" << endl;
  for(auto it = list1.begin(); it != list1.end(); ++it){
    cout << *it << endl;
  }
  cout << "Bob's cards:" << endl;
  for(auto it = list2.begin(); it != list2.end(); ++it){
    cout << *it << endl;
  }

  return 0;
}
