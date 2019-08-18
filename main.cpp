#include <iostream>
#include <map>
#include "Character/character.hpp"
#include "Character/weapons.hpp"
#include "Core/dice.hpp"

using std::cout;
using std::cin;
using std::endl;

int main(){
    dnd::character fred = dnd::character("Fred", "Rogue", "Human", "Acolyte", 1, 10, 10, 10, 10, 10, 10, false);

    fred.setWeapon("DAGGER");

    cout << fred.attack() << endl;

    return 0;
}