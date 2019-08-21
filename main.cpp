#include <iostream>
#include "Core/board.hpp"

using std::cout;
using std::cin;
using std::endl;

int main(){
    dnd::character fred = dnd::character("Fred", "PALADIN", "HILL DWARF", "ACOLYTE", 1, 14, 12, 15, 8, 13, 10, false);
    fred.setWeapon("GREATSWORD");
    fred.setArmor("PLATE");

    dnd::character bob = dnd::character("Bob", "ROGUE", "LIGHTFOOT HALFLING", "ACOLYTE", 1, 10, 14, 15, 12, 8, 13);
    bob.setWeapon("RAPIER");
    bob.setArmor("STUDDED LEATHER");

    dnd::core::board board;

    board.place(fred, 6, 6);
    board.place(bob, 7, 6);

    cout << board.getPos(fred).first << endl;

    board.move(fred, 8, 6);

    cout << board.getPos(fred).first << endl;

    return 0;
}