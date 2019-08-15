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
    dnd::weapons weapons;

    cout << fred.getAbilities()["STR"] << endl;
    cout << fred.getName() << endl;
    cout << fred.getClass() << endl;
    cout << fred.getRace() << endl;
    cout << fred.getBg() << endl;

    cout << dnd::d0.roll() << endl;
    cout << dnd::d1.roll() << endl;
    cout << dnd::d2.roll() << endl;
    cout << dnd::d4.roll() << endl;
    cout << dnd::d6.roll() << endl;
    cout << dnd::d8.roll() << endl;
    cout << dnd::d10.roll() << endl;
    cout << dnd::d12.roll() << endl;
    cout << dnd::d20.roll() << endl;
    cout << dnd::d100.roll() << endl;

    typedef dnd::core::dice die;

    std::map<std::string, die> x = {{"d4", dnd::d4}};

    cout << weapons.getWeaponDice("DAGGER").roll() << endl;
    cout << weapons.getWeaponInfo("DAGGER")[2] << endl;

    return 0;
}