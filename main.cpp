#include <iostream>
#include <vector>
#include "Core/board.hpp"

using std::cout;
using std::cin;
using std::endl;

int main(){
    dnd::character fred = dnd::character("FRED", "PALADIN", "HILL DWARF", "ACOLYTE", 1, 14, 12, 15, 8, 13, 10, false, 1001);
    fred.setWeapon("GREATSWORD");
    fred.setArmor("PLATE");

    fred.save("data/fred.ezdc");

    dnd::character bob = dnd::character("Bob", "ROGUE", "LIGHTFOOT HALFLING", "ACOLYTE", 1, 10, 14, 15, 12, 8, 13, true, 1002);
    bob.setWeapon("RAPIER");
    bob.setArmor("STUDDED LEATHER");

    dnd::core::board board;
    dnd::core::board z;

    board.place(bob, 6, 6);
    board.place(fred, 6, 7);

    std::vector<dnd::character> x;
    x.push_back(fred); x.push_back(bob);

    board.save("data/board.ezdb");
    z.load("data/board.ezdb", x);

    cout << z.getAdjacent(bob.uid)[0].getName() << endl;

    return 0;
}