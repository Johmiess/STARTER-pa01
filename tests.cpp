#include "card_list.h"
#include "card.h"
#include <iostream>
#include <cassert>
#include <sstream>
using namespace std;

void playGame(card_list& hand1, card_list& hand2) {
    bool found = true;
    while (found) {
        found = false;
        for (auto it = hand1.begin(); it != hand1.end(); ++it) {
            if (hand2.contains(*it)) {
                card match = *it;
                cout << match << endl;
                hand1.remove(match);
                hand2.remove(match);
                found = true;
                break;
            }
        }
    }
}

void t_ins_empty() {
    card_list list(nullptr);
    card c1("h", "5");
    list.insert(c1);
    assert(list.contains(c1) == true);
    cout << "t_ins_empty passed!" << endl;
}

void t_ins_single() {
    card_list list(nullptr);
    card c1("h", "k");
    list.insert(c1);
    auto it = list.begin();
    assert(*it == c1);
    ++it;
    assert(it == list.end());
    cout << "t_ins_single passed!" << endl;
}

void t_ins_mult() {
    card_list list(nullptr);
    card c1("h", "5");
    card c2("h", "3");
    card c3("h", "8");
    card c4("h", "a");
    card c5("h", "9");

    list.insert(c1);
    list.insert(c3);
    list.insert(c2);
    list.insert(c5);
    list.insert(c4);

    assert(list.contains(c1) == true);
    assert(list.contains(c2) == true);
    assert(list.contains(c3) == true);
    assert(list.contains(c4) == true);
    assert(list.contains(c5) == true);

    auto it = list.begin();
    assert(*it == c4);
    ++it;
    assert(*it == c2);
    ++it;
    assert(*it == c1);
    ++it;
    assert(*it == c3);
    ++it;
    assert(*it == c5);

    cout << "t_ins_mult passed!" << endl;
}

void t_ins_dup() {
    card_list list(nullptr);
    card c1("s", "7");
    list.insert(c1);
    list.insert(c1);
    assert(list.contains(c1) == true);

    int count = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        count++;
    }
    assert(count == 1);

    cout << "t_ins_dup passed!" << endl;
}

void t_ins_mem() {
    card_list* list_ptr = new card_list(nullptr);
    for (int i = 2; i <= 10; i++) {
        card c("h", to_string(i));
        list_ptr->insert(c);
    }
    delete list_ptr;
    cout << "t_ins_mem passed!" << endl;
}

void t_ins_diff_suits() {
    card_list list(nullptr);
    card c1("c", "5");
    card c2("d", "5");
    card c3("s", "5");
    card c4("h", "5");

    list.insert(c1);
    list.insert(c2);
    list.insert(c3);
    list.insert(c4);

    assert(list.contains(c1) == true);
    assert(list.contains(c2) == true);
    assert(list.contains(c3) == true);
    assert(list.contains(c4) == true);

    auto it = list.begin();
    assert(*it == c1);
    ++it;
    assert(*it == c2);
    ++it;
    assert(*it == c3);
    ++it;
    assert(*it == c4);

    cout << "t_ins_diff_suits passed!" << endl;
}

void t_con_empty() {
    card_list list(nullptr);
    card c1("h", "5");
    assert(list.contains(c1) == false);
    cout << "t_con_empty passed!" << endl;
}

void t_con_single() {
    card_list list(nullptr);
    card c1("h", "k");
    list.insert(c1);
    assert(list.contains(c1) == true);

    card c2("h", "q");
    assert(list.contains(c2) == false);
    cout << "t_con_single passed!" << endl;
}

void t_con_mult() {
    card_list list(nullptr);
    card c1("c", "a");
    card c2("d", "7");
    card c3("h", "k");
    card c4("s", "3");

    list.insert(c1);
    list.insert(c2);
    list.insert(c3);
    list.insert(c4);

    assert(list.contains(c1) == true);
    assert(list.contains(c2) == true);
    assert(list.contains(c3) == true);
    assert(list.contains(c4) == true);
    cout << "t_con_mult passed!" << endl;
}

