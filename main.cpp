#include <iostream>
#include "Core/board.hpp"

using std::cout;
using std::cin;
using std::endl;

int main(){
    dnd::character fred = dnd::character("FRED", "PALADIN", "HILL DWARF", "ACOLYTE", 1, 14, 12, 15, 8, 13, 10, false);
    fred.setWeapon("GREATSWORD");
    fred.setArmor("PLATE");

    dnd::character test = dnd::character("EMPTY", "EMPTY", "EMPTY", "EMPTY");

    fred.save("data/fred.ezdc");
    test.load("data/fred.ezdc");

    cout << test.getName() << endl;

    return 0;
}