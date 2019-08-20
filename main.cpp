#include <iostream>
#include "Character/character.hpp"

using std::cout;
using std::cin;
using std::endl;

int main(){
    dnd::character fred = dnd::character("Fred", "Rogue", "ROCK GNOME", "ACOLYTE", 1, 10, 10, 10, 10, 10, 10, false);
    fred.setWeapon("DAGGER");
    fred.setArmor("STUDDED LEATHER");

    cout << fred.rollSkill("RELIGION") << endl;

    return 0;
}