void t_con_nonexist() {
    card_list list(nullptr);
    card c1("h", "5");
    card c2("h", "8");
    card c3("h", "3");
    list.insert(c1);
    list.insert(c2);
    list.insert(c3);

    card missing("s", "a");
    assert(list.contains(missing) == false);
    cout << "t_con_nonexist passed!" << endl;
}

void t_con_after_rem() {
    card_list list(nullptr);
    card c1("h", "5");
    card c2("h", "8");
    list.insert(c1);
    list.insert(c2);

    assert(list.contains(c1) == true);
    list.remove(c1);
    assert(list.contains(c1) == false);
    assert(list.contains(c2) == true);
    cout << "t_con_after_rem passed!" << endl;
}

void t_rem_leaf() {
    card_list list(nullptr);
    card c1("h", "5");
    card c2("h", "3");
    card c3("h", "8");
    list.insert(c1);
    list.insert(c2);
    list.insert(c3);

    list.remove(c2);
    assert(list.contains(c2) == false);
    assert(list.contains(c1) == true);
    assert(list.contains(c3) == true);
    cout << "t_rem_leaf passed!" << endl;
}

void t_rem_one_child() {
    card_list list(nullptr);
    card c1("h", "5");
    card c2("h", "3");
    card c3("h", "2");
    list.insert(c1);
    list.insert(c2);
    list.insert(c3);

    list.remove(c2);
    assert(list.contains(c2) == false);
    assert(list.contains(c1) == true);
    assert(list.contains(c3) == true);
    cout << "t_rem_one_child passed!" << endl;
}

void t_rem_two_child() {
    card_list list(nullptr);
    card c1("h", "5");
    card c2("h", "3");
    card c3("h", "8");
    card c4("h", "2");
    card c5("h", "4");
    list.insert(c1);
    list.insert(c2);
    list.insert(c3);
    list.insert(c4);
    list.insert(c5);

    list.remove(c2);
    assert(list.contains(c2) == false);
    assert(list.contains(c4) == true);
    assert(list.contains(c5) == true);
    assert(list.contains(c1) == true);
    assert(list.contains(c3) == true);
    cout << "t_rem_two_child passed!" << endl;
}

void t_rem_root() {
    card_list list(nullptr);
    card c1("h", "5");
    card c2("h", "3");
    card c3("h", "8");
    list.insert(c1);
    list.insert(c2);
    list.insert(c3);

    list.remove(c1);
    assert(list.contains(c1) == false);
    assert(list.contains(c2) == true);
    assert(list.contains(c3) == true);

    auto it = list.begin();
    assert(*it == c2);
    ++it;
    assert(*it == c3);
    cout << "t_rem_root passed!" << endl;
}

void t_rem_nonexist() {
    card_list list(nullptr);
    card c1("h", "5");
    list.insert(c1);

    card missing("s", "a");
    list.remove(missing);
    assert(list.contains(c1) == true);
    cout << "t_rem_nonexist passed!" << endl;
}

void t_rem_only() {
    card_list list(nullptr);
    card c1("h", "5");
    list.insert(c1);

    list.remove(c1);
    assert(list.contains(c1) == false);
    assert(list.begin() == list.end());
    cout << "t_rem_only passed!" << endl;
}

void t_iter_empty() {
    card_list list(nullptr);
    assert(list.begin() == list.end());
    assert(list.rbegin() == list.rend());
    cout << "t_iter_empty passed!" << endl;
}

void t_iter_single() {
    card_list list(nullptr);
    card c1("h", "5");
    list.insert(c1);

    auto it = list.begin();
    assert(*it == c1);
    ++it;
    assert(it == list.end());

    auto rit = list.rbegin();
    assert(*rit == c1);
    --rit;
    assert(rit == list.rend());
    cout << "t_iter_single passed!" << endl;
}

void t_iter_inorder() {
    card_list list(nullptr);
    card c1("c", "a");
    card c2("c", "5");
    card c3("c", "k");
    card c4("d", "3");
    card c5("h", "7");

    list.insert(c3);
    list.insert(c1);
    list.insert(c5);
    list.insert(c2);
    list.insert(c4);

    auto it = list.begin();
    assert(*it == c1); ++it;
    assert(*it == c2); ++it;
    assert(*it == c3); ++it;
    assert(*it == c4); ++it;
    assert(*it == c5); ++it;
    assert(it == list.end());
    cout << "t_iter_inorder passed!" << endl;
}

void t_iter_rev() {
    card_list list(nullptr);
    card c1("c", "a");
    card c2("c", "5");
    card c3("c", "k");
    card c4("d", "3");
    card c5("h", "7");

    list.insert(c3);
    list.insert(c1);
    list.insert(c5);
    list.insert(c2);
    list.insert(c4);

    auto it = list.rbegin();
    assert(*it == c5); --it;
    assert(*it == c4); --it;
    assert(*it == c3); --it;
    assert(*it == c2); --it;
    assert(*it == c1); --it;
    assert(it == list.rend());
    cout << "t_iter_rev passed!" << endl;
}

void t_iter_past_end() {
    card_list list(nullptr);
    card c1("h", "5");
    list.insert(c1);

    auto it = list.begin();
    ++it;
    assert(it == list.end());
    ++it;
    assert(it == list.end());
    cout << "t_iter_past_end passed!" << endl;
}

void t_iter_cmp() {
    card_list list(nullptr);
    card c1("h", "3");
    card c2("h", "7");
    list.insert(c1);
    list.insert(c2);

    auto it1 = list.begin();
    auto it2 = list.begin();
    assert(it1 == it2);
    assert(!(it1 != it2));

    ++it2;
    assert(it1 != it2);
    assert(!(it1 == it2));

    assert(list.end() == list.rend());
    cout << "t_iter_cmp passed!" << endl;
}

void t_game_common() {
    card_list hand1(nullptr);
    card_list hand2(nullptr);

    card c1("h", "5");
    card c2("h", "3");
    card c3("d", "a");
    card c4("s", "k");
    card c5("c", "7");

    hand1.insert(c1);
    hand1.insert(c2);
    hand1.insert(c3);

    hand2.insert(c1);
    hand2.insert(c4);
    hand2.insert(c3);

    playGame(hand1, hand2);

    assert(hand1.contains(c1) == false);
    assert(hand1.contains(c3) == false);
    assert(hand1.contains(c2) == true);

    assert(hand2.contains(c1) == false);
    assert(hand2.contains(c3) == false);
    assert(hand2.contains(c4) == true);

    cout << "t_game_common passed!" << endl;
}

void t_game_empty() {
    card_list hand1(nullptr);
    card_list hand2(nullptr);

    card c1("h", "5");
    hand2.insert(c1);

    playGame(hand1, hand2);

    assert(hand2.contains(c1) == true);
    cout << "t_game_empty passed!" << endl;
}

void t_game_no_common() {
    card_list hand1(nullptr);
    card_list hand2(nullptr);

    card c1("h", "5");
    card c2("h", "3");
    card c3("d", "a");
    card c4("s", "k");

    hand1.insert(c1);
    hand1.insert(c2);
    hand2.insert(c3);
    hand2.insert(c4);

    playGame(hand1, hand2);

    assert(hand1.contains(c1) == true);
    assert(hand1.contains(c2) == true);
    assert(hand2.contains(c3) == true);
    assert(hand2.contains(c4) == true);

    cout << "t_game_no_common passed!" << endl;
}

int main() {
    cout << "=== Running INSERT Tests ===" << endl;
    t_ins_empty();
    t_ins_single();
    t_ins_mult();
    t_ins_dup();
    t_ins_mem();
    t_ins_diff_suits();

    cout << "\n=== Running CONTAINS Tests ===" << endl;
    t_con_empty();
    t_con_single();
    t_con_mult();
    t_con_nonexist();
    t_con_after_rem();

    cout << "\n=== Running REMOVE Tests ===" << endl;
    t_rem_leaf();
    t_rem_one_child();
    t_rem_two_child();
    t_rem_root();
    t_rem_nonexist();
    t_rem_only();

    cout << "\n=== Running ITERATOR Tests ===" << endl;
    t_iter_empty();
    t_iter_single();
    t_iter_inorder();
    t_iter_rev();
    t_iter_past_end();
    t_iter_cmp();

    cout << "\n=== Running PLAYGAME Tests ===" << endl;
    t_game_common();
    t_game_empty();
    t_game_no_common();

    cout << "\n All tests passed!" << endl;
    return 0;
}
